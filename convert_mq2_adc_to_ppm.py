import pandas as pd
import numpy as np
import os
from pathlib import Path

# Constants
RL_VALUE = 10  # Load resistance in kΩ
ADC_MAX = 4095  # 12-bit ADC maximum value
RO_VALUE = 0.9474  # Calibrated baseline resistance in clean air (kΩ)

# Smoke PPM curve constants
PCURVE_0 = 2.3
PCURVE_1 = 0.53
PCURVE_2 = -0.44

def adc_to_ppm(adc_value):
    """
    Convert MQ2 ADC value to Smoke PPM using the formula chain:
    Step 1: ADC → Rs (Sensor Resistance)
    Step 2: Rs/Ro Ratio
    Step 3: Ratio → Smoke PPM
    """
    try:
        # Step 1: ADC to Rs
        rs = RL_VALUE * (ADC_MAX - adc_value) / adc_value
        
        # Step 2: Rs/Ro ratio
        ratio = rs / RO_VALUE
        
        # Step 3: Ratio to Smoke PPM
        # ppm = 10 ^ ( (log10(ratio) - pcurve[1]) / pcurve[2] + pcurve[0] )
        ppm = 10 ** ((np.log10(ratio) - PCURVE_1) / PCURVE_2 + PCURVE_0)
        
        return round(ppm, 2)
    except (ValueError, ZeroDivisionError):
        return np.nan

def convert_csv_file(file_path):
    """Convert MQ2_ADC to MQ2_PPM in a CSV file"""
    try:
        print(f"Processing: {file_path}")
        
        # Read the CSV file
        df = pd.read_csv(file_path)
        
        # Check if MQ2_ADC column exists
        if 'MQ2_ADC' not in df.columns:
            print(f"  ⚠ Skipping: No MQ2_ADC column found")
            return False
        
        # Convert MQ2_ADC to MQ2_PPM
        df['MQ2_ADC'] = df['MQ2_ADC'].apply(adc_to_ppm)
        
        # Rename the column header
        df.rename(columns={'MQ2_ADC': 'MQ2_PPM'}, inplace=True)
        
        # Save the modified CSV
        df.to_csv(file_path, index=False)
        
        print(f"  ✓ Successfully converted and saved")
        return True
        
    except Exception as e:
        print(f"  ✗ Error: {str(e)}")
        return False

def process_all_csv_files(dataset_folder):
    """Process all CSV files in the dataset folder"""
    csv_files = list(Path(dataset_folder).glob("*.csv"))
    
    if not csv_files:
        print("No CSV files found in the dataset folder")
        return
    
    print(f"Found {len(csv_files)} CSV files\n")
    
    successful = 0
    failed = 0
    skipped = 0
    
    for csv_file in sorted(csv_files):
        if convert_csv_file(str(csv_file)):
            successful += 1
        else:
            failed += 1
    
    print(f"\n{'='*60}")
    print(f"Conversion Summary:")
    print(f"  Successful: {successful}")
    print(f"  Failed: {failed}")
    print(f"  Total: {len(csv_files)}")
    print(f"{'='*60}")

if __name__ == "__main__":
    dataset_folder = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"
    process_all_csv_files(dataset_folder)
