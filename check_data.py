import pandas as pd

# Read a sample file
df = pd.read_csv('dataset/03-16-2026 (Inside of Temfacil).csv')

# Show stats
print('MQ2_ppm stats:')
print(f'  Min: {df["MQ2_ppm"].min()}, Max: {df["MQ2_ppm"].max()}, Mean: {df["MQ2_ppm"].mean():.2f}')
print(f'  Sample values: {df["MQ2_ppm"].head(10).tolist()}')

print('\nMQ7_ppm stats:')
print(f'  Min: {df["MQ7_ppm"].min()}, Max: {df["MQ7_ppm"].max()}, Mean: {df["MQ7_ppm"].mean():.2f}')
print(f'  Sample values: {df["MQ7_ppm"].head(10).tolist()}')
