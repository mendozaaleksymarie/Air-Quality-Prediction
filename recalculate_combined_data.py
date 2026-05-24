import pandas as pd
import numpy as np
from pathlib import Path

def recalculate_combined_data_columns():
    """
    Recalculate all derived columns in combined_data.csv that depend on MQ7_PPM (CO)
    """
    combined_data_path = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset\combined_data.csv"
    
    print("=" * 80)
    print("Recalculating Derived Columns in combined_data.csv")
    print("=" * 80)
    print()
    
    # Read the combined_data.csv
    df = pd.read_csv(combined_data_path)
    print(f"✓ Loaded combined_data.csv with {len(df)} rows")
    print(f"  Columns: {list(df.columns)}")
    print()
    
    # Rename 'gas' to actual column name if it exists (it might be MQ2_PPM or similar)
    # First, identify the gas and co columns
    gas_col = None
    co_col = None
    
    for col in df.columns:
        col_lower = col.lower()
        if 'gas' in col_lower or 'mq2' in col_lower:
            gas_col = col
        if 'co' in col_lower or 'mq7' in col_lower:
            co_col = col
    
    print(f"  Gas column detected: {gas_col}")
    print(f"  CO column detected: {co_col}")
    print()
    
    if gas_col is None or co_col is None:
        print("✗ Could not identify gas or CO columns")
        return False
    
    # Rename columns to standard names for processing
    df.rename(columns={
        'pm2_5': 'pm25',
        'pm10': 'pm10',
        gas_col: 'gas',
        co_col: 'co'
    }, inplace=True, errors='ignore')
    
    # Ensure required columns exist
    required_cols = ['gas', 'co']
    for col in required_cols:
        if col not in df.columns:
            print(f"✗ Missing required column: {col}")
            return False
    
    # Calculate groupby column
    groupby_col = 'source_file' if 'source_file' in df.columns else 'alarm_status'
    print(f"  Using '{groupby_col}' for groupby operations")
    print()
    
    # 1. Recalculate gas_co_ratio
    print("Recalculating gas_co_ratio...")
    df['gas_co_ratio'] = df['gas'] / (df['co'] + 0.1)
    df['gas_co_ratio'] = df['gas_co_ratio'].fillna(0)
    print(f"  ✓ gas_co_ratio recalculated")
    print(f"    Range: {df['gas_co_ratio'].min():.6f} - {df['gas_co_ratio'].max():.6f}")
    print()
    
    # 2. Recalculate CO deltas and CO lag values
    print("Recalculating CO-related features...")
    
    # co_delta
    df['co_delta'] = df.groupby(groupby_col)['co'].diff().fillna(0)
    print(f"  ✓ co_delta recalculated")
    print(f"    Range: {df['co_delta'].min():.6f} - {df['co_delta'].max():.6f}")
    
    # co_lag_1, co_lag_3, co_lag_5
    for lag in [1, 3, 5]:
        col_name = f'co_lag_{lag}'
        df[col_name] = df.groupby(groupby_col)['co'].shift(lag).fillna(0)
        print(f"  ✓ {col_name} recalculated")
        if df[col_name].sum() > 0:
            print(f"    Range: {df[col_name].min():.6f} - {df[col_name].max():.6f}")
    
    print()
    
    # 3. Recalculate gas_delta and gas_trend (dependent on changes in gas sensor readings)
    print("Recalculating gas-related features...")
    
    # gas_delta
    df['gas_delta'] = df.groupby(groupby_col)['gas'].diff().fillna(0)
    print(f"  ✓ gas_delta recalculated")
    print(f"    Range: {df['gas_delta'].min():.6f} - {df['gas_delta'].max():.6f}")
    
    # gas_lag_1, gas_lag_3, gas_lag_5
    for lag in [1, 3, 5]:
        col_name = f'gas_lag_{lag}'
        df[col_name] = df.groupby(groupby_col)['gas'].shift(lag).fillna(0)
        print(f"  ✓ {col_name} recalculated")
        if df[col_name].sum() > 0:
            print(f"    Range: {df[col_name].min():.6f} - {df[col_name].max():.6f}")
    
    print()
    
    # 4. Recalculate gas_acceleration and gas_trend
    print("Recalculating gas acceleration and trend features...")
    
    # gas_acceleration
    df['gas_acceleration'] = (df['gas_delta'].abs() > 2).astype(int)
    print(f"  ✓ gas_acceleration recalculated")
    print(f"    Values: {df['gas_acceleration'].value_counts().to_dict()}")
    
    # gas_trend: +1 (rising), -1 (falling), 0 (stable)
    df['gas_trend'] = df['gas_delta'].apply(lambda x: np.sign(x) if x != 0 else 0).astype(int)
    print(f"  ✓ gas_trend recalculated")
    print(f"    Values: {df['gas_trend'].value_counts().to_dict()}")
    
    # is_gas_accelerating: sustained rise (both current and previous deltas positive)
    df['is_gas_accelerating'] = 0
    for i in range(1, len(df)):
        if (df.iloc[i]['gas_delta'] > 0 and df.iloc[i-1]['gas_delta'] > 0):
            # Only if in same group
            if df.iloc[i][groupby_col] == df.iloc[i-1][groupby_col]:
                df.at[i, 'is_gas_accelerating'] = 1
    print(f"  ✓ is_gas_accelerating recalculated")
    print(f"    Values: {df['is_gas_accelerating'].value_counts().to_dict()}")
    
    print()
    
    # 5. Recalculate volatility (gas_volatility)
    print("Recalculating gas volatility...")
    df['gas_volatility'] = df.groupby(groupby_col)['gas'].rolling(window=5).std().reset_index(0, drop=True)
    df['gas_volatility'] = df['gas_volatility'].fillna(0)
    print(f"  ✓ gas_volatility recalculated")
    print(f"    Range: {df['gas_volatility'].min():.6f} - {df['gas_volatility'].max():.6f}")
    
    print()
    
    # Restore original column names if they were different
    column_mapping = {
        'gas': gas_col if gas_col != 'gas' else 'gas',
        'co': co_col if co_col != 'co' else 'co',
        'pm25': 'pm2_5' if 'pm2_5' in df.columns or gas_col == 'pm2_5' else 'pm25'
    }
    
    # Actually, let's keep the original column names
    # We need to check what the original column names are
    
    # Save the updated CSV
    df.to_csv(combined_data_path, index=False)
    print("=" * 80)
    print(f"✓ Successfully recalculated and saved combined_data.csv")
    print("=" * 80)
    
    return True


if __name__ == "__main__":
    recalculate_combined_data_columns()
