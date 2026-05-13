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


def adc_to_ppm(adc_value, scale_factor):
    if pd.isna(adc_value):
        return None
    try:
        return round((float(adc_value) / 4095.0) * scale_factor, 2)
    except Exception:
        return None


for filename in FILES:
    path = os.path.join(DATASET_DIR, filename)
    if not os.path.exists(path):
        print(f"⚠️  Missing file: {filename}")
        continue

    df = pd.read_csv(path)
    if "MQ2_ADC" not in df.columns or "MQ7_ADC" not in df.columns:
        print(f"⚠️  Skipping {filename}: MQ2_ADC/MQ7_ADC not present")
        continue

    df["MQ2_ADC"] = df["MQ2_ADC"].apply(lambda x: adc_to_ppm(x, 1000.0))
    df["MQ7_ADC"] = df["MQ7_ADC"].apply(lambda x: adc_to_ppm(x, 100.0))
    df = df.rename(columns={"MQ2_ADC": "MQ2_PPM", "MQ7_ADC": "MQ7_PPM"})
    df.to_csv(path, index=False)

    print(f"✅ Converted {filename}: {len(df)} rows")

print("\n✅ Conversion complete.")