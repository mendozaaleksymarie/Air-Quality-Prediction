"""
Train Random Forest model for Air Quality prediction with 3-class labeling
Enhanced with simulation training data, multi-sensor escalation rules, and misting detection
Saves model for use in ML inference server
"""

import pandas as pd
import numpy as np
import pickle
import os
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split, cross_val_score, GridSearchCV
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import matplotlib.pyplot as plt
import seaborn as sns
from datetime import datetime
import glob

# Configuration
DATASET_PATH = os.path.join(os.path.dirname(__file__), '..', 'dataset', 'combined_data.csv')
DATASET_DIR = os.path.join(os.path.dirname(__file__), '..', 'dataset')
MODEL_SAVE_PATH = os.path.join(os.path.dirname(__file__), '..', 'models', 'random_forest_model.pkl')
SCALER_SAVE_PATH = os.path.join(os.path.dirname(__file__), '..', 'models', 'scaler.pkl')

# Status to alarm label mapping
STATUS_TO_LABEL = {
    'Safe (Clean Air)': 0,
    'Safe (Clean Air - High Hum)': 0,
    'Safe (Misting Detected)': 0,
    'Safe': 0,  # Simple Safe label from real sensor data
    'Caution': 1,
    'Hazardous': 2,
    'Hazardous (Wear Mask)': 2,
    'Hazardous (VOC - Wear Mask)': 2,
    'Hazardous (Fire Detected — Evacuate)': 2
}

def apply_status_mapping(status_value):
    """Map Status column to numeric label (0/1/2)"""
    if pd.isna(status_value):
        return None
    
    status_str = str(status_value).strip()
    
    # Try exact match first
    if status_str in STATUS_TO_LABEL:
        return STATUS_TO_LABEL[status_str]
    
    # Try partial matching
    for key, label in STATUS_TO_LABEL.items():
        if key in status_str or status_str in key:
            return label
    
    return None

def load_and_combine_data():
    """Load and combine simulation CSVs and real data CSVs"""
    print("Loading and combining training data...")
    
    dfs = []
    
    # Find all CSV files in dataset directory
    csv_files = glob.glob(os.path.join(DATASET_DIR, '*.csv'))
    
    # Exclude combined_data.csv if it exists (from previous runs)
    csv_files = [f for f in csv_files if 'combined_data' not in os.path.basename(f)]
    
    if not csv_files:
        raise FileNotFoundError(f"No CSV files found in {DATASET_DIR}")
    
    print(f"Found {len(csv_files)} CSV files to process\n")
    
    for file_path in sorted(csv_files):
        filename = os.path.basename(file_path)
        print(f"Processing: {filename}")
        
        try:
            df = pd.read_csv(file_path)
            
            # Standardize column names to lowercase
            df.columns = df.columns.str.lower().str.strip()
            
            # Add source_file column for tracking
            df['source_file'] = filename
            
            # Rename columns to standard names based on what exists
            # Handle both simulation and real sensor data formats
            rename_dict = {}
            
            # Timestamp columns
            if 'timestamp' in df.columns:
                rename_dict['timestamp'] = 'created_at'
            elif 'timestamp_' in df.columns:
                rename_dict['timestamp_'] = 'created_at'
            
            # PM columns
            if 'pm25' in df.columns:
                rename_dict['pm25'] = 'pm2_5'
            if 'pm10' in df.columns:
                rename_dict['pm10'] = 'pm10'
            
            # Gas sensor columns
            if 'mq2_ppm' in df.columns:
                rename_dict['mq2_ppm'] = 'gas'
            if 'mq7_ppm' in df.columns:
                rename_dict['mq7_ppm'] = 'co'
            
            # Temperature column
            if 'temp' in df.columns:
                rename_dict['temp'] = 'temp'
            if 'temperature' in df.columns:
                rename_dict['temperature'] = 'temp'
            
            # Humidity columns
            if 'hum' in df.columns:
                rename_dict['hum'] = 'humidity'
            
            # Status column (simulation data only)
            if 'status' in df.columns:
                rename_dict['status'] = 'status'
            
            # Apply all renames
            df = df.rename(columns=rename_dict)
            
            # For simulation data, map Status to alarm_status
            if 'status' in df.columns:
                df['alarm_status'] = df['status'].apply(apply_status_mapping)
                df = df.drop('status', axis=1)
            
            print(f"  - Loaded {len(df)} rows")
            print(f"  - Columns after standardization: {list(df.columns)}")
            
            dfs.append(df)
            
        except Exception as e:
            print(f"  ERROR loading {filename}: {str(e)}")
            continue
    
    # Combine all dataframes
    combined_df = pd.concat(dfs, ignore_index=True)
    
    # Final standardization: ensure all sensor columns exist
    # For rows missing gas/co (from real data that was already renamed), they'll be NaN
    # For rows missing alarm_status (real data without labels), they'll be NaN - we'll handle this below
    
    print(f"\n=== COMBINED DATASET (Before Label Creation) ===")
    print(f"Total rows: {len(combined_df)}")
    print(f"Columns: {list(combined_df.columns)}")
    print(f"Missing values:\n{combined_df.isnull().sum()}")
    
    return combined_df



