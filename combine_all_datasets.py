import pandas as pd
import os
import glob

# Define dataset folder path
dataset_folder = 'dataset'

# Get all CSV files in the dataset folder
csv_files = glob.glob(os.path.join(dataset_folder, '*.csv'))

# Remove combined_data.csv and combined_dataset.csv if they exist (to avoid circular references)
csv_files = [f for f in csv_files if 'combined_data.csv' not in f and 'combined_dataset.csv' not in f]

print(f"Found {len(csv_files)} CSV files to combine:\n")

all_dataframes = []

# Read each CSV file and add to list
for file_path in sorted(csv_files):
    filename = os.path.basename(file_path)
    try:
        df = pd.read_csv(file_path)
        all_dataframes.append(df)
        print(f"✓ {filename}: {len(df)} rows, {len(df.columns)} columns")
    except Exception as e:
        print(f"✗ {filename}: Error - {str(e)}")

# Combine all dataframes
if all_dataframes:
    combined_df = pd.concat(all_dataframes, ignore_index=True)
    
    # Save to new CSV file
    output_path = os.path.join(dataset_folder, 'combined_dataset.csv')
    combined_df.to_csv(output_path, index=False)
    
    print(f"\n{'='*60}")
    print(f"✓ Combined dataset created successfully!")
    print(f"{'='*60}")
    print(f"Output file: {output_path}")
    print(f"Total rows: {len(combined_df)}")
    print(f"Total columns: {len(combined_df.columns)}")
    print(f"\nColumns: {list(combined_df.columns)}")
    print(f"\nDataset info:")
    print(combined_df.info())
else:
    print("No CSV files found to combine!")
