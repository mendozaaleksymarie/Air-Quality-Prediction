import pandas as pd
import os

# Check the first few rows and columns of one of the new files
dataset_folder = 'dataset'
file = '03-16-2026 (Inside of Temfacil).csv'
path = os.path.join(dataset_folder, file)

df = pd.read_csv(path)
print(f"File: {file}")
print(f"Columns: {df.columns.tolist()}")
print(f"\nFirst 5 rows:")
print(df.head())
print(f"\nData shape: {df.shape}")
