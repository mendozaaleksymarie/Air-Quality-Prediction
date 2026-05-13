import pandas as pd
import numpy as np
from pathlib import Path

# Define dataset directory
dataset_dir = 'dataset'

# Conversion formulas
def adc_to_ppm_mq2(adc):
    return ((adc / 4095.0) * 1000.0) - 510.0

def adc_to_ppm_mq7(adc):
    return ((adc / 4095.0) * 100.0) - 52.0

print("Starting ADC to PPM conversion process...")
print("MQ2_PPM = ((MQ2_ADC / 4095.0) × 1000.0) - 510.0")
print("MQ7_PPM = ((MQ7_ADC / 4095.0) × 100.0) - 52.0\n")

# Get all CSV files in dataset folder
csv_files = list(Path(dataset_dir).glob('*.csv'))

# Filter out combined files (we'll handle those separately)
data_files = [f for f in csv_files if f.name not in ['combined_data.csv', 'combined_dataset.csv']]

print(f"Found {len(data_files)} data files to process\n")

# Process each data file
for file_path in sorted(data_files):
    try:
        df = pd.read_csv(file_path)
        original_rows = len(df)
        
        # Check if MQ2_ADC and MQ7_ADC columns exist
        if 'MQ2_ADC' in df.columns and 'MQ7_ADC' in df.columns:
            # Convert ADC to PPM
            df['MQ2_PPM'] = adc_to_ppm_mq2(df['MQ2_ADC']).round(2)
            df['MQ7_PPM'] = adc_to_ppm_mq7(df['MQ7_ADC']).round(2)
            
            # Drop the old ADC columns
            df = df.drop(columns=['MQ2_ADC', 'MQ7_ADC'])
            
            # Save back to file
            df.to_csv(file_path, index=False)
            
            print(f"✅ {file_path.name}")
            print(f"   Rows: {original_rows}")
            print(f"   MQ2_PPM range: {df['MQ2_PPM'].min():.2f} - {df['MQ2_PPM'].max():.2f}")
            print(f"   MQ7_PPM range: {df['MQ7_PPM'].min():.2f} - {df['MQ7_PPM'].max():.2f}")
        else:
            print(f"⚠️  {file_path.name}: Missing MQ2_ADC or MQ7_ADC columns")
    except Exception as e:
        print(f"❌ {file_path.name}: Error - {str(e)}")

print("\n" + "="*60)
print("Updating combined_data.csv...")
print("="*60 + "\n")

# Now handle combined_data.csv
try:
    df_combined = pd.read_csv('dataset/combined_data.csv')
    
    # Sort by timestamp to ensure proper ordering for lag calculations
    df_combined['created_at'] = pd.to_datetime(df_combined['created_at'])
    df_combined = df_combined.sort_values('created_at').reset_index(drop=True)
    
    # Convert ADC to PPM
    df_combined['MQ2_PPM'] = adc_to_ppm_mq2(df_combined['MQ2_ADC']).round(2)
    df_combined['MQ7_PPM'] = adc_to_ppm_mq7(df_combined['MQ7_ADC']).round(2)
    
    # Drop the old ADC columns
    df_combined = df_combined.drop(columns=['MQ2_ADC', 'MQ7_ADC'])
    
    # Use converted PPM values for recalculation
    gas = df_combined['MQ2_PPM']
    co = df_combined['MQ7_PPM']
    
    # Recalculate derived columns
    df_combined['gas_co_ratio'] = (gas / co).fillna(0).replace([np.inf, -np.inf], 0)
    df_combined['gas_delta'] = gas - gas.shift(1).fillna(gas)
    df_combined['co_delta'] = co - co.shift(1).fillna(co)
    
    # Lag columns
    df_combined['gas_lag_1'] = gas.shift(1).fillna(gas)
    df_combined['co_lag_1'] = co.shift(1).fillna(co)
    df_combined['gas_lag_3'] = gas.shift(3).fillna(gas)
    df_combined['co_lag_3'] = co.shift(3).fillna(co)
    df_combined['gas_lag_5'] = gas.shift(5).fillna(gas)
    df_combined['co_lag_5'] = co.shift(5).fillna(co)
    
    # Gas volatility (rolling standard deviation)
    df_combined['gas_volatility'] = gas.rolling(window=5, min_periods=1).std().fillna(0)
    
    # Gas trend (linear regression slope over last 5 points)
    def calculate_trend(series, window=5):
        trends = []
        for i in range(len(series)):
            if i < window - 1:
                trends.append(0.0)
            else:
                y = series.iloc[i-window+1:i+1].values
                x = np.arange(window)
                if len(y) > 1 and np.std(y) > 0:
                    slope = np.polyfit(x, y, 1)[0]
                    trends.append(slope)
                else:
                    trends.append(0.0)
        return trends
    
    df_combined['gas_trend'] = calculate_trend(gas)
    
    # Gas acceleration (second derivative)
    gas_delta = df_combined['gas_delta'].fillna(0)
    df_combined['gas_acceleration'] = gas_delta - gas_delta.shift(1).fillna(0)
    
    # Is gas accelerating (PPM-based threshold)
    threshold = 0.1  # PPM-based threshold
    df_combined['is_gas_accelerating'] = (df_combined['gas_acceleration'].abs() > threshold).astype(int)
    
    # Save updated combined_data.csv
    df_combined.to_csv('dataset/combined_data.csv', index=False)
    
    print(f"✅ combined_data.csv")
    print(f"   Rows: {len(df_combined)}")
    print(f"   MQ2_PPM range: {df_combined['MQ2_PPM'].min():.2f} - {df_combined['MQ2_PPM'].max():.2f}")
    print(f"   MQ7_PPM range: {df_combined['MQ7_PPM'].min():.2f} - {df_combined['MQ7_PPM'].max():.2f}")
    print(f"   Derived columns recalculated: 9 columns")
    
except Exception as e:
    print(f"❌ combined_data.csv: Error - {str(e)}")

print("\n" + "="*60)
print("Also updating combined_dataset.csv...")
print("="*60 + "\n")

# Update combined_dataset.csv
try:
    df_dataset = pd.read_csv('dataset/combined_dataset.csv')
    
    # Convert ADC to PPM
    df_dataset['MQ2_PPM'] = adc_to_ppm_mq2(df_dataset['MQ2_ADC']).round(2)
    df_dataset['MQ7_PPM'] = adc_to_ppm_mq7(df_dataset['MQ7_ADC']).round(2)
    
    # Drop the old ADC columns
    df_dataset = df_dataset.drop(columns=['MQ2_ADC', 'MQ7_ADC'])
    
    # Save back to file
    df_dataset.to_csv('dataset/combined_dataset.csv', index=False)
    
    print(f"✅ combined_dataset.csv")
    print(f"   Rows: {len(df_dataset)}")
    print(f"   MQ2_PPM range: {df_dataset['MQ2_PPM'].min():.2f} - {df_dataset['MQ2_PPM'].max():.2f}")
    print(f"   MQ7_PPM range: {df_dataset['MQ7_PPM'].min():.2f} - {df_dataset['MQ7_PPM'].max():.2f}")
    
except Exception as e:
    print(f"❌ combined_dataset.csv: Error - {str(e)}")

print("\n" + "="*60)
print("✅ ADC to PPM conversion complete!")
print("="*60)
