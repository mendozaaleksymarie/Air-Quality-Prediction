import pandas as pd
import os
from pathlib import Path

# Read the reference file with correct MQ7_ADC values
ref_file = r'c:\Users\MAKI\Downloads\combined_dataset_with_MQ2_PPM.csv'
ref_df = pd.read_csv(ref_file)

# Create mapping of timestamp to MQ7_ADC
timestamp_to_adc = dict(zip(ref_df['Timestamp'], ref_df['MQ7_ADC']))

print(f"Reference file loaded with {len(timestamp_to_adc)} timestamp-MQ7_ADC mappings")
print(f"Sample mappings: {list(timestamp_to_adc.items())[:3]}")

# Get all CSV files in the dataset folder
dataset_folder = 'dataset'
csv_files = [f for f in os.listdir(dataset_folder) if f.endswith('.csv')]
print(f"\nFound {len(csv_files)} CSV files in dataset folder")

# Track updates
updated_files = []
failed_files = []

# Process each CSV file
for csv_file in sorted(csv_files):
    file_path = os.path.join(dataset_folder, csv_file)
    try:
        print(f"\nProcessing: {csv_file}")
        df = pd.read_csv(file_path)
        
        if 'MQ7_PPM' not in df.columns:
            print(f"  ⚠ Skipping - no MQ7_PPM column")
            continue
            
        if 'Timestamp' not in df.columns:
            print(f"  ⚠ Skipping - no Timestamp column")
            continue
        
        # Replace MQ7_PPM with MQ7_ADC values
        replaced_count = 0
        for idx, row in df.iterrows():
            timestamp = row['Timestamp']
            if timestamp in timestamp_to_adc:
                df.at[idx, 'MQ7_PPM'] = timestamp_to_adc[timestamp]
                replaced_count += 1
        
        # Save the updated file
        df.to_csv(file_path, index=False)
        print(f"  ✓ Replaced {replaced_count} values out of {len(df)} rows")
        updated_files.append((csv_file, replaced_count))
        
    except Exception as e:
        print(f"  ✗ Error: {e}")
        failed_files.append((csv_file, str(e)))

print("\n" + "="*60)
print("SUMMARY")
print("="*60)
print(f"Successfully updated: {len(updated_files)} files")
for fname, count in updated_files:
    print(f"  - {fname}: {count} values replaced")

if failed_files:
    print(f"\nFailed: {len(failed_files)} files")
    for fname, error in failed_files:
        print(f"  - {fname}: {error}")

# Now update combined_data.csv
print("\n" + "="*60)
print("Updating combined_data.csv...")
print("="*60)

try:
    combined_path = os.path.join(dataset_folder, 'combined_data.csv')
    if os.path.exists(combined_path):
        combined_df = pd.read_csv(combined_path)
        if 'MQ7_PPM' in combined_df.columns and 'Timestamp' in combined_df.columns:
            replaced_count = 0
            for idx, row in combined_df.iterrows():
                timestamp = row['Timestamp']
                if timestamp in timestamp_to_adc:
                    combined_df.at[idx, 'MQ7_PPM'] = timestamp_to_adc[timestamp]
                    replaced_count += 1
            
            combined_df.to_csv(combined_path, index=False)
            print(f"✓ combined_data.csv updated: {replaced_count} values replaced out of {len(combined_df)} rows")
        else:
            print("⚠ combined_data.csv is missing MQ7_PPM or Timestamp column")
    else:
        print("⚠ combined_data.csv not found")
except Exception as e:
    print(f"✗ Error updating combined_data.csv: {e}")

print("\n✓ All operations completed!")
