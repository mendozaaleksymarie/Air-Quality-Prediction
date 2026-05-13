import os
import pandas as pd

dataset_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"
MQ2_OFFSET = 510.0
MQ7_OFFSET = 52.0

csv_files = [
    "03-16-2026 (Inside of Temfacil).csv",
    "03-17-2026 (Warehouse).csv",
]

def adc_to_ppm(adc_value, offset, scale_factor):
    if pd.isna(adc_value):
        return None
    try:
        ppm = ((float(adc_value) / 4095.0) * scale_factor) - offset
        return round(ppm, 2)
    except:
        return None

for csv_file in csv_files:
    file_path = os.path.join(dataset_dir, csv_file)
    if not os.path.exists(file_path):
        continue
    
    df = pd.read_csv(file_path)
    
    if "MQ2_ADC" in df.columns and "MQ7_ADC" in df.columns:
        df["MQ2_ppm"] = df["MQ2_ADC"].apply(lambda x: adc_to_ppm(x, MQ2_OFFSET, 1000.0))
        df["MQ7_ppm"] = df["MQ7_ADC"].apply(lambda x: adc_to_ppm(x, MQ7_OFFSET, 100.0))
        df = df.drop(columns=["MQ2_ADC", "MQ7_ADC"])
        cols = list(df.columns)
        if "PM10" in cols:
            pm10_idx = cols.index("PM10")
            cols.remove("MQ2_ppm")
            cols.remove("MQ7_ppm")
            cols.insert(pm10_idx + 1, "MQ2_ppm")
            cols.insert(pm10_idx + 2, "MQ7_ppm")
            df = df[cols]
        df.to_csv(file_path, index=False)
        print("Reverted: " + csv_file)
