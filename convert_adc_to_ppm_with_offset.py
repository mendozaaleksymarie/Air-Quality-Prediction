import os
import pandas as pd

DATASET_DIR = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"

FILES = [
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


def adc_to_ppm_mq2(adc_value):
    if pd.isna(adc_value):
        return None
    try:
        return round(((float(adc_value) / 4095.0) * 1000.0) - 510.0, 2)
    except Exception:
        return None


def adc_to_ppm_mq7(adc_value):
    if pd.isna(adc_value):
        return None
    try:
        return round(((float(adc_value) / 4095.0) * 100.0) - 52.0, 2)
    except Exception:
        return None


for filename in FILES:
    path = os.path.join(DATASET_DIR, filename)
    if not os.path.exists(path):
        print(f"⚠️  Missing: {filename}")
        continue

    df = pd.read_csv(path)
    if "MQ2_ADC" not in df.columns or "MQ7_ADC" not in df.columns:
        print(f"⚠️  Skipping {filename}: ADC columns not found")
        continue

    df["MQ2_ADC"] = df["MQ2_ADC"].apply(adc_to_ppm_mq2)
    df["MQ7_ADC"] = df["MQ7_ADC"].apply(adc_to_ppm_mq7)
    df = df.rename(columns={"MQ2_ADC": "MQ2_PPM", "MQ7_ADC": "MQ7_PPM"})
    df.to_csv(path, index=False)

    print(f"✅ Converted {filename}: {len(df)} rows")
    print(f"   MQ2_PPM range: {df['MQ2_PPM'].min():.2f} - {df['MQ2_PPM'].max():.2f}")
    print(f"   MQ7_PPM range: {df['MQ7_PPM'].min():.2f} - {df['MQ7_PPM'].max():.2f}")

print("\n✅ All conversions complete.")
