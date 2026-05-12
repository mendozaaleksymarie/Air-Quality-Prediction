import pandas as pd
import os

dataset_folder = 'dataset'
csv_files = [f for f in os.listdir(dataset_folder) if f.endswith('.csv')]

print("Checking column structure in files:\n")
for filename in sorted(csv_files):
    filepath = os.path.join(dataset_folder, filename)
    df = pd.read_csv(filepath)
    cols = list(df.columns)
    has_mq2_adc = 'MQ2_ADC' in cols
    has_mq2 = 'MQ2' in cols
    status = "MQ2_ADC" if has_mq2_adc else ("MQ2 (PPM)" if has_mq2 else "NO MQ2")
    print(f"{status:15} | {filename}")
