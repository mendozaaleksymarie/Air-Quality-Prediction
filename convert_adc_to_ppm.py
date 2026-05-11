import pandas as pd
import os
import glob

# Dataset folder path
dataset_folder = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"

# Get all CSV files
csv_files = glob.glob(os.path.join(dataset_folder, "*.csv"))

print(f"Found {len(csv_files)} CSV files")

for csv_file in csv_files:
    filename = os.path.basename(csv_file)
    print(f"\nProcessing: {filename}")
    
    try:
        # Read CSV
        df = pd.read_csv(csv_file)
        
        # Check if MQ2_ADC and MQ7_ADC columns exist
        if "MQ2_ADC" in df.columns and "MQ7_ADC" in df.columns:
            # Convert ADC to PPM
            df["MQ2_PPM"] = (df["MQ2_ADC"] / 4095.0) * 1000.0
            df["MQ7_PPM"] = (df["MQ7_ADC"] / 4095.0) * 100.0
            
            # Save the updated CSV
            df.to_csv(csv_file, index=False)
            
            print(f"✓ Updated successfully")
            print(f"  - Rows: {len(df)}")
            print(f"  - MQ2_PPM range: {df['MQ2_PPM'].min():.2f} - {df['MQ2_PPM'].max():.2f}")
            print(f"  - MQ7_PPM range: {df['MQ7_PPM'].min():.2f} - {df['MQ7_PPM'].max():.2f}")
        else:
            print(f"⚠ Skipped - Missing MQ2_ADC or MQ7_ADC columns")
            if "MQ2_ADC" in df.columns:
                print(f"  Columns: {list(df.columns)}")
    
    except Exception as e:
        print(f"✗ Error: {str(e)}")

print("\n✓ Conversion complete!")