def load_data():
    """Load and prepare the dataset"""
    print("Loading dataset...")
    
    base_dir = os.path.dirname(os.path.dirname(__file__))
    
    # Check if combined_data.csv already exists
    if os.path.exists(DATASET_PATH):
        print(f"Found existing combined dataset: {DATASET_PATH}")
        df = pd.read_csv(DATASET_PATH)
    else:
        # Load and combine multiple CSVs
        df = load_and_combine_data()
        
        # Save combined dataset for future use
        print(f"\nSaving combined dataset to {DATASET_PATH}...")
        df.to_csv(DATASET_PATH, index=False)
        print("Combined dataset saved.")
    
    print(f"\nDataset loaded: {df.shape}")
    print(f"Columns: {df.columns.tolist()}")
    print(f"\nClass distribution:\n{df['alarm_status'].value_counts().sort_index()}")
    
    return df

def apply_rolling_average_smoothing(df, columns, window=3):
    """Apply rolling average smoothing to sensor columns"""
    print(f"\nApplying rolling average smoothing (window={window})...")
    
    for col in columns:
        if col in df.columns:
            df[col] = df[col].rolling(window=window, center=True, min_periods=1).mean()
    
    print("Smoothing applied.")
    return df

def extract_time_of_day(df):
    """Extract hour of day from created_at timestamp"""
    print("\nExtracting time_of_day feature...")
    
    if 'created_at' in df.columns:
        try:
            df['created_at'] = pd.to_datetime(df['created_at'])
            df['time_of_day'] = df['created_at'].dt.hour
            print(f"Time_of_day feature created.")
        except Exception as e:
            print(f"Warning: Could not extract time_of_day: {e}")
            df['time_of_day'] = 0
    else:
        # If no timestamp, default to 0
        df['time_of_day'] = 0
    
    return df

def detect_and_report_outliers(df, sensor_columns):
    """Detect outliers (>3 std devs from mean) and report them"""
    print("\n=== OUTLIER DETECTION ===")
    
    outliers = []
    
    for col in sensor_columns:
        if col not in df.columns:
            continue
        
        mean_val = df[col].mean()
        std_val = df[col].std()
        
        # Find rows with values > 3 std devs from mean
        threshold = 3 * std_val
        outlier_rows = df[np.abs(df[col] - mean_val) > threshold]
        
        if len(outlier_rows) > 0:
            print(f"\n{col}:")
            print(f"  Mean: {mean_val:.2f}, Std: {std_val:.2f}, Threshold (±3σ): {threshold:.2f}")
            print(f"  Found {len(outlier_rows)} outlier rows")
            
            for idx, row in outlier_rows.iterrows():
                outliers.append({
                    'row_index': idx,
                    'sensor': col,
                    'value': row[col],
                    'mean': mean_val,
                    'std': std_val,
                    'z_score': (row[col] - mean_val) / std_val if std_val > 0 else 0
                })
    
    if outliers:
        outlier_df = pd.DataFrame(outliers)
        print(f"\nTotal outlier instances: {len(outliers)}")
    else:
        print("No outliers detected.")
    
    return outliers

