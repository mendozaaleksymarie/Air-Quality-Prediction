import pandas as pd
import os
import glob

dataset_folder = 'dataset'

# Define simulation datasets by class
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

real_sensor_files = [
    '03-16-2026 (Inside of Temfacil).csv',
    '03-17-2026 (Warehouse).csv',
    '03-18-2026 (Outside of Temfacil).csv',
    '03-19-2026 (Fabrication Area).csv',
    '03-30-2026 (Active Floor Area).csv'
]

all_dfs = []

# Load simulation data with Safe label (0)
print("Loading Safe simulation data...")
for file in simulation_safe_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 0
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Load simulation data with Hazardous label (2)
print("\nLoading Hazardous simulation data...")
for file in simulation_hazardous_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 2
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Load real sensor data (0 - Safe by default, no alarm)
print("\nLoading Real sensor data...")
for file in real_sensor_files:
    path = os.path.join(dataset_folder, file)
    if os.path.exists(path):
        df = pd.read_csv(path)
        df['alarm_status'] = 0  # Real data has no alarm
        df['source_file'] = file
        all_dfs.append(df)
        print(f"  ✓ {file}: {len(df)} rows")

# Combine all
print("\nCombining datasets...")
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

# Parse timestamp
combined_df['created_at'] = pd.to_datetime(combined_df['created_at'])

# Extract hour for time_of_day
combined_df['time_of_day'] = combined_df['created_at'].dt.hour

# Sort by timestamp
combined_df = combined_df.sort_values('created_at').reset_index(drop=True)

# Select final columns
final_columns = ['created_at', 'pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'source_file', 'alarm_status', 'time_of_day']
combined_df = combined_df[final_columns]

# Save
combined_df.to_csv(os.path.join(dataset_folder, 'combined_data.csv'), index=False)

print("\n" + "="*60)
print("✓ ORIGINAL combined_data.csv has been restored!")
print("="*60)
print(f"\nDataset info:")
print(f"  Total records: {len(combined_df)}")
print(f"  Date range: {combined_df['created_at'].min()} to {combined_df['created_at'].max()}")
print(f"\nLabel distribution (ORIGINAL 3-class):")
print(combined_df['alarm_status'].value_counts().sort_index())
print(f"  Safe (0): {(combined_df['alarm_status'] == 0).sum()}")
print(f"  Caution (1): {(combined_df['alarm_status'] == 1).sum()}")
print(f"  Hazardous (2): {(combined_df['alarm_status'] == 2).sum()}")
