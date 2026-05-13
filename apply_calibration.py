import pandas as pd
import numpy as np
from pathlib import Path

def calibrate_mq2(adc):
    """Apply linear regression calibration formula to MQ2_ADC values"""
    return ((0.3417 * adc) + 2068.83).round(2)

def calibrate_mq7(adc):
    """Apply linear regression calibration formula to MQ7_ADC values"""
    return ((0.4055 * adc) + 2116.79).round(2)

def recalculate_derived_columns(df):
    """Recalculate all derived columns affected by MQ2_ADC and MQ7_ADC changes"""
    
    # Ensure data is sorted by timestamp for proper lag calculations
    if 'created_at' in df.columns:
        df = df.sort_values('created_at').reset_index(drop=True)
    
    # 1. gas_co_ratio: MQ2_ADC / MQ7_ADC
    if 'MQ2_ADC' in df.columns and 'MQ7_ADC' in df.columns:
        df['gas_co_ratio'] = df['MQ2_ADC'] / df['MQ7_ADC']
        df['gas_co_ratio'] = df['gas_co_ratio'].replace([np.inf, -np.inf], np.nan)
        df['gas_co_ratio'] = df['gas_co_ratio'].fillna(0).round(4)
    
    # 2. gas_delta: Current MQ2_ADC - Previous MQ2_ADC
    if 'MQ2_ADC' in df.columns:
        df['gas_delta'] = df['MQ2_ADC'].diff().fillna(0).round(2)
    
    # 3. co_delta: Current MQ7_ADC - Previous MQ7_ADC
    if 'MQ7_ADC' in df.columns:
        df['co_delta'] = df['MQ7_ADC'].diff().fillna(0).round(2)
    
    # 4. gas_lag_1: MQ2_ADC shifted 1 step
    if 'MQ2_ADC' in df.columns:
        df['gas_lag_1'] = df['MQ2_ADC'].shift(1).fillna(df['MQ2_ADC'].iloc[0]).round(2)
    
    # 5. co_lag_1: MQ7_ADC shifted 1 step
    if 'MQ7_ADC' in df.columns:
        df['co_lag_1'] = df['MQ7_ADC'].shift(1).fillna(df['MQ7_ADC'].iloc[0]).round(2)
    
    # 6. gas_lag_3: MQ2_ADC shifted 3 steps
    if 'MQ2_ADC' in df.columns:
        df['gas_lag_3'] = df['MQ2_ADC'].shift(3).fillna(df['MQ2_ADC'].iloc[0]).round(2)
    
    # 7. co_lag_3: MQ7_ADC shifted 3 steps
    if 'MQ7_ADC' in df.columns:
        df['co_lag_3'] = df['MQ7_ADC'].shift(3).fillna(df['MQ7_ADC'].iloc[0]).round(2)
    
    # 8. gas_lag_5: MQ2_ADC shifted 5 steps
    if 'MQ2_ADC' in df.columns:
        df['gas_lag_5'] = df['MQ2_ADC'].shift(5).fillna(df['MQ2_ADC'].iloc[0]).round(2)
    
    # 9. co_lag_5: MQ7_ADC shifted 5 steps
    if 'MQ7_ADC' in df.columns:
        df['co_lag_5'] = df['MQ7_ADC'].shift(5).fillna(df['MQ7_ADC'].iloc[0]).round(2)
    
    # 10. gas_volatility: Rolling standard deviation (5-point window)
    if 'MQ2_ADC' in df.columns:
        df['gas_volatility'] = df['MQ2_ADC'].rolling(window=5, min_periods=1).std().fillna(0).round(4)
    
    # 11. gas_trend: Linear regression slope over 5-point window
    if 'MQ2_ADC' in df.columns:
        gas_trend = []
        for i in range(len(df)):
            start_idx = max(0, i - 4)
            window = df['MQ2_ADC'].iloc[start_idx:i+1].values
            if len(window) > 1:
                x = np.arange(len(window))
                slope = np.polyfit(x, window, 1)[0]
                gas_trend.append(slope)
            else:
                gas_trend.append(0)
        df['gas_trend'] = np.array(gas_trend).round(4)
    
    # 12. gas_acceleration: Second derivative (delta of delta)
    if 'gas_delta' in df.columns:
        df['gas_acceleration'] = df['gas_delta'].diff().fillna(0).round(2)
    
    # 13. is_gas_accelerating: Boolean flag (acceleration > 1.0 ADC threshold)
    if 'gas_acceleration' in df.columns:
        df['is_gas_accelerating'] = df['gas_acceleration'] > 1.0
    
    return df

# Path to dataset folder
dataset_path = Path("dataset")

# Get all CSV files
csv_files = list(dataset_path.glob("*.csv"))
data_files = [f for f in csv_files if not f.name.startswith('combined')]
combined_data_file = dataset_path / "combined_data.csv"
combined_dataset_file = dataset_path / "combined_dataset.csv"

