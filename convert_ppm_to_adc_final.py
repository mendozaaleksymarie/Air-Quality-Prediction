import os
import pandas as pd

# Dataset directory
dataset_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"

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

def ppm_to_adc(ppm_value, scale_factor):
    """Convert PPM value to ADC"""
    if pd.isna(ppm_value):
        return None
    try:
        adc = (float(ppm_value) / scale_factor) * 4095.0
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

        # Check if MQ2_PPM and MQ7_PPM columns exist
        if "MQ2_PPM" in df.columns and "MQ7_PPM" in df.columns:
            # Convert PPM to ADC in-place
            df["MQ2_PPM"] = df["MQ2_PPM"].apply(lambda x: ppm_to_adc(x, 1000.0))
            df["MQ7_PPM"] = df["MQ7_PPM"].apply(lambda x: ppm_to_adc(x, 100.0))

            # Rename columns
            df = df.rename(columns={"MQ2_PPM": "MQ2_ADC", "MQ7_PPM": "MQ7_ADC"})

            # Write back to CSV
            df.to_csv(file_path, index=False)

            # Display stats
            print(f"✅ Converted: {csv_file}")
            print(f"   MQ2_ADC - Min: {df['MQ2_ADC'].min():.2f}, Max: {df['MQ2_ADC'].max():.2f}, Mean: {df['MQ2_ADC'].mean():.2f}")
            print(f"   MQ7_ADC - Min: {df['MQ7_ADC'].min():.2f}, Max: {df['MQ7_ADC'].max():.2f}, Mean: {df['MQ7_ADC'].mean():.2f}")
        else:
            print(f"⚠️  No PPM columns found in: {csv_file}")

    except Exception as e:
        print(f"❌ Error processing {csv_file}: {str(e)}")

print("\n✅ All CSV files converted from PPM to ADC!")
