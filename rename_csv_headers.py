import pandas as pd
import glob
import os
from pathlib import Path

dataset_path = Path(r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset")

print("=" * 80)
print("Renaming CSV Column Headers: MQ2_PPM → Gas, MQ7_PPM → CO")
print("=" * 80)
print()

# Get all CSV files
csv_files = sorted([f for f in dataset_path.glob("*.csv")])
print(f"Found {len(csv_files)} CSV file(s) to process\n")

success_count = 0
skip_count = 0

for csv_file in csv_files:
    filename = csv_file.name
    try:
        # Read CSV
        df = pd.read_csv(csv_file)
        
        # Track if changes were made
        changes_made = False
        
        # Rename columns
        if 'MQ2_PPM' in df.columns:
            df.rename(columns={'MQ2_PPM': 'Gas'}, inplace=True)
            changes_made = True
        
        if 'MQ7_PPM' in df.columns:
            df.rename(columns={'MQ7_PPM': 'CO'}, inplace=True)
            changes_made = True
        
        if changes_made:
            # Save CSV
            df.to_csv(csv_file, index=False)
            print(f"✓ Updated: {filename}")
            success_count += 1
        else:
            print(f"⊘ Skipped: {filename} (no MQ2_PPM/MQ7_PPM columns)")
            skip_count += 1
            
    except Exception as e:
        print(f"✗ Error: {filename} - {str(e)}")

print()
print("=" * 80)
print(f"Rename Summary: {success_count} updated, {skip_count} skipped")
print("=" * 80)
print()

# Verify by checking first file
if csv_files:
    df_check = pd.read_csv(csv_files[0])
    print("Verification - Columns in first file:")
    print(list(df_check.columns))
