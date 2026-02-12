"""
Train Random Forest model for Air Quality prediction
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

# Configuration
# Note: Update this to point to your combined dataset file
DATASET_PATH = os.path.join(os.path.dirname(__file__), '..', 'dataset', 'combined_data.csv')
MODEL_SAVE_PATH = os.path.join(os.path.dirname(__file__), '..', 'models', 'random_forest_model.pkl')
SCALER_SAVE_PATH = os.path.join(os.path.dirname(__file__), '..', 'models', 'scaler.pkl')

def load_data():
    """Load and prepare the dataset"""
    print("Loading dataset...")
    
    base_dir = os.path.dirname(os.path.dirname(__file__))
    
    # Try different possible dataset files
    # Updated to use correct CSV filenames with proper case sensitivity
    dataset_paths = [
        os.path.join(base_dir, 'dataset', 'combined_data.csv'),
        os.path.join(base_dir, 'src', 'preprocessed_data.csv')
    ]
    
    df = None
    for path in dataset_paths:
        if os.path.exists(path):
            print(f"Found dataset: {path}")
            if path.endswith('.csv'):
                df = pd.read_csv(path)
            else:
                df = pd.read_excel(path)
            break
    
    if df is None:
        raise FileNotFoundError(f"No dataset found! Searched: {dataset_paths}")
    
    print(f"Dataset loaded: {df.shape}")
    print(f"Columns: {df.columns.tolist()}")
    
    return df

def preprocess_data(df):
    """Preprocess the data for training"""
    print("\nPreprocessing data...")
    
    # Handle missing values
    print(f"Missing values:\n{df.isnull().sum()}")
    df = df.dropna()
    
    # Define features and target
    # Adjust column names based on your actual dataset
    feature_columns = []
    
    # Try to identify feature columns
    # Features: PM2.5, PM10, Temperature, Humidity, Gas, Carbon Monoxide
    possible_features = ['pm2_5', 'pm25', 'PM2.5', 'pm10', 'PM10', 
                         'temp', 'temperature', 'Temperature',
                         'humidity', 'Humidity', 'hum',
                         'pressure', 'Pressure', 'gas', 'Gas',
                         'co', 'CO', 'carbon_monoxide']
    
    for col in df.columns:
        for feature in possible_features:
            if feature.lower() in col.lower():
                if col not in feature_columns:
                    feature_columns.append(col)
                break
    
    # Target column (alarm)
    target_column = None
    possible_targets = ['alarm', 'Alarm', 'alert', 'Alert']
    
    for col in df.columns:
        for target in possible_targets:
            if target.lower() in col.lower():
                target_column = col
                break
        if target_column:
            break
    
    if not target_column:
        # Create alarm based on thresholds
        print("Creating alarm column based on thresholds...")
        df['alarm'] = 0
        
        # Find PM2.5 column
        pm25_col = [c for c in df.columns if 'pm2' in c.lower() or 'pm25' in c.lower()]
        pm10_col = [c for c in df.columns if 'pm10' in c.lower()]
        temp_col = [c for c in df.columns if 'temp' in c.lower()]
        
        if pm25_col:
            df.loc[df[pm25_col[0]] > 35, 'alarm'] = 1
        if pm10_col:
            df.loc[df[pm10_col[0]] > 50, 'alarm'] = 1
        if temp_col:
            df.loc[(df[temp_col[0]] > 30) | (df[temp_col[0]] < 18), 'alarm'] = 1
        
        target_column = 'alarm'
    
    print(f"Features: {feature_columns}")
    print(f"Target: {target_column}")
    
    # Extract features and target
    X = df[feature_columns].values
    y = df[target_column].values
    
    # Ensure binary classification
    y = (y > 0).astype(int)
    
    print(f"\nFeatures shape: {X.shape}")
    print(f"Target distribution: {np.bincount(y)}")
    
    return X, y, feature_columns

def train_model(X, y):
    """Train Random Forest classifier"""
    print("\nTraining Random Forest model...")
    
    # Split data
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, test_size=0.25, random_state=42, stratify=y
    )
    
    # Scale features
    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)
    X_test_scaled = scaler.transform(X_test)
    
    # Train Random Forest with hyperparameter tuning
    print("Performing hyperparameter tuning...")
    
    param_grid = {
        'n_estimators': [50, 100, 200],
        'max_depth': [None, 10, 20, 30],
        'min_samples_split': [2, 5, 10],
        'min_samples_leaf': [1, 2, 4]
    }
    
    rf_base = RandomForestClassifier(random_state=42)
    
    grid_search = GridSearchCV(
        rf_base, param_grid, cv=5, 
        scoring='accuracy', n_jobs=-1, verbose=1
    )
    
    grid_search.fit(X_train_scaled, y_train)
    
    print(f"\nBest parameters: {grid_search.best_params_}")
    print(f"Best cross-validation score: {grid_search.best_score_:.4f}")
    
    # Best model
    model = grid_search.best_estimator_
    
    # Evaluate on test set
    y_pred = model.predict(X_test_scaled)
    
    print("\n=== Model Performance ===")
    print(f"Accuracy: {accuracy_score(y_test, y_pred):.4f}")
    print(f"\nConfusion Matrix:\n{confusion_matrix(y_test, y_pred)}")
    print(f"\nClassification Report:\n{classification_report(y_test, y_pred)}")
    
    # Feature importance
    feature_importance = pd.DataFrame({
        'feature': range(len(model.feature_importances_)),
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
    """Create visualizations"""
    print("\nCreating visualizations...")
    
    # Confusion matrix heatmap
    plt.figure(figsize=(8, 6))
    cm = confusion_matrix(y_test, y_pred)
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues')
    plt.title('Confusion Matrix')
    plt.ylabel('True Label')
    plt.xlabel('Predicted Label')
    save_path = os.path.join(os.path.dirname(MODEL_SAVE_PATH), 'confusion_matrix.png')
    plt.savefig(save_path)
    print(f"Confusion matrix saved to {save_path}")
    plt.close()

def main():
    """Main training pipeline"""
    print("="*60)
    print("Random Forest Air Quality Alarm Prediction")
    print("="*60)
    
    # Load data
    df = load_data()
    
    # Preprocess
    X, y, feature_names = preprocess_data(df)
    
    # Train model
    model, scaler, X_test, y_test, y_pred = train_model(X, y)
    
    # Save model
    save_model(model, scaler)
    
    # Visualize
    visualize_results(y_test, y_pred)
    
    print("\n" + "="*60)
    print("Training complete!")
    print("="*60)
    print(f"Model saved to: {MODEL_SAVE_PATH}")
    print(f"Scaler saved to: {SCALER_SAVE_PATH}")
    print("\nYou can now use the ML inference server to make predictions.")

if __name__ == '__main__':
    main()
