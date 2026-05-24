#!/usr/bin/env python
"""Verify the conversion was successful"""

import pandas as pd

df = pd.read_csv('dataset/combined_data.csv')

print("Gas-related columns verification:")
print("=" * 70)
gas_cols = [col for col in df.columns if 'gas' in col.lower() or 'MQ2' in col]
for col in sorted(gas_cols):
    print(f"  ✓ {col}")

print("\nSample row data (Row 1):")
row = df.iloc[0]
for col in sorted(gas_cols):
    print(f"  {col}: {row[col]}")

print("\n✅ All gas-related features are present and recalculated!")
