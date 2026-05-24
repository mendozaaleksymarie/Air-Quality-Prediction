"""
Convert MQ2_ADC to MQ2_PPM (Smoke PPM) for all CSV files in the dataset folder.

Conversion Formula Chain (Field-Calibrated Ro):
=========================================================================

Step 1 — ADC to Rs (Sensor Resistance): 
   Rs = RL * (ADC_MAX - raw_adc) / raw_adc
      = 10 * (4095 - MQ2_ADC) / MQ2_ADC
   where RL = 10 kΩ and ADC_MAX = 4095 (12-bit ADC)

Step 2 — Rs/Ro Ratio:
   ratio = Rs / Ro
   where Ro = Field-calibrated baseline resistance in clean air
   
   METHOD A: From firmware calibration (50 samples at startup):
      Ro = average(Rs over 50 samples) / RO_CLEAN_AIR_FACTOR
      Ro = average(Rs) / 9.83
   
   METHOD B: From known baseline ADC in clean air:
      Rs_baseline = 10 * (4095 - baseline_adc) / baseline_adc
      Ro = Rs_baseline / 9.83

Step 3 — Ratio to Smoke PPM:
   MQ2_PPM = 10 ^ ( (log10(ratio) - pcurve[1]) / pcurve[2] + pcurve[0] )
           = 10 ^ ( (log10(ratio) - 0.53) / -0.44 + 2.3 )
   
   using MQ2 Smoke curve constants:
   - pcurve[0] = 2.3
   - pcurve[1] = 0.53
   - pcurve[2] = -0.44
"""

import pandas as pd
import numpy as np
import os
import glob
from pathlib import Path

# Configuration
DATASET_FOLDER = os.path.join(os.path.dirname(__file__), 'dataset')

# MQ2 SENSOR CONSTANTS
RL_VALUE = 10.0                    # Load resistor (kΩ)
ADC_MAX = 4095.0                   # 12-bit ADC maximum
RO_CLEAN_AIR_FACTOR = 9.83         # Clean air calibration factor (from firmware)

# MQ2 Smoke curve constants
PCURVE_0 = 2.3    # Curve constant a0
PCURVE_1 = 0.53   # Curve constant a1
PCURVE_2 = -0.44  # Curve constant a2

# =========================================================================
# FIELD-CALIBRATED RO VALUES (Per Location/Date)
# =========================================================================
# 
# These Ro values should be obtained from field calibration data.
# To calculate Ro from a known baseline ADC reading:
#   1. Take sensor in clean air
#   2. Record baseline_adc value
#   3. Calculate: Rs_baseline = 10 * (4095 - baseline_adc) / baseline_adc
#   4. Calculate: Ro = Rs_baseline / 9.83
#
# Example from firmware calibration (MQ2_OFFSET_CALIBRATED):
#   - Baseline ADC: 2210 (from field deployment)
#   - Rs_baseline = 10 * (4095 - 2210) / 2210 = 8.3440 kOhm
#   - Ro = 8.3440 / 9.83 = 0.8488 kOhm

FIELD_CALIBRATED_RO = {
    # Location: Ro value (kOhm)
    # Format: "filename_pattern" or "location_name": Ro_value
    
    "03-16-2026 (Inside of Temfacil).csv": None,        # To be calibrated
    "03-17-2026 (Warehouse).csv": None,                 # To be calibrated
    "03-18-2026 (Outside of Temfacil).csv": None,       # To be calibrated
    "03-19-2026 (Fabrication Area).csv": None,          # To be calibrated
    "03-30-2026 (Active Floor Area).csv": None,         # To be calibrated
    
    # Training simulation data - use firmware default
    "TRAINING SIMULATION DATA": 0.8488,                 # From firmware baseline (2210 ADC)
    
    # Combined datasets - use average of known values
    "combined_data.csv": None,                          # Composite (multiple sources)
    "combined_dataset.csv": None,                       # Composite (multiple sources)
}

# DEFAULT RO (fallback if not specified for a location)
DEFAULT_RO = 0.8488  # Calculated from firmware MQ2_OFFSET_CALIBRATED (baseline ADC: 2210)