def apply_misting_detection(row):
    """
    Critical rule: Detect misting (high PM from water droplets, not real dust)
    if humidity >= 95% AND gas (MQ-2) is in normal range → must be misting → Safe (0)
    This overrides all other sensor readings
    """
    humidity = row.get('humidity', 0)
    gas = row.get('gas', 0)
    
    # Misting detection: humidity >= 95% and gas is normal (< 100 ppm baseline)
    if humidity >= 95 and gas < 100:
        return 0  # Safe - misting detected
    
    return None  # Not a misting case

def apply_multi_sensor_escalation(row):
    """
    Apply smart multi-sensor escalation rules based on sensor combinations
    CRITICAL: Check misting rule FIRST before any escalation
    
    Returns alarm_status (0=Safe, 1=Caution, 2=Hazardous)
    """
    
    # Extract sensor readings with safe defaults
    pm2_5 = row.get('pm2_5', 0)
    pm10 = row.get('pm10', 0)
    gas = row.get('gas', 0)
    co = row.get('co', 0)
    temp = row.get('temp', 25)
    humidity = row.get('humidity', 50)
    
    # FIRST: Check misting rule - overrides EVERYTHING
    misting_result = apply_misting_detection(row)
    if misting_result is not None:
        return misting_result
    
    # Define caution thresholds for each sensor
    pm2_5_caution_threshold = 35
    pm10_caution_threshold = 50
    gas_caution_threshold = 100  # MQ-2 baseline ~60-70 ppm in clean air, 100 is caution
    co_caution_threshold = 10    # MQ-7 baseline ~2-5 ppm, 10 is caution
    temp_caution_threshold = 38  # °C - Above normal for comfort but not dangerous alone
    humidity_caution_threshold = 60  # % - humidity alone never triggers alarm in this system
    
    # Count which sensors are in caution/high range
    sensors_in_caution = []
    
    pm2_5_caution = pm2_5 >= pm2_5_caution_threshold
    pm10_caution = pm10 >= pm10_caution_threshold
    gas_caution = gas >= gas_caution_threshold
    co_caution = co >= co_caution_threshold
    temp_high = temp >= temp_caution_threshold
    humidity_high = humidity >= humidity_caution_threshold
    
    if pm2_5_caution:
        sensors_in_caution.append('pm2_5')
    if pm10_caution:
        sensors_in_caution.append('pm10')
    if gas_caution:
        sensors_in_caution.append('gas')
    if co_caution:
        sensors_in_caution.append('co')
    if temp_high:
        sensors_in_caution.append('temp')
    if humidity_high:
        sensors_in_caution.append('humidity')
    
    # DEFAULT: If no sensors in caution, it's Safe
    if len(sensors_in_caution) == 0:
        return 0  # Safe
    
    # SINGLE SENSOR RULES - Never escalate alone (except deadly combinations)
    if len(sensors_in_caution) == 1:
        sensor = sensors_in_caution[0]
        
        # These alone never escalate:
        # - Temperature high: normal Philippine weather
        # - Humidity high: never a danger trigger
        # - Single gas or CO spike: monitor but not alarming without PM
        # - Single PM spike: dust present but not confirmed hazard without gas
        
        return 1  # Caution - single sensor elevated, continue monitoring
    
    # TWO SENSOR RULES - dangerous vs non-dangerous combinations
    if len(sensors_in_caution) == 2:
        sensor_pair = set(sensors_in_caution)
        
        # DANGEROUS combinations -> Hazardous (2)
        dangerous_pairs = [
            {'pm2_5', 'gas'},       # Smoke or combustion
            {'pm2_5', 'co'},        # Fire or exhaust accumulation
            {'pm10', 'gas'},        # Coarse smoke with chemical
            {'pm10', 'co'},         # Exhaust with coarse dust
            {'gas', 'co'},          # Both gas sensors = combustion indicator
            {'pm2_5', 'pm10'},      # Both fine and coarse dust = heavy event
        ]
        
        for dangerous in dangerous_pairs:
            if sensor_pair == dangerous:
                return 2  # Hazardous
        
        # NON-DANGEROUS combinations -> Keep as Caution (1)
        # These are not escalated:
        # - Temp + PM: hot dusty day
        # - Temp + Gas: heat causes MQ-2 cross-sensitivity
        # - Temp + CO: heat affects MQ-7
        # - Humidity + any PM: humid dusty day
        # - Humidity + Gas: humidity causes MQ-2 cross-sensitivity
        # - Humidity + CO: cross-sensitivity concern
        # - Temp + Humidity: just a hot humid day
        
        return 1  # Caution
    
    # THREE OR MORE SENSORS in caution/high range -> Hazardous (2)
    # Exception: if this is a misting situation (handled above), already returned
    if len(sensors_in_caution) >= 3:
        return 2  # Hazardous - multiple sensor layers indicate real hazard
    
    # Fallback (shouldn't reach here)
    return 1  # Caution

