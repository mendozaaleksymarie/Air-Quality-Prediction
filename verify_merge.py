import pandas as pd

# Load and display summary
df = pd.read_csv(r'c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\dataset\combined_dataset.csv')

print('=' * 80)
print('Updated combined_dataset.csv Summary')
print('=' * 80)
print(f'Total Rows: {len(df):,}')
print(f'Columns: {list(df.columns)}')
print(f'\nClass Distribution:')
print(df['Status'].value_counts())
print(f'\nDate Range: {df["Timestamp"].min()} to {df["Timestamp"].max()}')
print(f'\nFirst 3 rows:')
print(df.head(3))
print(f'\nLast 3 rows:')
print(df.tail(3))
print('=' * 80)