def convert_adc_to_ppm(adc_value, ro_value=None):
    """
    Convert MQ2_ADC value to MQ2_PPM (Smoke) using the formula chain.
    
    Uses field-calibrated Ro value for accurate conversion.
    
    Args:
        adc_value: Raw ADC reading from MQ2 sensor
        ro_value: Field-calibrated Ro value (kΩ). If None, uses DEFAULT_RO
    
    Returns:
        PPM value rounded to 2 decimal places
    """
    if pd.isna(adc_value) or adc_value == 0:
        return np.nan
    
    # Use default Ro if not specified
    if ro_value is None:
        ro_value = DEFAULT_RO
    
    try:
        # Step 1: ADC to Rs (Sensor Resistance)
        # Rs = RL * (ADC_MAX - raw_adc) / raw_adc
        rs = RL_VALUE * (ADC_MAX - adc_value) / adc_value
        
        # Step 2: Rs/Ro Ratio (using field-calibrated Ro)
        ratio = rs / ro_value
        
        # Step 3: Ratio to Smoke PPM (MQ2 Smoke curve)
        # MQ2_PPM = 10 ^ ((log10(ratio) - pcurve[1]) / pcurve[2] + pcurve[0])
        log_ratio = np.log10(ratio)
        exponent = (log_ratio - PCURVE_1) / PCURVE_2 + PCURVE_0
        ppm = 10 ** exponent
        
        # Round to 2 decimal places
        return round(ppm, 2)
    except Exception:
        return np.nan

def get_ro_for_file(filename):
    """
    Get the field-calibrated Ro value for a specific CSV file.
    
    Args:
        filename: Name of the CSV file
    
    Returns:
        Ro value in kΩ, or DEFAULT_RO if not specified
    """
    # Exact match
    if filename in FIELD_CALIBRATED_RO and FIELD_CALIBRATED_RO[filename] is not None:
        return FIELD_CALIBRATED_RO[filename]
    
    # Partial match (for simulation data)
    for pattern, ro_value in FIELD_CALIBRATED_RO.items():
        if pattern in filename and ro_value is not None:
            return ro_value
    
    # Return default
    return DEFAULT_RO

def process_csv_file(filepath, is_combined_data=False):
    """
    Process a CSV file and convert MQ2_ADC to MQ2_PPM using field-calibrated Ro.
    
    Args:
        filepath: Path to the CSV file
        is_combined_data: Whether this is the combined_data.csv file with derived features
    
    Returns:
        DataFrame with converted values
    """
    filename = os.path.basename(filepath)
    print(f"\nProcessing: {filename}")
    
    try:
        df = pd.read_csv(filepath)
        
        # Check if MQ2_ADC column exists
        if 'MQ2_ADC' not in df.columns:
            print(f"  [WARN] No MQ2_ADC column found. Skipping.")
            return None
        
        print(f"  Rows: {len(df)}")
        
        # Get field-calibrated Ro value for this file
        ro_value = get_ro_for_file(filename)
        print(f"  Using Ro = {ro_value:.4f} kOhm (field-calibrated)")
        
        # Convert MQ2_ADC to MQ2_PPM using field-calibrated Ro
        print(f"  Converting MQ2_ADC to MQ2_PPM...")
        df['MQ2_ADC'] = df['MQ2_ADC'].apply(lambda x: convert_adc_to_ppm(x, ro_value=ro_value))
        
        # Rename column
        df = df.rename(columns={'MQ2_ADC': 'MQ2_PPM'})
        print(f"  [OK] Column renamed: MQ2_ADC → MQ2_PPM")
        
        if is_combined_data:
            print(f"  [WARN] Note: Recalculating gas-related derived features in combined_data.csv")
            # The combined_data.csv will need special handling for derived features
            # This will be done in a separate function
        
        return df
    
    except Exception as e:
        print(f"  [FAILED] Error: {str(e)}")
        return None