def apply_intelligent_labeling(df):
    """
    Apply multi-sensor escalation rules to create 3-class labels
    Overrides any existing alarm_status from raw data
    """
    print("\n=== APPLYING INTELLIGENT LABELING (3-CLASS) ===")
    
    # Create new alarm_status based on multi-sensor rules
    df['alarm_status'] = df.apply(apply_multi_sensor_escalation, axis=1)
    
    print("\nClass distribution after intelligent labeling:")
    print(df['alarm_status'].value_counts().sort_index())
    
    # Breakdown by class
    for cls in [0, 1, 2]:
        class_rows = df[df['alarm_status'] == cls]
        pct = 100 * len(class_rows) / len(df)
        class_name = ['Safe', 'Caution', 'Hazardous'][cls]
        print(f"  {class_name} ({cls}): {len(class_rows)} rows ({pct:.1f}%)")
    
    return df

def preprocess_data(df):
    """Preprocess the data for training with 3-class labels"""
    print("\nPreprocessing data...")
    
    # Make a copy to avoid modifying original
    df = df.copy()
    
    # Handle missing values
    print(f"Missing values before cleaning:\n{df.isnull().sum()}")
    
    # Drop rows with missing critical columns
    critical_columns = ['pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity']
    df = df.dropna(subset=critical_columns)
    
    print(f"Rows after removing missing critical values: {len(df)}")
    
    # Fill remaining minor missing values with column median
    for col in df.columns:
        if df[col].isnull().any():
            df[col] = df[col].fillna(df[col].median())
    
    # Apply rolling average smoothing to sensor columns
    sensor_columns = ['pm2_5', 'pm10', 'gas', 'co']
    df = apply_rolling_average_smoothing(df, sensor_columns, window=3)
    
    # Extract time_of_day feature
    df = extract_time_of_day(df)
    
    # Apply intelligent multi-sensor labeling (3-class)
    df = apply_intelligent_labeling(df)
    
    # Detect and report outliers
    outliers = detect_and_report_outliers(df, sensor_columns)
    
    # Define feature and target columns
    # Include time_of_day as a feature (hour of day)
    feature_columns = ['pm2_5', 'pm10', 'temp', 'humidity', 'gas', 'co', 'time_of_day']
    target_column = 'alarm_status'
    
    # Verify all feature columns exist
    for col in feature_columns:
        if col not in df.columns:
            raise ValueError(f"Feature column '{col}' not found in dataset")
    
    if target_column not in df.columns:
        raise ValueError(f"Target column '{target_column}' not found in dataset")
    
    # Extract features and target
    X = df[feature_columns].values
    y = df[target_column].values
    
    # Verify 3-class labels (0, 1, 2)
    unique_labels = np.unique(y)
    print(f"\nUnique labels in target: {unique_labels}")
    print(f"Target distribution:\n{np.bincount(y.astype(int))}")
    
    print(f"\nFeatures shape: {X.shape}")
    print(f"Feature columns: {feature_columns}")
    
    return df, X, y, feature_columns, outliers



