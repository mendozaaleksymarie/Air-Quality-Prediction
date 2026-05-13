import pandas as pd

# Load combined_dataset.csv
df = pd.read_csv('dataset/combined_dataset.csv')

# Apply scaling factors
df['MQ2_ADC'] = (df['MQ2_ADC'] * 0.9427).round(2)
df['MQ7_ADC'] = (df['MQ7_ADC'] * 0.9449).round(2)

# Save back to file
df.to_csv('dataset/combined_dataset.csv', index=False)

print('✅ combined_dataset.csv updated')
print(f'Rows: {len(df)}')
print(f'MQ2_ADC range: {df["MQ2_ADC"].min():.2f} - {df["MQ2_ADC"].max():.2f}')
print(f'MQ7_ADC range: {df["MQ7_ADC"].min():.2f} - {df["MQ7_ADC"].max():.2f}')