print("=" * 80)
print("APPLYING LINEAR REGRESSION CALIBRATION TO ALL DATASET FILES")
print("=" * 80)

# Process data files (excluding combined files initially)
for file_path in sorted(data_files):
    try:
        print(f"\nProcessing: {file_path.name}")
        
        # Read CSV
        df = pd.read_csv(file_path)
        
        # Store original values for reporting
        if 'MQ2_ADC' in df.columns:
            mq2_before = df['MQ2_ADC'].describe()
        if 'MQ7_ADC' in df.columns:
            mq7_before = df['MQ7_ADC'].describe()
        
        # Apply calibration formulas
        if 'MQ2_ADC' in df.columns:
            df['MQ2_ADC'] = calibrate_mq2(df['MQ2_ADC'])
            mq2_after = df['MQ2_ADC'].describe()
            print(f"  MQ2_ADC: {mq2_before['min']:.2f}-{mq2_before['max']:.2f} → {mq2_after['min']:.2f}-{mq2_after['max']:.2f}")
        
        if 'MQ7_ADC' in df.columns:
            df['MQ7_ADC'] = calibrate_mq7(df['MQ7_ADC'])
            mq7_after = df['MQ7_ADC'].describe()
            print(f"  MQ7_ADC: {mq7_before['min']:.2f}-{mq7_before['max']:.2f} → {mq7_after['min']:.2f}-{mq7_after['max']:.2f}")
        
        # Save back to file
        df.to_csv(file_path, index=False)
        print(f"  ✓ Saved {len(df)} rows")
        
    except Exception as e:
        print(f"  ✗ ERROR: {str(e)}")

# Process combined_data.csv (with derived column recalculation)
if combined_data_file.exists():
    try:
        print(f"\n{'=' * 80}")
        print(f"Processing: combined_data.csv (with derived column recalculation)")
        print(f"{'=' * 80}")
        
        df = pd.read_csv(combined_data_file)
        
        # Store original values
        if 'MQ2_ADC' in df.columns:
            mq2_before = df['MQ2_ADC'].describe()
        if 'MQ7_ADC' in df.columns:
            mq7_before = df['MQ7_ADC'].describe()
        
        # Apply calibration formulas
        if 'MQ2_ADC' in df.columns:
            df['MQ2_ADC'] = calibrate_mq2(df['MQ2_ADC'])
            mq2_after = df['MQ2_ADC'].describe()
            print(f"MQ2_ADC: {mq2_before['min']:.2f}-{mq2_before['max']:.2f} → {mq2_after['min']:.2f}-{mq2_after['max']:.2f}")
        
        if 'MQ7_ADC' in df.columns:
            df['MQ7_ADC'] = calibrate_mq7(df['MQ7_ADC'])
            mq7_after = df['MQ7_ADC'].describe()
            print(f"MQ7_ADC: {mq7_before['min']:.2f}-{mq7_before['max']:.2f} → {mq7_after['min']:.2f}-{mq7_after['max']:.2f}")
        
        # Recalculate derived columns
        print(f"\nRecalculating derived columns...")
        df = recalculate_derived_columns(df)
        print(f"  ✓ Updated 13 derived columns")
        
        # Save back to file
        df.to_csv(combined_data_file, index=False)
        print(f"  ✓ Saved {len(df)} rows")
        
    except Exception as e:
        print(f"  ✗ ERROR: {str(e)}")

# Process combined_dataset.csv
if combined_dataset_file.exists():
    try:
        print(f"\nProcessing: combined_dataset.csv")
        
        df = pd.read_csv(combined_dataset_file)
        
        # Store original values
        if 'MQ2_ADC' in df.columns:
            mq2_before = df['MQ2_ADC'].describe()
        if 'MQ7_ADC' in df.columns:
            mq7_before = df['MQ7_ADC'].describe()
        
        # Apply calibration formulas
        if 'MQ2_ADC' in df.columns:
            df['MQ2_ADC'] = calibrate_mq2(df['MQ2_ADC'])
            mq2_after = df['MQ2_ADC'].describe()
            print(f"  MQ2_ADC: {mq2_before['min']:.2f}-{mq2_before['max']:.2f} → {mq2_after['min']:.2f}-{mq2_after['max']:.2f}")
        
        if 'MQ7_ADC' in df.columns:
            df['MQ7_ADC'] = calibrate_mq7(df['MQ7_ADC'])
            mq7_after = df['MQ7_ADC'].describe()
            print(f"  MQ7_ADC: {mq7_before['min']:.2f}-{mq7_before['max']:.2f} → {mq7_after['min']:.2f}-{mq7_after['max']:.2f}")
        
        # Save back to file
        df.to_csv(combined_dataset_file, index=False)
        print(f"  ✓ Saved {len(df)} rows")
        
    except Exception as e:
        print(f"  ✗ ERROR: {str(e)}")

print(f"\n{'=' * 80}")
print("CALIBRATION COMPLETE")
print(f"{'=' * 80}")
