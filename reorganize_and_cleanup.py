import pandas as pd
import os

dataset_folder = 'dataset'
csv_files = [f for f in os.listdir(dataset_folder) if f.endswith('.csv')]

files_to_delete = []
files_to_reorder = []

# Identify files to delete and files to reorder
for filename in sorted(csv_files):
    filepath = os.path.join(dataset_folder, filename)
    df = pd.read_csv(filepath)
    
    if 'MQ2_ADC' in df.columns:
        files_to_delete.append(filepath)
    elif 'MQ2' in df.columns:
        files_to_reorder.append((filename, filepath))

# Delete files with MQ2_ADC
print(f"Deleting {len(files_to_delete)} files with MQ2_ADC:\n")
for filepath in files_to_delete:
    try:
        os.remove(filepath)
        print(f"✓ Deleted: {os.path.basename(filepath)}")
    except Exception as e:
        print(f"✗ Error deleting {os.path.basename(filepath)}: {str(e)}")

# Reorder columns in MQ2 (PPM) files - MQ2 should come after PM10
print(f"\nReordering columns in {len(files_to_reorder)} files (MQ2 after PM10):\n")
for filename, filepath in files_to_reorder:
    try:
        df = pd.read_csv(filepath)
        cols = list(df.columns)
        
        # Get PM10 index
        if 'PM10' in cols:
            pm10_idx = cols.index('PM10')
            # Remove MQ2 from current position
            cols.remove('MQ2')
            # Insert MQ2 right after PM10
            cols.insert(pm10_idx + 1, 'MQ2')
            # Reorder dataframe
            df = df[cols]
            # Save back
            df.to_csv(filepath, index=False)
            print(f"✓ {filename}")
            print(f"  Columns: {', '.join(cols[:8])}...")
        else:
            print(f"⚠️  Skip {filename} - PM10 column not found")
    except Exception as e:
        print(f"✗ Error reordering {filename}: {str(e)}")

print(f"\nDone!")
