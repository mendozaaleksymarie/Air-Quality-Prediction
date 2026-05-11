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
    "TRAINING SIMULATION DATA - Hazardous - Combustion .csv",
    "TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv",
    "TRAINING SIMULATION DATA - Hazardous - Pure Dust.csv",
    "TRAINING SIMULATION DATA - Hazardous - VOC.csv",
    "TRAINING SIMULATION DATA - Safe - Clean Air (High Humidity).csv",
    "TRAINING SIMULATION DATA - Safe - Clean Air.csv",
    "TRAINING SIMULATION DATA - Safe - Misting.csv",
]

def ppm_to_adc(ppm_value, offset, scale_factor):
    """Convert PPM back to ADC value (inverse formula)"""
    if pd.isna(ppm_value):
        return None
    try:
        adc = ((float(ppm_value) + offset) / scale_factor) * 4095.0
        return adc
    except:
        return None

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
        
        # Check if MQ2_ppm and MQ7_ppm columns exist
        if "MQ2_ppm" in df.columns and "MQ7_ppm" in df.columns:
            # Reverse PPM to ADC
            mq2_adc = df["MQ2_ppm"].apply(lambda x: ppm_to_adc(x, MQ2_OFFSET, 1000.0))
            mq7_adc = df["MQ7_ppm"].apply(lambda x: ppm_to_adc(x, MQ7_OFFSET, 100.0))
            
            # Convert ADC back to PPM using the formula
            df["MQ2_ppm"] = mq2_adc.apply(lambda x: adc_to_ppm(x, MQ2_OFFSET, 1000.0))
            df["MQ7_ppm"] = mq7_adc.apply(lambda x: adc_to_ppm(x, MQ7_OFFSET, 100.0))
            
            # Write back to CSV
            df.to_csv(file_path, index=False)
            
            # Display stats
            print(f"✅ Standardized: {csv_file}")
            print(f"   MQ2_ppm - Min: {df['MQ2_ppm'].min():.2f}, Max: {df['MQ2_ppm'].max():.2f}, Mean: {df['MQ2_ppm'].mean():.2f}")
            print(f"   MQ7_ppm - Min: {df['MQ7_ppm'].min():.2f}, Max: {df['MQ7_ppm'].max():.2f}, Mean: {df['MQ7_ppm'].mean():.2f}")
        else:
            print(f"⚠️  No MQ columns found in: {csv_file}")
    
    except Exception as e:
        print(f"❌ Error processing {csv_file}: {str(e)}")

print("\n✅ All CSV files standardized with your calibration formulas!")
