import pandas as pd
import numpy as np
from pathlib import Path

# Constants for conversion (ADC → PPM) - NEW FORMULA
VIN = 3.3
ADC_MAX = 4095
RL = 10000
RO = 1822  # Updated from 2120 to 1822
COEFF = 99.042
EXPONENT = -1.518

def convert_adc_to_ppm(adc_value):
    """Convert MQ7_ADC to MQ7_PPM using forward formula"""
    try:
        # Step 1: Vout = MQ7_ADC × (3.3 / 4095)
        vout = adc_value * (VIN / ADC_MAX)
        
        # Step 2: Rs = 10,000 × (3.3 - Vout) / Vout
        rs = RL * (VIN - vout) / vout
        
        # Step 3: ratio = Rs / 1822
        ratio = rs / RO
        
        # Step 4: MQ7_PPM = 99.042 × ratio^(-1.518)
        ppm = COEFF * pow(ratio, EXPONENT)
        
        # Handle negative values
        if ppm < 0:
            ppm = 0.0
        
        return round(ppm, 2)
    except Exception:
        return np.nan


def process_csv_file(file_path):
    """Process a single CSV file: convert MQ7 values to MQ7_PPM using new formula"""
    try:
        df = pd.read_csv(file_path)
        
        # Check for MQ7_PPM or MQ7_ADC column
        if 'MQ7_PPM' in df.columns:
            col_name = 'MQ7_PPM'
        elif 'MQ7_ADC' in df.columns:
            col_name = 'MQ7_ADC'
        else:
            return False, "No MQ7_PPM or MQ7_ADC column found"
        
        # Convert values
        df[col_name] = df[col_name].apply(convert_adc_to_ppm)
        
        # Rename column to MQ7_PPM if not already
        if col_name == 'MQ7_ADC':
            df.rename(columns={'MQ7_ADC': 'MQ7_PPM'}, inplace=True)
        
        # Save file
        df.to_csv(file_path, index=False)
        return True, None
    except Exception as e:
        return False, str(e)


def process_all_csv_files():
    """Process all CSV files in dataset folder"""
    dataset_path = Path(r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset")
    
    print("=" * 80)
    print("MQ7 ADC to PPM Conversion Tool (R₀ = 1822)")
    print("=" * 80)
    print()
    
    # Get all CSV files
    csv_files = sorted([f for f in dataset_path.glob("*.csv")])
    print(f"Found {len(csv_files)} CSV file(s) to process:")
    print()
    
    success_count = 0
    skip_count = 0
    error_count = 0
    
    for csv_file in csv_files:
        filename = csv_file.name
        success, error = process_csv_file(csv_file)
        
        if success:
            print(f"✓ Converted: {filename}")
            success_count += 1
        elif error:
            print(f"⚠ Skipped: {filename} ({error})")
            skip_count += 1
        else:
            print(f"✗ Error: {filename}")
            error_count += 1
    
    print()
    print("=" * 80)
    print(f"Conversion Summary: {success_count} converted, {skip_count} skipped, {error_count} errors")
    print("=" * 80)
    print()
    
    return success_count, skip_count, error_count


if __name__ == "__main__":
    process_all_csv_files()
