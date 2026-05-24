import pandas as pd
import os
from pathlib import Path

# Constants
Vin = 3.3  # Reference voltage
ADC_max = 4095  # 12-bit ADC
RL = 10000  # Load resistance in ohms
Ro = 2120  # Clean air resistance in ohms

def convert_mq7_adc_to_ppm(adc_value):
    """
    Convert MQ7 ADC value to PPM using the formula chain:
    Step 1: Vout = MQ7_ADC × (3.3 / 4095)
    Step 2: Rs = 10,000 × (3.3 - Vout) / Vout
    Step 3: ratio = Rs / 2120
    Step 4: MQ7_PPM = 99.042 × ratio^(-1.518)
    """
    try:
        # Step 1: Calculate Vout
        Vout = adc_value * (Vin / ADC_max)
        
        # Step 2: Calculate Rs
        if Vout <= 0:
            return 0.0
        Rs = RL * (Vin - Vout) / Vout
        
        # Step 3: Calculate ratio
        ratio = Rs / Ro
        
        # Step 4: Calculate MQ7_PPM
        ppm = 99.042 * (ratio ** (-1.518))
        
        # Round to 2 decimal places
        return round(ppm, 2)
    except Exception as e:
        print(f"Error converting ADC value {adc_value}: {e}")
        return 0.0


def process_csv_file(file_path):
    """
    Process a single CSV file to convert MQ7_ADC to MQ7_PPM
    """
    try:
        # Read the CSV file
        df = pd.read_csv(file_path)
        
        # Check if MQ7_ADC column exists
        if 'MQ7_ADC' not in df.columns:
            print(f"✗ Skipped: {os.path.basename(file_path)} (no MQ7_ADC column)")
            return False
        
        # Convert MQ7_ADC to MQ7_PPM
        df['MQ7_ADC'] = df['MQ7_ADC'].apply(convert_mq7_adc_to_ppm)
        
        # Rename the column
        df = df.rename(columns={'MQ7_ADC': 'MQ7_PPM'})
        
        # Save the updated CSV
        df.to_csv(file_path, index=False)
        print(f"✓ Converted: {os.path.basename(file_path)}")
        return True
        
    except Exception as e:
        print(f"✗ Error processing {os.path.basename(file_path)}: {e}")
        return False


def main():
    dataset_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset"
    
    print("=" * 70)
    print("MQ7 ADC to PPM Conversion Tool")
    print("=" * 70)
    print()
    
    # Get all CSV files in the dataset directory
    csv_files = list(Path(dataset_dir).glob("*.csv"))
    csv_files = sorted([f for f in csv_files if f.is_file()])
    
    if not csv_files:
        print("No CSV files found in dataset directory.")
        return
    
    print(f"Found {len(csv_files)} CSV file(s) to process:\n")
    
    converted_count = 0
    skipped_count = 0
    
    for csv_file in csv_files:
        if process_csv_file(str(csv_file)):
            converted_count += 1
        else:
            skipped_count += 1
    
    print()
    print("=" * 70)
    print(f"Conversion Summary: {converted_count} converted, {skipped_count} skipped")
    print("=" * 70)
    print()
    
    # Check combined_data.csv for columns affected by this change
    combined_data_path = os.path.join(dataset_dir, "combined_data.csv")
    if os.path.exists(combined_data_path):
        print("Note: combined_data.csv has been processed if it contained MQ7_ADC column.")
        print("Please review if any derived columns need recalculation.")


if __name__ == "__main__":
    main()
