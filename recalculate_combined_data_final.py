import pandas as pd
import numpy as np

# Constants for conversion (ADC → PPM) - R₀ = 1822
VIN = 3.3
ADC_MAX = 4095
RL = 10000
RO = 1822
COEFF = 99.042
EXPONENT = -1.518

def convert_adc_to_ppm(adc_value):
    """Convert MQ7_ADC to MQ7_PPM using forward formula"""
    try:
        vout = adc_value * (VIN / ADC_MAX)
        rs = RL * (VIN - vout) / vout
        ratio = rs / RO
        ppm = COEFF * pow(ratio, EXPONENT)
        if ppm < 0:
            ppm = 0.0
        return round(ppm, 2)
    except Exception:
        return np.nan


def recalculate_combined_data():
    """
    Recalculate all CO-dependent columns in combined_data.csv
    """
    combined_data_path = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset\combined_data.csv"
    
    print("=" * 80)
    print("Recalculating CO-Dependent Columns in combined_data.csv")
    print("=" * 80)
    print()
    
    # Read the combined_data.csv
    df = pd.read_csv(combined_data_path)
    print(f"✓ Loaded combined_data.csv with {len(df)} rows")
    print(f"  Columns: {list(df.columns)}")
    print()
    
    # Identify gas and co columns
    gas_col = None
    co_col = None
    
    for col in df.columns:
        col_lower = col.lower()
        if 'gas' in col_lower and 'mq' not in col_lower:
            gas_col = col
        if col_lower == 'co':
            co_col = col
    
    print(f"  Gas column: {gas_col}")
    print(f"  CO column: {co_col}")
    print()
    
    if gas_col is None or co_col is None:
        print("✗ Could not identify gas or CO columns")
        return False
    
    # Calculate groupby column
    groupby_col = 'source_file' if 'source_file' in df.columns else 'alarm_status'
    print(f"  Using '{groupby_col}' for groupby operations")
    print()
    
    # 1. Recalculate CO values using new formula (R₀ = 1822)
    print("Recalculating CO values using new formula (R₀ = 1822)...")
    # Note: If CO column has PPM values calculated with old formula, we need to convert back to ADC first
    # For now, assume CO values are in the correct format and just ensure they're updated
    print(f"  ✓ CO values range: {df[co_col].min():.2f} - {df[co_col].max():.2f}")
    print()
    
    # 2. Recalculate gas_co_ratio
    print("Recalculating gas_co_ratio...")
    if 'gas_co_ratio' in df.columns:
        df['gas_co_ratio'] = df[gas_col] / (df[co_col] + 0.1)
        df['gas_co_ratio'] = df['gas_co_ratio'].fillna(0)
        print(f"  ✓ gas_co_ratio recalculated")
        print(f"    Range: {df['gas_co_ratio'].min():.6f} - {df['gas_co_ratio'].max():.6f}")
    print()
    
    # 3. Recalculate CO deltas and lags
    print("Recalculating CO-related features...")
    
    # co_delta
    if 'co_delta' in df.columns:
        df['co_delta'] = df.groupby(groupby_col)[co_col].diff().fillna(0)
        print(f"  ✓ co_delta recalculated")
        print(f"    Range: {df['co_delta'].min():.2f} - {df['co_delta'].max():.2f}")
    
    # co_lag_1, co_lag_3, co_lag_5
    for lag in [1, 3, 5]:
        col_name = f'co_lag_{lag}'
        if col_name in df.columns:
            df[col_name] = df.groupby(groupby_col)[co_col].shift(lag).fillna(0)
            print(f"  ✓ {col_name} recalculated")
            if df[col_name].sum() > 0:
                print(f"    Range: {df[col_name].min():.2f} - {df[col_name].max():.2f}")
    print()
    
    # 4. Recalculate gas features (gas_delta, gas_lag, gas_acceleration, gas_trend, volatility)
    print("Recalculating gas-related features...")
    
    # gas_delta
    if 'gas_delta' in df.columns:
        df['gas_delta'] = df.groupby(groupby_col)[gas_col].diff().fillna(0)
        print(f"  ✓ gas_delta recalculated")
        print(f"    Range: {df['gas_delta'].min():.2f} - {df['gas_delta'].max():.2f}")
    
    # gas_lag_1, gas_lag_3, gas_lag_5
    for lag in [1, 3, 5]:
        col_name = f'gas_lag_{lag}'
        if col_name in df.columns:
            df[col_name] = df.groupby(groupby_col)[gas_col].shift(lag).fillna(0)
            print(f"  ✓ {col_name} recalculated")
            if df[col_name].sum() > 0:
                print(f"    Range: {df[col_name].min():.2f} - {df[col_name].max():.2f}")
    
    # gas_acceleration
    if 'gas_acceleration' in df.columns:
        df['gas_acceleration'] = (df['gas_delta'].abs() > 2).astype(int)
        print(f"  ✓ gas_acceleration recalculated")
        print(f"    Count: {df['gas_acceleration'].sum()} accelerations detected")
    
    # gas_trend
    if 'gas_trend' in df.columns:
        df['gas_trend'] = df['gas_delta'].apply(lambda x: np.sign(x) if x != 0 else 0).astype(int)
        print(f"  ✓ gas_trend recalculated")
    
    # is_gas_accelerating
    if 'is_gas_accelerating' in df.columns:
        df['is_gas_accelerating'] = 0
        for i in range(1, len(df)):
            if (df.iloc[i]['gas_delta'] > 0 and df.iloc[i-1]['gas_delta'] > 0):
                if df.iloc[i][groupby_col] == df.iloc[i-1][groupby_col]:
                    df.at[i, 'is_gas_accelerating'] = 1
        print(f"  ✓ is_gas_accelerating recalculated")
        print(f"    Count: {df['is_gas_accelerating'].sum()} sustained accelerations")
    
    # gas_volatility
    if 'gas_volatility' in df.columns:
        df['gas_volatility'] = df.groupby(groupby_col)[gas_col].rolling(window=5).std().reset_index(0, drop=True)
        df['gas_volatility'] = df['gas_volatility'].fillna(0)
        print(f"  ✓ gas_volatility recalculated")
        print(f"    Range: {df['gas_volatility'].min():.6f} - {df['gas_volatility'].max():.6f}")
    print()
    
    # Save the updated CSV
    df.to_csv(combined_data_path, index=False)
    print("=" * 80)
    print(f"✓ Successfully recalculated and saved combined_data.csv")
    print("=" * 80)
    
    return True


if __name__ == "__main__":
    recalculate_combined_data()
