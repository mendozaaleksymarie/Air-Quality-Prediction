import pandas as pd
import numpy as np

print("="*60)
print("Updating combined_data.csv with new MQ7_ADC values")
print("="*60)

# Read the updated combined_dataset.csv which has correct MQ7_ADC values
combined_dataset_path = 'dataset/combined_dataset.csv'
combined_data_path = 'dataset/combined_data.csv'

# Read files
combined_dataset = pd.read_csv(combined_dataset_path)
combined_data = pd.read_csv(combined_data_path)

print(f"\nLoaded combined_dataset.csv: {len(combined_dataset)} rows")
print(f"Loaded combined_data.csv: {len(combined_data)} rows")

# Create mapping from created_at timestamp to MQ7_ADC value
# First, normalize timestamps to match between the two files
# combined_dataset has: 'Timestamp' (format: 2026-03-16 08:30:07 UTC)
# combined_data has: 'created_at' (format: 2026-03-16 08:30:07+00:00)

# Extract just the date and time part from created_at (remove timezone)
combined_data['timestamp_normalized'] = pd.to_datetime(combined_data['created_at']).dt.strftime('%Y-%m-%d %H:%M:%S')
# Normalize combined_dataset timestamps
combined_dataset['timestamp_normalized'] = combined_dataset['Timestamp'].str.replace(' UTC', '')

# Create mapping
# Note: The column is named MQ7_PPM but now contains MQ7_ADC values
timestamp_to_mq7_adc = dict(zip(combined_dataset['timestamp_normalized'], combined_dataset['MQ7_PPM']))
print(f"\nCreated mapping with {len(timestamp_to_mq7_adc)} unique timestamps")

# Update co column with MQ7_ADC values
matched_count = 0
for idx, row in combined_data.iterrows():
    ts = row['timestamp_normalized']
    if ts in timestamp_to_mq7_adc:
        combined_data.at[idx, 'co'] = timestamp_to_mq7_adc[ts]
        matched_count += 1

print(f"Matched and updated {matched_count} rows")

# Now recalculate all CO-dependent derived columns
print("\nRecalculating CO-dependent derived columns...")

# gas_co_ratio
combined_data['gas_co_ratio'] = combined_data['gas'] / combined_data['co']

# co_delta (change from previous row)
combined_data['co_delta'] = combined_data['co'].diff().fillna(0)

# co_lag_1, co_lag_3, co_lag_5
combined_data['co_lag_1'] = combined_data['co'].shift(1).fillna(combined_data['co'])
combined_data['co_lag_3'] = combined_data['co'].shift(3).fillna(combined_data['co'])
combined_data['co_lag_5'] = combined_data['co'].shift(5).fillna(combined_data['co'])

# Recalculate gas-dependent columns as well
combined_data['gas_delta'] = combined_data['gas'].diff().fillna(0)
combined_data['gas_lag_1'] = combined_data['gas'].shift(1).fillna(combined_data['gas'])
combined_data['gas_lag_3'] = combined_data['gas'].shift(3).fillna(combined_data['gas'])
combined_data['gas_lag_5'] = combined_data['gas'].shift(5).fillna(combined_data['gas'])

# gas_acceleration (rate of change of gas)
combined_data['gas_acceleration'] = combined_data['gas_delta'].diff().fillna(0)

# gas_trend (positive/negative indication)
combined_data['gas_trend'] = combined_data['gas_delta'].apply(lambda x: 1 if x > 0 else (-1 if x < 0 else 0))

# is_gas_accelerating
combined_data['is_gas_accelerating'] = (combined_data['gas_acceleration'] > 0).astype(int)

# gas_volatility (rolling standard deviation)
combined_data['gas_volatility'] = combined_data['gas'].rolling(window=5, min_periods=1).std().fillna(0)

print("✓ Recalculated all CO-dependent derived columns")

# Drop the temporary normalized timestamp column
combined_data = combined_data.drop('timestamp_normalized', axis=1)

# Save the updated file
combined_data.to_csv(combined_data_path, index=False)
print(f"\n✓ combined_data.csv saved with {len(combined_data)} rows")
print("✓ All updates completed!")

# Show sample of updated data
print("\n" + "="*60)
print("Sample of updated data (first 5 rows, key columns):")
print("="*60)
print(combined_data[['created_at', 'gas', 'co', 'gas_co_ratio', 'co_delta', 'gas_volatility']].head())