def train_model(X, y):
    """Train Random Forest classifier for 3-class classification"""
    print("\nTraining Random Forest model (3-class)...")
    
    # Split data with stratification for 3 classes
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.25, random_state=42, stratify=y
    )
    
    print(f"\nTraining set size: {len(X_train)}")
    print(f"Test set size: {len(X_test)}")
    print(f"Training set class distribution: {np.bincount(y_train.astype(int))}")
    print(f"Test set class distribution: {np.bincount(y_test.astype(int))}")
    
    # Scale features
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)
    
    # Train Random Forest with hyperparameter tuning
    print("\nPerforming hyperparameter tuning...")
    
    param_grid = {
        'n_estimators': [50, 100, 200],
        'max_depth': [None, 10, 20, 30],
        'min_samples_split': [2, 5, 10],
        'min_samples_leaf': [1, 2, 4]
    }
    
    rf_base = RandomForestClassifier(random_state=42, n_jobs=-1)
    
    grid_search = GridSearchCV(
        rf_base, param_grid, cv=5, 
        scoring='f1_weighted', n_jobs=-1, verbose=1
    )
    
    grid_search.fit(X_train_scaled, y_train)
    
    print(f"\nBest parameters: {grid_search.best_params_}")
    print(f"Best cross-validation score (weighted F1): {grid_search.best_score_:.4f}")
    
    # Best model
    model = grid_search.best_estimator_
    
    # Evaluate on test set
    y_pred = model.predict(X_test_scaled)
    
    print("\n" + "="*60)
    print("=== MODEL PERFORMANCE (3-CLASS) ===")
    print("="*60)
    print(f"Accuracy: {accuracy_score(y_test, y_pred):.4f}")
    print(f"\nConfusion Matrix:\n{confusion_matrix(y_test, y_pred)}")
    
    # Classification report with class names
    class_names = ['Safe (0)', 'Caution (1)', 'Hazardous (2)']
    print(f"\nClassification Report:\n{classification_report(y_test, y_pred, target_names=class_names)}")
    
    # Feature importance
    feature_importance = pd.DataFrame({
        'feature': ['PM2.5', 'PM10', 'Temperature', 'Humidity', 'Gas (MQ-2)', 'CO (MQ-7)', 'Time of Day'],
        'importance': model.feature_importances_
    }).sort_values('importance', ascending=False)
    
    print(f"\nFeature Importance:\n{feature_importance}")
    
    return model, scaler, X_test_scaled, y_test, y_pred

def save_model(model, scaler):
    """Save trained model and scaler"""
    print("\nSaving model...")
    
    # Create models directory
    os.makedirs(os.path.dirname(MODEL_SAVE_PATH), exist_ok=True)
    
    # Save model
    with open(MODEL_SAVE_PATH, 'wb') as f:
        pickle.dump(model, f)
    print(f"Model saved to {MODEL_SAVE_PATH}")
    
    # Save scaler
    with open(SCALER_SAVE_PATH, 'wb') as f:
        pickle.dump(scaler, f)
    print(f"Scaler saved to {SCALER_SAVE_PATH}")

