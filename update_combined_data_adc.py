import pandas as pd
import numpy as np

# Load the combined_data.csv
df = pd.read_csv('dataset/combined_data.csv')

# Sort by timestamp to ensure proper ordering for lag calculations
df['created_at'] = pd.to_datetime(df['created_at'])
df = df.sort_values('created_at').reset_index(drop=True)

# Use MQ2_ADC and MQ7_ADC as gas and co
df['gas'] = df['MQ2_ADC']
df['co'] = df['MQ7_ADC']

print("Recalculating derived columns based on new ADC values...")

# 1. gas_co_ratio = gas / co (avoid division by zero)
df['gas_co_ratio'] = df.apply(lambda row: row['gas'] / row['co'] if row['co'] != 0 else 0, axis=1)

# 2. gas_delta = gas - gas_lag_1
df['gas_delta'] = df['gas'] - df['gas'].shift(1).fillna(df['gas'])

# 3. co_delta = co - co_lag_1
df['co_delta'] = df['co'] - df['co'].shift(1).fillna(df['co'])

# 4. Lag columns
df['gas_lag_1'] = df['gas'].shift(1)
df['co_lag_1'] = df['co'].shift(1)
df['gas_lag_3'] = df['gas'].shift(3)
df['co_lag_3'] = df['co'].shift(3)
df['gas_lag_5'] = df['gas'].shift(5)
df['co_lag_5'] = df['co'].shift(5)

# 5. gas_volatility = rolling standard deviation of gas (window=5)
df['gas_volatility'] = df['gas'].rolling(window=5, min_periods=1).std().fillna(0)

# 6. gas_trend = slope of linear regression over last 5 points
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

df['gas_trend'] = calculate_trend(df['gas'])

# 7. gas_acceleration = second derivative (change in gas_delta)
gas_delta = df['gas_delta'].fillna(0)
df['gas_acceleration'] = gas_delta - gas_delta.shift(1).fillna(0)

# 8. is_gas_accelerating = 1 if gas_acceleration > threshold, else 0
threshold = 1.0  # ADC-based threshold (larger than PPM threshold)
df['is_gas_accelerating'] = (df['gas_acceleration'].abs() > threshold).astype(int)

# Fill NaN values in lag columns with current values
df['gas_lag_1'] = df['gas_lag_1'].fillna(df['gas'])
df['co_lag_1'] = df['co_lag_1'].fillna(df['co'])
df['gas_lag_3'] = df['gas_lag_3'].fillna(df['gas'])
df['co_lag_3'] = df['co_lag_3'].fillna(df['co'])
df['gas_lag_5'] = df['gas_lag_5'].fillna(df['gas'])
df['co_lag_5'] = df['co_lag_5'].fillna(df['co'])

# Remove the temporary gas and co columns (keep MQ2_ADC and MQ7_ADC)
df = df.drop(columns=['gas', 'co'])

# Save the updated file
df.to_csv('dataset/combined_data.csv', index=False)

print("✅ Updated combined_data.csv with recalculated derived columns!")
print(f"Total rows processed: {len(df)}")

# Show sample of updated columns
print("\nSample of updated columns:")
sample_cols = ['MQ2_ADC', 'MQ7_ADC', 'gas_co_ratio', 'gas_delta', 'co_delta', 'gas_acceleration', 'gas_volatility', 'gas_trend', 'is_gas_accelerating']
print(df[sample_cols].head())
