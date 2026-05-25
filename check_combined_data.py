import pandas as pd

combined_path = r'dataset\combined_data.csv'
df = pd.read_csv(combined_path, nrows=5)
print("Combined_data.csv columns:")
print(df.columns.tolist())
print("\nFirst 5 rows:")
print(df)
print(f"\nTotal rows: {len(pd.read_csv(combined_path))}")
