"""
Train Random Forest model with labeled real sensor data + simulation data
Simplified version without hyperparameter tuning
"""

import pandas as pd
import numpy as np
import pickle
import os
import glob
from sklearn.ensemble import RandomForestClassifier
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score, precision_score, recall_score, f1_score

# Paths
base_dir = os.path.dirname(os.path.dirname(__file__))
dataset_dir = os.path.join(base_dir, 'dataset')

# Status mapping dictionary
STATUS_TO_LABEL = {
    'Safe': 0,
    'Caution': 1,
    'Hazardous': 2,
}

def apply_status_mapping(status_value):
    """Convert Status text to numeric label"""
    if pd.isna(status_value):
        return None
    status_str = str(status_value).strip()
    return STATUS_TO_LABEL.get(status_str, None)

def load_all_data():
    """Load and combine labeled real sensor data + simulation training data"""
    print("="*70)
    print("LOADING DATA: LABELED REAL SENSORS + SIMULATION TRAINING DATA")
    print("="*70)
    
    labeled_real_files = [
        '03-16-2026 (Inside of Temfacil).csv',
        '03-17-2026 (Warehouse).csv',
        '03-18-2026 (Outside of Temfacil).csv',
        '03-19-2026 (Fabrication Area).csv',
        '03-30-2026 (Active Floor Area).csv'
    ]
    
    simulation_safe = [
        'TRAINING SIMULATION DATA - Safe - Clean Air.csv',
        'TRAINING SIMULATION DATA - Safe - Clean Air (High Humidity).csv',
        'TRAINING SIMULATION DATA - Safe - Misting.csv'
    ]
    
    simulation_hazard = [
        'TRAINING SIMULATION DATA - Hazardous - Combustion .csv',
        'TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv',
        'TRAINING SIMULATION DATA - Hazardous - Pure Dust.csv',
        'TRAINING SIMULATION DATA - Hazardous - VOC.csv'
    ]
    
    all_dfs = []
    
    # Load labeled real sensor data
    print("\nLoading LABELED Real Sensor Data:")
    for filename in labeled_real_files:
        path = os.path.join(dataset_dir, filename)
        if os.path.exists(path):
            df = pd.read_csv(path)
            # Convert Status to alarm_status
            df['alarm_status'] = df['Status'].apply(apply_status_mapping)
            df['source'] = 'Real (Labeled)'
            
            # Standardize column names
            df = df.rename(columns={
                'Timestamp': 'created_at',
                'PM25': 'pm2_5',
                'PM10': 'pm10',
                'MQ2_ppm': 'gas',
                'MQ7_ppm': 'co',
                'Temp': 'temp',
                'Hum': 'humidity'
            })
            
            all_dfs.append(df)
            counts = df['alarm_status'].value_counts()
            print(f"  ✓ {filename}: {len(df)} rows")
            print(f"    Safe={counts.get(0, 0)}, Caution={counts.get(1, 0)}, Hazardous={counts.get(2, 0)}")
    
    # Load simulation safe data
    print("\nLoading Simulation Training Data (Safe):")
    for filename in simulation_safe:
        path = os.path.join(dataset_dir, filename)
        if os.path.exists(path):
            df = pd.read_csv(path)
            df['alarm_status'] = 0  # Safe
            df['source'] = 'Simulation (Safe)'
            
            # Standardize column names
            df = df.rename(columns={
                'timestamp': 'created_at',
                'Timestamp': 'created_at',
            })
            
            all_dfs.append(df)
            print(f"  ✓ {filename}: {len(df)} rows (Safe)")
    
    # Load simulation hazard data
    print("\nLoading Simulation Training Data (Hazardous):")
    for filename in simulation_hazard:
        path = os.path.join(dataset_dir, filename)
        if os.path.exists(path):
            df = pd.read_csv(path)
            df['alarm_status'] = 2  # Hazardous
            df['source'] = 'Simulation (Hazard)'
            
            # Standardize column names
            df = df.rename(columns={
                'timestamp': 'created_at',
                'Timestamp': 'created_at',
            })
            
            all_dfs.append(df)
            print(f"  ✓ {filename}: {len(df)} rows (Hazardous)")
    
    # Combine all data
    combined_df = pd.concat(all_dfs, ignore_index=True)
    
    # Standardize column names to lowercase
    combined_df.columns = combined_df.columns.str.lower().str.strip()
    
    # Parse timestamp and extract hour
    combined_df['created_at'] = pd.to_datetime(combined_df['created_at'], errors='coerce')
    combined_df['time_of_day'] = combined_df['created_at'].dt.hour
    
    print(f"\n{'='*70}")
    print(f"COMBINED DATASET SUMMARY")
    print(f"{'='*70}")
    print(f"Total records: {len(combined_df)}")
    print(f"\nLabel distribution:")
    counts = combined_df['alarm_status'].value_counts().sort_index()
    for cls, count in counts.items():
        label_name = ['Safe', 'Caution', 'Hazardous'][cls]
        pct = 100 * count / len(combined_df)
        print(f"  {label_name} ({cls}): {count} ({pct:.1f}%)")
    
    return combined_df

