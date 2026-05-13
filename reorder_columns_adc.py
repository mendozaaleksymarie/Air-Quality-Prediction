import pandas as pd
from pathlib import Path

# Define dataset directory
dataset_dir = 'dataset'

# Get all CSV files in dataset folder
csv_files = list(Path(dataset_dir).glob('*.csv'))

print("Reordering columns to place MQ2_ADC and MQ7_ADC next to PM10...\n")

# Process all CSV files
for file_path in sorted(csv_files):
    try:
        df = pd.read_csv(file_path)
        
        # Define new column order based on current columns
        cols = df.columns.tolist()
        
        # Remove MQ2_ADC and MQ7_ADC from their current positions (if they exist)
        if 'MQ2_ADC' in cols:
            cols.remove('MQ2_ADC')
        if 'MQ7_ADC' in cols:
            cols.remove('MQ7_ADC')
        
        # Find PM10 position and insert MQ2_ADC and MQ7_ADC after it
        if 'PM10' in cols:
            pm10_idx = cols.index('PM10')
            cols.insert(pm10_idx + 1, 'MQ2_ADC')
            cols.insert(pm10_idx + 2, 'MQ7_ADC')
        else:
            # Fallback: just add them at the end
            cols.extend(['MQ2_ADC', 'MQ7_ADC'])
        
        # Reorder dataframe
        df = df[cols]
        
        # Save back to file
        df.to_csv(file_path, index=False)
        
        print(f"✅ {file_path.name}")
        print(f"   Column order: {', '.join(cols)}")
        
    except Exception as e:
        print(f"❌ {file_path.name}: Error - {str(e)}")

print("\n✅ Column reordering complete!")
