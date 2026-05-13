import os
import pandas as pd

# Dataset directory
dataset_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"

# Calibration constants
MQ2_OFFSET = 510.0
MQ7_OFFSET = 52.0

# List of CSV files to process
csv_files = [
    "03-16-2026 (Inside of Temfacil).csv",
    "03-17-2026 (Warehouse).csv",
    "03-18-2026 (Outside of Temfacil).csv",
    "03-19-2026 (Fabrication Area).csv",
    "03-30-2026 (Active Floor Area).csv",
    "combined_data.csv",
    "combined_dataset.csv",
    "TRAINING SIMULATION DATA - Hazardous - Combustion .csv",
    "TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv",
    "TRAINING SIMULATION DATA - Hazardous - Pure Dust.csv",
    "TRAINING SIMULATION DATA - Hazardous - VOC.csv",
    "TRAINING SIMULATION DATA - Safe - Clean Air (High Humidity).csv",
    "TRAINING SIMULATION DATA - Safe - Clean Air.csv",
    "TRAINING SIMULATION DATA - Safe - Misting.csv",
]

def adc_to_ppm(adc_value, offset, scale_factor):
    """Convert ADC value to PPM"""
    if pd.isna(adc_value):
        return None
    try:
        ppm = ((float(adc_value) / 4095.0) * scale_factor) - offset
        return round(ppm, 2)
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
        
        # Check if MQ2_ADC and MQ7_ADC columns exist
        if "MQ2_ADC" in df.columns and "MQ7_ADC" in df.columns:
            # Convert ADC to PPM
            df["MQ2_ppm"] = df["MQ2_ADC"].apply(lambda x: adc_to_ppm(x, MQ2_OFFSET, 1000.0))
            df["MQ7_ppm"] = df["MQ7_ADC"].apply(lambda x: adc_to_ppm(x, MQ7_OFFSET, 100.0))
            
            # Drop ADC columns
            df = df.drop(columns=["MQ2_ADC", "MQ7_ADC"])
            
            # Reorder columns: move PPM columns after PM10
            cols = list(df.columns)
            if "PM10" in cols:
                pm10_idx = cols.index("PM10")
                cols.remove("MQ2_ppm")
                cols.remove("MQ7_ppm")
                cols.insert(pm10_idx + 1, "MQ2_ppm")
                cols.insert(pm10_idx + 2, "MQ7_ppm")
                df = df[cols]
            
            # Write back to CSV
            df.to_csv(file_path, index=False)
            
            # Display stats
            print(f"✅ Reverted: {csv_file}")
            print(f"   MQ2_ppm - Min: {df['MQ2_ppm'].min():.2f}, Max: {df['MQ2_ppm'].max():.2f}, Mean: {df['MQ2_ppm'].mean():.2f}")
            print(f"   MQ7_ppm - Min: {df['MQ7_ppm'].min():.2f}, Max: {df['MQ7_ppm'].max():.2f}, Mean: {df['MQ7_ppm'].mean():.2f}")
        else:
            print(f"⚠️  No ADC columns found in: {csv_file}")
    
    except Exception as e:
        print(f"❌ Error processing {csv_file}: {str(e)}")

print("\n✅ All CSV files reverted to PPM format!")
