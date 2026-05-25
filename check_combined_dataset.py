import pandas as pd

combined_dataset_path = 'dataset/combined_dataset.csv'
df = pd.read_csv(combined_dataset_path, nrows=2)
print("Columns in combined_dataset.csv:")
print(df.columns.tolist())
print("\nFirst row data:")
print(df.iloc[0])
