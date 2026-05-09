#!/usr/bin/env python3
"""Convert MQ2 gas readings to PPM in-place for combined_data.csv.

This script replaces the values in the `gas` column with the computed
PPM using constants from the project PDF (RL=10kΩ, R0=24,539.77Ω).

Usage: python scripts/convert_combined_data_gas.py
"""
import csv
from pathlib import Path
import tempfile
import os

# Constants (from project PDF) — UPDATED: RL=10kΩ, R0=24,539.77Ω
ADC_MAX = 4095.0
VIN = 5.0
RL = 10000.0  # Load resistor changed to 10kΩ
R0 = 24539.77  # R0 recalibrated (halved proportionally)
A = 3616.1
B = -2.675

DATASET_DIR = Path('dataset')

def convert_adc_to_ppm(adc_value):
    try:
        adc = float(adc_value)
    except Exception:
        return None

    vout = (adc / ADC_MAX) * VIN
    if vout <= 0:
        return 0.0

    rs = ((VIN - vout) / vout) * RL
    ratio = rs / R0
    try:
        ppm = A * (ratio ** B)
    except Exception:
        return None
    return ppm

def process_combined_data():
    csv_path = DATASET_DIR / 'combined_data.csv'
    
    if not csv_path.exists():
        print(f"Error: {csv_path} not found")
        return
    
    # Create temporary file
    fd, tmpname = tempfile.mkstemp(prefix='combined_data_tmp_', suffix='.csv', dir=csv_path.parent)
    os.close(fd)
    tmp_path = Path(tmpname)
    
    processed = 0
    try:
        with csv_path.open('r', newline='', encoding='utf-8') as fr:
            reader = csv.DictReader(fr)
            
            # Check if 'gas' column exists
            if reader.fieldnames is None or 'gas' not in reader.fieldnames:
                print(f"Error: 'gas' column not found in {csv_path}")
                tmp_path.unlink()
                return
            
            # Write to temp file with converted values
            with tmp_path.open('w', newline='', encoding='utf-8') as fw:
                writer = csv.DictWriter(fw, fieldnames=reader.fieldnames)
                writer.writeheader()
                
                for row in reader:
                    # Convert gas value to PPM
                    try:
                        ppm = convert_adc_to_ppm(row['gas'])
                        if ppm is not None:
                            row['gas'] = ppm
                            processed += 1
                    except Exception:
                        pass
                    
                    writer.writerow(row)
        
        # Replace original file with temp file
        csv_path.unlink()
        tmp_path.rename(csv_path)
        
        print(f"Updated {processed} gas values in combined_data.csv")
    
    except Exception as e:
        print(f"Error processing combined_data.csv: {e}")
        if tmp_path.exists():
            tmp_path.unlink()

if __name__ == '__main__':
    process_combined_data()
