import os
import pandas as pd

# Dataset directory
dataset_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"

# Calibration constants
MQ2_OFFSET = 510.0
MQ7_OFFSET = 52.0

# Files to process
csv_files = [
    "combined_data.csv",
    "combined_dataset.csv",
]

def ppm_to_adc(ppm_value, offset, scale_factor):
    """Convert PPM to ADC value using inverse formula"""
    if pd.isna(ppm_value):
        return None
    try:
        adc = ((float(ppm_value) + offset) / scale_factor) * 4095.0
        return round(adc, 2)
    except:
        return None

# Process each CSV file
for csv_file in csv_files:
    file_path = os.path.join(dataset_dir, csv_file)
    
    if not os.path.exists(file_path):
        print(f"⚠️  File not found: {csv_file}")
        continue
    
    try:
        # Read CSV
        df = pd.read_csv(file_path)
        
        # Check if gas and co columns exist
        if "gas" in df.columns and "co" in df.columns:
            # Convert PPM to ADC
            df["MQ2_ADC"] = df["gas"].apply(lambda x: ppm_to_adc(x, MQ2_OFFSET, 1000.0))
            df["MQ7_ADC"] = df["co"].apply(lambda x: ppm_to_adc(x, MQ7_OFFSET, 100.0))
            
            # Drop original gas and co columns
            df = df.drop(columns=["gas", "co"])
            
            # Write back to CSV
            df.to_csv(file_path, index=False)
            
            # Display stats
            print(f"✅ Converted: {csv_file}")
            print(f"   MQ2_ADC - Min: {df['MQ2_ADC'].min():.2f}, Max: {df['MQ2_ADC'].max():.2f}, Mean: {df['MQ2_ADC'].mean():.2f}")
            print(f"   MQ7_ADC - Min: {df['MQ7_ADC'].min():.2f}, Max: {df['MQ7_ADC'].max():.2f}, Mean: {df['MQ7_ADC'].mean():.2f}")
            print(f"   Rows processed: {len(df)}")
        else:
            print(f"⚠️  No gas/co columns found in: {csv_file}")
            print(f"   Available columns: {df.columns.tolist()}")
    
    except Exception as e:
        print(f"❌ Error processing {csv_file}: {str(e)}")

print("\n✅ All combined files converted to ADC values!")
