import pandas as pd
import numpy as np
from pathlib import Path

def recalculate_combined_data(file_path):
    """
    Recalculate columns in combined_data.csv that are affected by MQ2_ADC → MQ2_PPM conversion
    """
    print(f"Processing: {file_path}")
    
    # Read the CSV file
    df = pd.read_csv(file_path)
    
    if 'MQ2_PPM' not in df.columns or 'MQ7_ADC' not in df.columns:
        print("  ⚠ Skipping: Required columns not found")
        return False
    
    try:
        # === Recalculate gas_co_ratio (MQ2_PPM / MQ7_ADC) ===
        df['gas_co_ratio'] = round(df['MQ2_PPM'] / df['MQ7_ADC'], 4)
        
        # === Recalculate gas_delta (change in MQ2_PPM) ===
        # First row is 0, subsequent rows are difference from previous row
        df['gas_delta'] = df['MQ2_PPM'].diff().fillna(0.0)
        df['gas_delta'] = round(df['gas_delta'], 4)
        
        # === Recalculate gas_lag_1 (MQ2_PPM from 1 step back) ===
        df['gas_lag_1'] = df['MQ2_PPM'].shift(1)
        
        # === Recalculate gas_lag_3 (MQ2_PPM from 3 steps back) ===
        df['gas_lag_3'] = df['MQ2_PPM'].shift(3)
        
        # === Recalculate gas_lag_5 (MQ2_PPM from 5 steps back) ===
        df['gas_lag_5'] = df['MQ2_PPM'].shift(5)
        
        # === Recalculate gas_volatility (standard deviation) ===
        # Using a rolling window approach (e.g., last 5 values)
        df['gas_volatility'] = df['MQ2_PPM'].rolling(window=5, min_periods=1).std()
        df['gas_volatility'] = round(df['gas_volatility'], 4)
        
        # === Recalculate gas_acceleration (second derivative) ===
        # Acceleration is the change in delta (gas_acceleration = gas_delta.diff())
        df['gas_acceleration'] = df['gas_delta'].diff().fillna(0.0)
        df['gas_acceleration'] = round(df['gas_acceleration'], 4)
        
        # === Recalculate is_gas_accelerating (whether acceleration > 0) ===
        df['is_gas_accelerating'] = (df['gas_acceleration'] > 0).astype(int)
        
        # === Recalculate gas_trend (direction of trend: -1, 0, or 1) ===
        # If current MQ2_PPM > 3-step lag: trend = 1 (increasing)
        # If current MQ2_PPM < 3-step lag: trend = -1 (decreasing)
        # Otherwise: trend = 0 (stable)
        df['gas_trend'] = np.where(
            df['MQ2_PPM'] > df['gas_lag_3'],
            1.0,
            np.where(df['MQ2_PPM'] < df['gas_lag_3'], -1.0, 0.0)
        )
        
        # Save the modified CSV
        df.to_csv(file_path, index=False)
        
        print(f"  ✓ Successfully recalculated and saved")
        print(f"    - Updated gas_co_ratio")
        print(f"    - Updated gas_delta")
        print(f"    - Updated gas_lag_1, gas_lag_3, gas_lag_5")
        print(f"    - Updated gas_volatility")
        print(f"    - Updated gas_acceleration")
        print(f"    - Updated is_gas_accelerating")
        print(f"    - Updated gas_trend")
        
        return True
        
    except Exception as e:
        print(f"  ✗ Error: {str(e)}")
        import traceback
        traceback.print_exc()
        return False

if __name__ == "__main__":
    combined_file = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset\combined_data.csv"
    recalculate_combined_data(combined_file)