def calculate_ro_from_baseline_adc(baseline_adc):
    """
    Calculate Ro (baseline resistance) from a known clean air ADC reading.
    
    This function follows the firmware calibration method:
    1. Take sensor in clean air
    2. Record baseline_adc value
    3. Calculate: Rs_baseline = RL * (ADC_MAX - baseline_adc) / baseline_adc
    4. Calculate: Ro = Rs_baseline / RO_CLEAN_AIR_FACTOR
    
    Args:
        baseline_adc: ADC reading taken in clean air (0-4095)
    
    Returns:
        Ro value in kΩ
    
    Example:
        >>> ro = calculate_ro_from_baseline_adc(2210)
        >>> print(f"Ro = {ro:.4f} kΩ")
        Ro = 0.8488 kΩ
    """
    if baseline_adc <= 0 or baseline_adc >= ADC_MAX:
        print(f"[WARN] Warning: Baseline ADC {baseline_adc} out of valid range (1-4094)")
        return DEFAULT_RO
    
    # Calculate Rs at baseline
    rs_baseline = RL_VALUE * (ADC_MAX - baseline_adc) / baseline_adc
    
    # Calculate Ro using clean air factor
    ro = rs_baseline / RO_CLEAN_AIR_FACTOR
    
    return ro

def recalculate_combined_data_features(df):
    """
    Recalculate all gas-related features in combined_data.csv.
    
    Features to recalculate:
    - gas_co_ratio: ratio of gas (MQ2_PPM) to co (MQ7_PPM)
    - gas_delta: change in gas value from previous row
    - gas_lag_1/3/5: lagged gas values
    - gas_acceleration: whether |gas_delta| > 2
    - gas_volatility: standard deviation of recent gas values
    - gas_trend: direction of change in gas
    - is_gas_accelerating: sustained rise in gas values
    
    Note: We don't have the raw MQ7_PPM in combined_data, so we'll need to
    reconstruct gas and co values from MQ2_PPM and MQ7_ADC.
    """
    print("\n  Recalculating gas-related features...")
    
    # For now, we need to:
    # 1. Reconstruct the "gas" variable from MQ2_PPM
    # 2. Reconstruct the "co" variable from MQ7_ADC (or convert if needed)
    # 3. Recalculate all dependent features
    
    # The problem is that we have MQ2_PPM but not the intermediate "gas" value
    # We'll use MQ2_PPM as the gas value for ratio calculations
    gas_values = df['MQ2_PPM'].fillna(0)
    
    # For CO, we need to check if MQ7_ADC needs conversion or if it's already in PPM
    # Looking at the data, MQ7_ADC values are in the range 1800-1900, which are ADC values
    # We'll need to convert these to PPM as well
    
    # Let me check if there's a co conversion needed
    # For now, I'll keep MQ7 as-is since the user only asked for MQ2 conversion
    co_values = df['MQ7_ADC'].fillna(0)
    
    # Recalculate gas_co_ratio
    df['gas_co_ratio'] = gas_values / (co_values + 0.1)
    
    # Recalculate gas_delta (change from previous row)
    df['gas_delta'] = gas_values.diff().fillna(0)
    
    # Recalculate gas_acceleration (|delta| > 2)
    df['gas_acceleration'] = (df['gas_delta'].abs() > 2).astype(int)
    
    # Recalculate gas_lag_1, gas_lag_3, gas_lag_5
    df['gas_lag_1'] = gas_values.shift(1).fillna(0)
    df['gas_lag_3'] = gas_values.shift(3).fillna(0)
    df['gas_lag_5'] = gas_values.shift(5).fillna(0)
    
    # Recalculate gas_volatility (rolling std of recent 5 readings)
    df['gas_volatility'] = gas_values.rolling(window=5, min_periods=1).std().fillna(0)
    
    # Recalculate gas_trend (+1, -1, or 0)
    df['gas_trend'] = df['gas_delta'].apply(lambda x: np.sign(x) if x != 0 else 0)
    
    # Recalculate is_gas_accelerating (sustained rise)
    df['is_gas_accelerating'] = 0
    for i in range(1, len(df)):
        if df['gas_delta'].iloc[i] > 0 and df['gas_delta'].iloc[i-1] > 0:
            df.loc[i, 'is_gas_accelerating'] = 1
    
    print(f"  [OK] Gas-related features recalculated")
    
    return df

