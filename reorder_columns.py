import pandas as pd
from pathlib import Path

# Define dataset directory
dataset_dir = 'dataset'

# Get all CSV files in dataset folder
csv_files = list(Path(dataset_dir).glob('*.csv'))

print("Reordering columns to place MQ2_PPM and MQ7_PPM next to PM10...\n")

# Process all CSV files
for file_path in sorted(csv_files):
    try:
        df = pd.read_csv(file_path)
        
        # Define new column order based on current columns
        cols = df.columns.tolist()
        
        # Remove MQ2_PPM and MQ7_PPM from their current positions
        if 'MQ2_PPM' in cols:
            cols.remove('MQ2_PPM')
        if 'MQ7_PPM' in cols:
            cols.remove('MQ7_PPM')
        
        # Find PM10 position and insert MQ2_PPM and MQ7_PPM after it
        if 'PM10' in cols:
            pm10_idx = cols.index('PM10')
            cols.insert(pm10_idx + 1, 'MQ2_PPM')
            cols.insert(pm10_idx + 2, 'MQ7_PPM')
        else:
            # Fallback: just add them at the end
            cols.extend(['MQ2_PPM', 'MQ7_PPM'])
        
        # Reorder dataframe
        df = df[cols]
        
        # Save back to file
        df.to_csv(file_path, index=False)
        
        print(f"✅ {file_path.name}")
        print(f"   Column order: {', '.join(cols)}")
        
    except Exception as e:
        print(f"❌ {file_path.name}: Error - {str(e)}")

print("\n✅ Column reordering complete!")
