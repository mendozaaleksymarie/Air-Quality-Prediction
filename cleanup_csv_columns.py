#!/usr/bin/env python3
"""
Remove Unnamed columns from all Testing Dataset CSV files
"""

import pandas as pd
from pathlib import Path

testing_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\Testng Dataset"

print("="*70)
print("REMOVING UNNAMED COLUMNS FROM TESTING DATASET")
print("="*70)

csv_files = list(Path(testing_dir).glob("*.csv"))

if not csv_files:
    print(f"❌ No CSV files found in {testing_dir}")
else:
    for csv_file in sorted(csv_files):
        try:
            # Read CSV
            df = pd.read_csv(csv_file)
            
            # Get unnamed columns
            unnamed_cols = [col for col in df.columns if col.startswith('Unnamed')]
            
            if unnamed_cols:
                print(f"\n✓ {csv_file.name}")
                print(f"  Removing columns: {unnamed_cols}")
                
                # Drop unnamed columns
                df = df.drop(columns=unnamed_cols)
                
                # Save cleaned file
                df.to_csv(csv_file, index=False)
                print(f"  Cleaned successfully - {len(df)} rows remaining")
            else:
                print(f"\n✓ {csv_file.name} - No unnamed columns found")
        
        except Exception as e:
            print(f"  ❌ Error: {str(e)}")

print("\n" + "="*70)
print("✓ CLEANUP COMPLETE")
print("="*70)