def visualize_results(y_test, y_pred):
    """Create visualizations for 3-class classification"""
    print("\nCreating visualizations...")
    
    # Confusion matrix heatmap with class labels
    plt.figure(figsize=(10, 8))
    cm = confusion_matrix(y_test, y_pred)
    class_labels = ['Safe', 'Caution', 'Hazardous']
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=class_labels, yticklabels=class_labels)
    plt.title('Confusion Matrix - 3-Class Air Quality Prediction')
    plt.ylabel('True Label')
    plt.xlabel('Predicted Label')
    
    os.makedirs(os.path.dirname(MODEL_SAVE_PATH), exist_ok=True)
    save_path = os.path.join(os.path.dirname(MODEL_SAVE_PATH), 'confusion_matrix.png')
    plt.savefig(save_path, dpi=300, bbox_inches='tight')
    print(f"Confusion matrix saved to {save_path}")
    plt.close()

def print_validation_report(df):
    """Print validation report for the dataset"""
    print("\n" + "="*60)
    print("=== VALIDATION REPORT ===")
    print("="*60)
    
    # Check for misting rows
    misting_rows = df[
        (df['humidity'] >= 95) & 
        (df['gas'] < 100) & 
        (df['alarm_status'] == 0)
    ]
    print(f"\nMisting Detection (Humidity ≥95% + Normal Gas):")
    print(f"  Rows correctly labeled as Safe: {len(misting_rows)}")
    
    # Check for specific simulation types if source_file column exists
    if 'source_file' in df.columns:
        print(f"\nClass distribution by source file:")
        for source in df['source_file'].unique():
            source_data = df[df['source_file'] == source]
            print(f"\n  {source}:")
            for cls in [0, 1, 2]:
                count = len(source_data[source_data['alarm_status'] == cls])
                pct = 100 * count / len(source_data) if len(source_data) > 0 else 0
                class_name = ['Safe', 'Caution', 'Hazardous'][cls]
                print(f"    {class_name}: {count} ({pct:.1f}%)")
    
    # Overall class distribution
    print(f"\nFinal class distribution:")
    for cls in [0, 1, 2]:
        count = len(df[df['alarm_status'] == cls])
        pct = 100 * count / len(df)
        class_name = ['Safe', 'Caution', 'Hazardous'][cls]
        print(f"  {class_name}: {count} ({pct:.1f}%)")
    
    print("="*60)

def main():
    """Main training pipeline"""
    print("="*70)
    print("RANDOM FOREST AIR QUALITY ALARM PREDICTION - 3-CLASS MODEL")
    print("Enhanced with Simulation Data & Multi-Sensor Escalation Rules")
    print("="*70)
    
    # Load data (combines all CSVs)
    df = load_data()
    
    # Preprocess with new intelligence
    df_processed, X, y, feature_names, outliers = preprocess_data(df)
    
    # Print validation report
    print_validation_report(df_processed)
    
    # Train model
    model, scaler, X_test, y_test, y_pred = train_model(X, y)
    
    # Save model
    save_model(model, scaler)
    
    # Visualize
    visualize_results(y_test, y_pred)
    
    # Save processed data with source_file tracking
    output_path = DATASET_PATH
    os.makedirs(os.path.dirname(output_path), exist_ok=True)
    df_processed.to_csv(output_path, index=False)
    print(f"\nProcessed dataset saved to: {output_path}")
    
    print("\n" + "="*70)
    print("TRAINING COMPLETE!")
    print("="*70)
    print(f"Model saved to: {MODEL_SAVE_PATH}")
    print(f"Scaler saved to: {SCALER_SAVE_PATH}")
    print(f"Combined dataset saved to: {output_path}")
    print("\nKey improvements in this version:")
    print("  ✓ 3-class labels: Safe (0), Caution (1), Hazardous (2)")
    print("  ✓ Intelligent misting detection (humidity ≥95% overrides all)")
    print("  ✓ Multi-sensor escalation rules")
    print("  ✓ Rolling average smoothing (window=3)")
    print("  ✓ Time-of-day feature for pattern learning")
    print("  ✓ Outlier detection and reporting")
    print("  ✓ Source file tracking for data traceability")
    print("\nYou can now use the ML inference server with the updated model.")



if __name__ == '__main__':
    main()