def train_model(combined_df):
    """Train Random Forest model"""
    
    # Define features
    features = ['pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'time_of_day']
    
    # Prepare data
    X = combined_df[features].fillna(0)
    y = combined_df['alarm_status']
    
    # Train-test split (80-20)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)
    
    print(f"\n{'='*70}")
    print(f"TRAINING CONFIGURATION")
    print(f"{'='*70}")
    print(f"Training samples: {len(X_train)}")
    print(f"Test samples: {len(X_test)}")
    print(f"Features: {features}")
    
    # Scale data
    print(f"\nFitting StandardScaler...")
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)
    
    # Train Random Forest
    print(f"Training Random Forest Classifier (100 trees)...")
    rf_model = RandomForestClassifier(
        n_estimators=100,
        max_depth=20,
        min_samples_split=10,
        min_samples_leaf=5,
        random_state=42,
        n_jobs=-1,
        verbose=1
    )
    rf_model.fit(X_train_scaled, y_train)
    
    # Evaluate
    y_pred = rf_model.predict(X_test_scaled)
    
    print(f"\n{'='*70}")
    print(f"MODEL PERFORMANCE")
    print(f"{'='*70}")
    
    accuracy = accuracy_score(y_test, y_pred)
    precision = precision_score(y_test, y_pred, average='weighted', zero_division=0)
    recall = recall_score(y_test, y_pred, average='weighted', zero_division=0)
    f1 = f1_score(y_test, y_pred, average='weighted', zero_division=0)
    
    print(f"\nOverall Metrics:")
    print(f"  Accuracy:  {accuracy:.4f}")
    print(f"  Precision: {precision:.4f}")
    print(f"  Recall:    {recall:.4f}")
    print(f"  F1-Score:  {f1:.4f}")
    
    print(f"\nConfusion Matrix:")
    cm = confusion_matrix(y_test, y_pred)
    print(cm)
    
    print(f"\nDetailed Classification Report:")
    class_names = ['Safe', 'Caution', 'Hazardous']
    print(classification_report(y_test, y_pred, target_names=class_names, zero_division=0))
    
    # Feature importance
    print(f"\nFeature Importance:")
    importance_df = pd.DataFrame({
        'feature': features,
        'importance': rf_model.feature_importances_
    }).sort_values('importance', ascending=False)
    print(importance_df.to_string(index=False))
    
    # Save model
    models_dir = os.path.join(base_dir, 'models')
    os.makedirs(models_dir, exist_ok=True)
    
    model_path = os.path.join(models_dir, 'random_forest_model.pkl')
    with open(model_path, 'wb') as f:
        pickle.dump(rf_model, f)
    print(f"\n✓ Model saved to: {model_path}")
    
    scaler_path = os.path.join(models_dir, 'scaler.pkl')
    with open(scaler_path, 'wb') as f:
        pickle.dump(scaler, f)
    print(f"✓ Scaler saved to: {scaler_path}")
    
    features_path = os.path.join(models_dir, 'features.txt')
    with open(features_path, 'w') as f:
        f.write(','.join(features))
    print(f"✓ Features saved to: {features_path}")
    
    print(f"\n{'='*70}")
    print(f"✓ TRAINING COMPLETE!")
    print(f"{'='*70}")
    print(f"\nModel trained successfully on:")
    print(f"  - Labeled real sensor data (5 files)")
    print(f"  - Simulation training data (7 files)")
    print(f"\nTotal: {len(combined_df)} samples across 3 classes")
    print(f"Test Accuracy: {accuracy:.2%}")

if __name__ == '__main__':
    # Load data
    combined_df = load_all_data()
    
    # Train model
    train_model(combined_df)
