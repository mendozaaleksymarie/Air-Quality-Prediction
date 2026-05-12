import pandas as pd
import os
import numpy as np

# Conversion parameters
RL = 10  # Load resistance in kΩ
ADC_MAX = 4095
Ro = 0.75  # Baseline resistance in kΩ
pcurve_smoke = [2.3, 0.53, -0.44]  # [a, b, c] for smoke

# Function to convert ADC to PPM for smoke
def adc_to_ppm_smoke(adc_value):
    # Step 1: ADC to Rs
    rs = RL * (ADC_MAX - adc_value) / adc_value
    
    # Step 2: Rs/Ro ratio
    ratio = rs / Ro
    
    # Step 3: Ratio to PPM using log-log formula
    # ppm = 10^((log10(ratio) - b) / c + a)
    ppm = 10 ** ((np.log10(ratio) - pcurve_smoke[1]) / pcurve_smoke[2] + pcurve_smoke[0])
    
    return ppm

# Get all CSV files in dataset folder (excluding _with_smoke_ppm files)
dataset_folder = 'dataset'
csv_files = [f for f in os.listdir(dataset_folder) if f.endswith('.csv') and '_with_smoke_ppm' not in f]

print(f'Processing {len(csv_files)} CSV files...\n')

for filename in sorted(csv_files):
    filepath = os.path.join(dataset_folder, filename)
    
    try:
        # Read CSV
        df = pd.read_csv(filepath)
        
        # Check if MQ2_ADC column exists
        if 'MQ2_ADC' not in df.columns:
            print(f'⚠️  SKIP: {filename} - MQ2_ADC column not found')
            continue
        
        # Convert MQ2_ADC to PPM
        df['MQ2'] = df['MQ2_ADC'].apply(adc_to_ppm_smoke)
        
        # Remove the original MQ2_ADC column
        df = df.drop('MQ2_ADC', axis=1)
        
        # Save back to the same file
        df.to_csv(filepath, index=False)
        
        print(f'✓ {filename}')
        print(f'  - Rows: {len(df)}, MQ2 PPM range: {df["MQ2"].min():.2f} - {df["MQ2"].max():.2f}')
        
    except Exception as e:
        print(f'✗ ERROR in {filename}: {str(e)}')

print(f'\nConversion complete!')