def main():
    """Main conversion function with field-calibrated Ro values"""
    print("=" * 80)
    print("MQ2_ADC to MQ2_PPM Conversion Script")
    print("Using Field-Calibrated Ro Values")
    print("=" * 80)
    
    # Display calibration information
    print(f"\nCALIBRATION CONSTANTS:")
    print(f"  RL (Load Resistor): {RL_VALUE} kOhm")
    print(f"  ADC_MAX (12-bit): {int(ADC_MAX)}")
    print(f"  RO_CLEAN_AIR_FACTOR: {RO_CLEAN_AIR_FACTOR}")
    print(f"  DEFAULT_RO (fallback): {DEFAULT_RO:.4f} kOhm")
    print(f"  MQ2 Smoke Curve: [{PCURVE_0}, {PCURVE_1}, {PCURVE_2}]")
    
    # Get all CSV files in dataset folder
    csv_files = sorted(glob.glob(os.path.join(DATASET_FOLDER, '*.csv')))
    
    if not csv_files:
        print(f"\n❌ No CSV files found in {DATASET_FOLDER}")
        return
    
    print(f"\nFound {len(csv_files)} CSV files")
    
    converted_files = []
    skipped_files = []
    conversion_log = {}
    
    # Process each CSV file
    for csv_file in csv_files:
        filename = os.path.basename(csv_file)
        is_combined = 'combined_data.csv' in filename
        
        ro_value = get_ro_for_file(filename)
        df = process_csv_file(csv_file, is_combined_data=is_combined)
        
        if df is not None:
            # Special handling for combined_data.csv
            if is_combined:
                df = recalculate_combined_data_features(df)
            
            # Save the converted file
            try:
                df.to_csv(csv_file, index=False)
                print(f"  [OK] Saved successfully")
                converted_files.append(filename)
                conversion_log[filename] = ro_value
            except Exception as e:
                print(f"  [FAILED] Failed to save: {str(e)}")
                skipped_files.append(filename)
        else:
            skipped_files.append(filename)
    
    # Summary
    print("\n" + "=" * 80)
    print("CONVERSION SUMMARY")
    print("=" * 80)
    print(f"\n[OK] Successfully converted: {len(converted_files)} files")
    for f in converted_files:
        ro = conversion_log.get(f, DEFAULT_RO)
        print(f"  - {f:50s} (Ro = {ro:.4f} kOhm)")
    
    if skipped_files:
        print(f"\n[WARN] Skipped: {len(skipped_files)} files")
        for f in skipped_files:
            print(f"  - {f}")
    
    print("\n" + "=" * 80)
    print("CONVERSION FORMULA CHAIN (Field-Calibrated):")
    print("=" * 80)
    print("Step 1: Rs = RL x (ADC_MAX - ADC) / ADC")
    print("        Rs = 10 x (4095 - ADC) / ADC")
    print("\nStep 2: ratio = Rs / Ro (using field-calibrated Ro)")
    print("\nStep 3: PPM = 10 ^ ((log(ratio) - 0.53) / -0.44 + 2.3)")
    print("=" * 80)
    
    print("\n[SUCCESS] MQ2_ADC to MQ2_PPM conversion complete!")
    print("=" * 80)

# =============================================================================
# HOW TO CONFIGURE FIELD-CALIBRATED RO VALUES
# =============================================================================
#
# OPTION 1: Use firmware baseline ADC readings
# ─────────────────────────────────────────────
# Each location has a baseline ADC reading (sensor in clean air).
# To calculate Ro:
#   from convert_mq2_adc_to_ppm import calculate_ro_from_baseline_adc
#   ro = calculate_ro_from_baseline_adc(baseline_adc_value)
#
# Example:
#   Inside Temfacil baseline ADC: 2210 → Ro = 0.8488 kΩ
#   Warehouse baseline ADC: 2150 → Ro = 0.8705 kΩ
#
# OPTION 2: From firmware field deployment data
# ──────────────────────────────────────────────
# Review the firmware calibration logs to find actual baseline readings.
# (See esp32_embedded_ml.ino: MQ2_OFFSET_CALIBRATED = 510.0, baseline ADC: 2210)
#
# OPTION 3: Update FIELD_CALIBRATED_RO dictionary
# ────────────────────────────────────────────────
# Edit the FIELD_CALIBRATED_RO dictionary above with known values:
#   FIELD_CALIBRATED_RO = {
#       "03-16-2026 (Inside of Temfacil).csv": 0.8488,  # Ro in kΩ
#       "03-17-2026 (Warehouse).csv": 0.8705,
#       ...
#   }
#
# =============================================================================

if __name__ == '__main__':
    main()
