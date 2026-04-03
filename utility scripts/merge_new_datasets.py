"""
Merge new air quality sensor datasets and create combined_data.csv
Handles new dataset format: Timestamp, PM25, PM10, MQ2_ppm, MQ7_ppm, Temp, Hum
"""

import pandas as pd
import os
import glob

# Define dataset folder
dataset_folder = os.path.join(os.path.dirname(__file__), '..', 'dataset')

# Find all CSV files with pattern "MM-DD-YYYY (Location).csv"
csv_files = glob.glob(os.path.join(dataset_folder, '*.csv'))
print(f"Found {len(csv_files)} CSV files")

# Filter out combined_data.csv if it exists
csv_files = [f for f in csv_files if 'combined_data.csv' not in f]
print(f"Processing {len(csv_files)} datasets for merging")

if not csv_files:
    print("No datasets found to merge!")
    exit(1)

# Read and combine all datasets
all_dfs = []
for file_path in sorted(csv_files):
    print(f"Reading: {os.path.basename(file_path)}")
    df = pd.read_csv(file_path)
    all_dfs.append(df)
    print(f"  - Shape: {df.shape}")

# Combine all dataframes
combined_df = pd.concat(all_dfs, ignore_index=True)
combined_df = combined_df.sort_values('Timestamp').reset_index(drop=True)

print(f"\nCombined dataset shape: {combined_df.shape}")
print(f"Columns: {combined_df.columns.tolist()}")

# Rename columns to standard format for training
rename_map = {
    'Timestamp': 'created_at',
    'PM25': 'pm2_5',
    'PM10': 'pm10',
    'MQ2_ppm': 'gas',
    'MQ7_ppm': 'co',
    'Temp': 'temp',
    'Hum': 'humidity'
}

combined_df = combined_df.rename(columns=rename_map)
combined_df['created_at'] = pd.to_datetime(combined_df['created_at'])

print("\n" + "="*60)
print("Calculating alarm_status based on sensor thresholds...")
print("="*60)

def calculate_alarm(row):
    """
    Determine alarm status based on hazardous level thresholds:
    - PM2.5 > 100 μg/m³
    - PM10 > 230 μg/m³
    - Temperature > 35 °C
    - Humidity > 70 %
    - Gas (MQ-2) ≥ 176 ppm (Smoke/Combustible Gases)
    - Carbon Monoxide > 30 ppm (RA 8749 IRR)
    """
    alarm = 0
    
    if pd.notna(row.get('pm2_5')) and row['pm2_5'] > 100:
        alarm = 1
    elif pd.notna(row.get('pm10')) and row['pm10'] > 230:
        alarm = 1
    elif pd.notna(row.get('temp')) and row['temp'] > 35:
        alarm = 1
    elif pd.notna(row.get('humidity')) and row['humidity'] > 70:
        alarm = 1
    elif pd.notna(row.get('gas')) and row['gas'] >= 176:
        alarm = 1
    elif pd.notna(row.get('co')) and row['co'] > 30:
        alarm = 1
        
    return alarm

combined_df['alarm_status'] = combined_df.apply(calculate_alarm, axis=1)

# Reorder columns
column_order = ['created_at', 'pm2_5', 'pm10', 'temp', 'humidity', 'gas', 'co', 'alarm_status']
combined_df = combined_df[column_order]

# Save to combined_data.csv
output_path = os.path.join(dataset_folder, 'combined_data.csv')
combined_df.to_csv(output_path, index=False)

print(f"\n✓ Successfully created combined dataset!")
print(f"  Output: {output_path}")
print(f"  Total rows: {len(combined_df)}")
print(f"  Date range: {combined_df['created_at'].min()} to {combined_df['created_at'].max()}")

print(f"\nAlarm distribution:")
print(f"  No alarm (0): {(combined_df['alarm_status'] == 0).sum()} ({(combined_df['alarm_status'] == 0).sum()/len(combined_df)*100:.1f}%)")
print(f"  Alarm (1):    {(combined_df['alarm_status'] == 1).sum()} ({(combined_df['alarm_status'] == 1).sum()/len(combined_df)*100:.1f}%)")

print("\nData statistics:")
print(combined_df[['pm2_5', 'pm10', 'temp', 'humidity', 'gas', 'co']].describe())

print("\nFirst 10 rows:")
print(combined_df.head(10))

print("\nLast 10 rows:")
print(combined_df.tail(10))

print("\n" + "="*60)
print("Ready for model training!")
print("="*60)
