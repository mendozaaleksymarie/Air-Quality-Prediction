import pandas as pd
import numpy as np
import os
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix, classification_report
import pickle

# Define paths
dataset_folder = 'dataset'
models_folder = 'models'

# Define labeled real sensor files
labeled_real_sensor_files = [
    '03-16-2026 (Inside of Temfacil).csv',
    '03-17-2026 (Warehouse).csv',
    '03-18-2026 (Outside of Temfacil).csv',
    '03-19-2026 (Fabrication Area).csv',
    '03-30-2026 (Active Floor Area).csv'
]

# Define simulation training datasets
simulation_safe_files = [
    'TRAINING SIMULATION DATA - Safe - Clean Air.csv',
    'TRAINING SIMULATION DATA - Safe - Clean Air (High Humidity).csv',
    'TRAINING SIMULATION DATA - Safe - Misting.csv'
]

simulation_hazardous_files = [
    'TRAINING SIMULATION DATA - Hazardous - Combustion .csv',
    'TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv',
    'TRAINING SIMULATION DATA - Hazardous - Pure Dust.csv',
    'TRAINING SIMULATION DATA - Hazardous - VOC.csv'
]

all_dfs = []

# Load labeled real sensor data
print("Loading LABELED Real Sensor Data...")
for file in labeled_real_sensor_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        # Convert Status to numeric labels
        status_map = {'Safe': 0, 'Caution': 1, 'Hazardous': 2}
        df['alarm_status'] = df['Status'].map(status_map)
        df['source'] = 'Real Sensor (Labeled)'
        all_dfs.append(df)
        print(f"  ✓ {file}")
        print(f"    - Safe: {(df['alarm_status'] == 0).sum()}, Caution: {(df['alarm_status'] == 1).sum()}, Hazardous: {(df['alarm_status'] == 2).sum()}")

# Load simulation training data - Safe
print("\nLoading Simulation Training Data (Safe)...")
for file in simulation_safe_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 0  # Safe
        df['source'] = 'Simulation (Safe)'
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Load simulation training data - Hazardous
print("\nLoading Simulation Training Data (Hazardous)...")
for file in simulation_hazardous_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 2  # Hazardous
        df['source'] = 'Simulation (Hazardous)'
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Combine all data
print("\nCombining all datasets...")
combined_df = pd.concat(all_dfs, ignore_index=True)

# Standardize column names
column_mapping = {
    'Timestamp': 'created_at',
    'PM25': 'pm2_5',
    'PM10': 'pm10',
    'MQ2_ppm': 'gas',
    'MQ7_ppm': 'co',
    'Temp': 'temp',
    'Hum': 'humidity'
}
combined_df = combined_df.rename(columns=column_mapping)

# Parse timestamp and extract time_of_day
combined_df['created_at'] = pd.to_datetime(combined_df['created_at'])
combined_df['time_of_day'] = combined_df['created_at'].dt.hour

# Feature columns
features = ['pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'time_of_day']

# Prepare training data
X = combined_df[features]
y = combined_df['alarm_status']

print(f"\n{'='*60}")
print(f"TRAINING DATA SUMMARY")
print(f"{'='*60}")
print(f"Total samples: {len(combined_df)}")
print(f"\nLabel distribution:")
print(f"  Safe (0): {(y == 0).sum()}")
print(f"  Caution (1): {(y == 1).sum()}")
print(f"  Hazardous (2): {(y == 2).sum()}")

# Split data: 80% train, 20% test
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42, stratify=y)

print(f"\nTrain/Test split (80/20):")
print(f"  Training samples: {len(X_train)}")
print(f"  Test samples: {len(X_test)}")

# Fit scaler on training data
print(f"\nFitting StandardScaler...")
scaler = StandardScaler()
X_train_scaled = scaler.fit_transform(X_train)

# Scale test data
X_test_scaled = scaler.transform(X_test)

# Train Random Forest
print(f"\nTraining Random Forest Classifier (100 trees)...")
rf_model = RandomForestClassifier(n_estimators=100, random_state=42, n_jobs=-1)
rf_model.fit(X_train_scaled, y_train)

# Make predictions
y_pred = rf_model.predict(X_test_scaled)

# Calculate metrics
accuracy = accuracy_score(y_test, y_pred)
precision = precision_score(y_test, y_pred, average='weighted', zero_division=0)
recall = recall_score(y_test, y_pred, average='weighted', zero_division=0)
f1 = f1_score(y_test, y_pred, average='weighted', zero_division=0)

print(f"\n{'='*60}")
print(f"MODEL PERFORMANCE (Test Set)")
print(f"{'='*60}")
print(f"Accuracy:  {accuracy:.4f}")
print(f"Precision: {precision:.4f}")
print(f"Recall:    {recall:.4f}")
print(f"F1-Score:  {f1:.4f}")

# Confusion matrix
cm = confusion_matrix(y_test, y_pred)
print(f"\nConfusion Matrix:")
print(cm)

# Classification report
print(f"\nDetailed Classification Report:")
class_names = ['Safe', 'Caution', 'Hazardous']
print(classification_report(y_test, y_pred, target_names=class_names, zero_division=0))

# Feature importance
print(f"\nFeature Importance:")
feature_importance = pd.DataFrame({
    'feature': features,
    'importance': rf_model.feature_importances_
}).sort_values('importance', ascending=False)
print(feature_importance.to_string(index=False))

# Save model and scaler
print(f"\n{'='*60}")
print(f"SAVING MODEL AND SCALER")
print(f"{'='*60}")

os.makedirs(models_folder, exist_ok=True)

# Save model
model_path = os.path.join(models_folder, 'random_forest_model.pkl')
with open(model_path, 'wb') as f:
    pickle.dump(rf_model, f)
print(f"✓ Model saved to: {model_path}")

# Save scaler
scaler_path = os.path.join(models_folder, 'standard_scaler.pkl')
with open(scaler_path, 'wb') as f:
    pickle.dump(scaler, f)
print(f"✓ Scaler saved to: {scaler_path}")

# Save feature names
features_path = os.path.join(models_folder, 'features.txt')
with open(features_path, 'w') as f:
    f.write(','.join(features))
print(f"✓ Features saved to: {features_path}")

print(f"\n{'='*60}")
print(f"✓ TRAINING COMPLETE!")
print(f"{'='*60}")
print(f"\nNew model trained successfully on:")
print(f"  - {sum(1 for f in labeled_real_sensor_files if os.path.exists(os.path.join(dataset_folder, f)))} labeled real sensor files")
print(f"  - {sum(1 for f in simulation_safe_files if os.path.exists(os.path.join(dataset_folder, f)))} safe simulation files")
print(f"  - {sum(1 for f in simulation_hazardous_files if os.path.exists(os.path.join(dataset_folder, f)))} hazardous simulation files")
print(f"\nTotal training samples: {len(X_train)} (with 7 features)")
print(f"Test accuracy: {accuracy:.2%}")
