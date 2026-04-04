import pandas as pd
import os
import glob

# Define paths
dataset_folder = 'dataset'

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

# Status to numeric label mapping
STATUS_TO_LABEL = {
    'Safe': 0,
    'Caution': 1,
    'Hazardous': 2
}

all_dfs = []

# Load labeled real sensor data
print("Loading NEW Labeled Real Sensor Data...")
for file in labeled_real_sensor_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        # Convert Status to numeric labels
        df['alarm_status'] = df['Status'].map(STATUS_TO_LABEL)
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}")
        status_counts = df['Status'].value_counts()
        print(f"    - {status_counts.to_dict()}")

# Load simulation training data - Safe
print("\nLoading Simulation Training Data (Safe)...")
for file in simulation_safe_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 0  # Safe
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Load simulation training data - Hazardous
print("\nLoading Simulation Training Data (Hazardous)...")
for file in simulation_hazardous_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 2  # Hazardous
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Combine all data
print("\n" + "="*60)
print("Combining all datasets...")
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

# Sort by timestamp
combined_df = combined_df.sort_values('created_at').reset_index(drop=True)

# Select final columns
final_columns = ['created_at', 'pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'source_file', 'alarm_status', 'time_of_day']
combined_df = combined_df[final_columns]

# Save to CSV
output_path = os.path.join(dataset_folder, 'combined_data.csv')
combined_df.to_csv(output_path, index=False)

print(f"\n✓ combined_data.csv has been updated!")
print(f"  Location: {output_path}")
print(f"  Total records: {len(combined_df)}")
print(f"  Date range: {combined_df['created_at'].min()} to {combined_df['created_at'].max()}")

print(f"\nLabel distribution:")
for label in [0, 1, 2]:
    count = (combined_df['alarm_status'] == label).sum()
    pct = 100 * count / len(combined_df)
    label_name = {0: 'Safe', 1: 'Caution', 2: 'Hazardous'}[label]
    print(f"  {label_name} ({label}): {count} ({pct:.1f}%)")

print(f"\nBreakdown by source file:")
for source in combined_df['source_file'].unique():
    subset = combined_df[combined_df['source_file'] == source]
    print(f"  {source}: {len(subset)} rows")

print("\n" + "="*60)
print("✓ UPDATE COMPLETE - Ready for model training!")
print("="*60)
