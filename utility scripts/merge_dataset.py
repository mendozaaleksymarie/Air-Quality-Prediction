"""
Merge Individual CSV Files into Combined Dataset

This script merges all individual sensor CSV files from the dataset folder
into a single combined_data.csv file that can be used by the ML notebooks and scripts.

Input Files (from dataset folder):
- Carbon Monoxide.csv (field4)
- Gas.csv (field3)
- Humidity.csv (field2)
- PM10.csv (field7)
- PM2.5.csv (field6)
- Temperature.csv (field1)

Output File:
- combined_data.csv (in dataset folder)

The combined file will have columns:
- created_at, pm2_5, pm10, temp, humidity, gas, co, alarm_status
"""

import pandas as pd
import os

def merge_sensor_data():
    """Merge all sensor CSV files into a combined dataset"""
    
    # Define paths with exact case-sensitive names
    dataset_folder = os.path.join(os.path.dirname(__file__), 'dataset')
    
    csv_files = {
        'pm2_5': 'PM2.5.csv',
        'pm10': 'PM10.csv',
        'temp': 'Temperature.csv',
        'humidity': 'Humidity.csv',
        'gas': 'Gas.csv',
        'co': 'Carbon Monoxide.csv'
    }
    
    print("Loading individual CSV files...")
    dataframes = {}
    
    # Load each CSV file
    for key, filename in csv_files.items():
        filepath = os.path.join(dataset_folder, filename)
        if os.path.exists(filepath):
            df = pd.read_csv(filepath)
            print(f"  ✓ Loaded {filename}: {len(df)} rows")
            
            # Rename the field column to the parameter name
            if len(df.columns) >= 3:
                field_col = df.columns[2]  # The third column is the actual data
                df = df.rename(columns={field_col: key})
                # Keep only created_at and the parameter column
                df = df[['created_at', key]]
                # Convert the parameter column to numeric, replacing empty strings with NaN
                df[key] = pd.to_numeric(df[key], errors='coerce')
                dataframes[key] = df
            else:
                print(f"  ⚠ Warning: {filename} doesn't have expected structure")
        else:
            print(f"  ✗ File not found: {filename}")
    
    if not dataframes:
        print("\n❌ No CSV files found! Please check the dataset folder.")
        return
    
    print("\nMerging dataframes...")
    # Start with the first dataframe
    combined_df = None
    for key, df in dataframes.items():
        if combined_df is None:
            combined_df = df
            print(f"  Base: {key}")
        else:
            # Merge on created_at timestamp
            combined_df = pd.merge(combined_df, df, on='created_at', how='outer')
            print(f"  + Merged: {key}")
    
    # Convert created_at to datetime
    combined_df['created_at'] = pd.to_datetime(combined_df['created_at'])
    
    # Sort by timestamp
    combined_df = combined_df.sort_values('created_at')
    
    # Calculate alarm_status based on thresholds from the reference table
    print("\nCalculating alarm_status based on sensor thresholds...")
    
    def calculate_alarm(row):
        """
        Determine alarm status based on hazardous level thresholds:
        - PM2.5 > 100 μg/m³
        - PM10 > 230 μg/m³
        - Temperature > 35 °C
        - Humidity > 70 %
        - Gas (MQ-2) ≥ 176 ppm (Smoke/Combustible Gases)
        - Carbon Monoxide > 30 ppm (RA 8749 IRR)
        """
        alarm = 0
        
        if pd.notna(row.get('pm2_5')) and row['pm2_5'] > 100:
            alarm = 1
        elif pd.notna(row.get('pm10')) and row['pm10'] > 230:
            alarm = 1
        elif pd.notna(row.get('temp')) and row['temp'] > 35:
            alarm = 1
        elif pd.notna(row.get('humidity')) and row['humidity'] > 70:
            alarm = 1
        elif pd.notna(row.get('gas')) and row['gas'] >= 176:
            alarm = 1
        elif pd.notna(row.get('co')) and row['co'] > 30:
            alarm = 1
            
        return alarm
    
    combined_df['alarm_status'] = combined_df.apply(calculate_alarm, axis=1)
    
    # Handle missing values - forward fill then backward fill
    print("Handling missing values...")
    combined_df = combined_df.fillna(method='ffill').fillna(method='bfill')
    
    # Save to combined_data.csv
    output_path = os.path.join(dataset_folder, 'combined_data.csv')
    combined_df.to_csv(output_path, index=False)
    
    print(f"\n✓ Successfully created combined dataset!")
    print(f"  Output: {output_path}")
    print(f"  Total rows: {len(combined_df)}")
    print(f"  Columns: {', '.join(combined_df.columns)}")
    print(f"\nAlarm distribution:")
    print(f"  No alarm (0): {(combined_df['alarm_status'] == 0).sum()}")
    print(f"  Alarm (1): {(combined_df['alarm_status'] == 1).sum()}")
    
    # Display first few rows
    print("\nFirst 5 rows:")
    print(combined_df.head())
    
    # Display basic statistics
    print("\nBasic statistics:")
    print(combined_df.describe())
    
    return combined_df

if __name__ == "__main__":
    print("="*60)
    print("IoT Air Quality - Dataset Merger")
    print("="*60)
    print()
    
    try:
        df = merge_sensor_data()
        print("\n" + "="*60)
        print("✓ Merge completed successfully!")
        print("="*60)
    except Exception as e:
        print(f"\n❌ Error during merge: {str(e)}")
        import traceback
        traceback.print_exc()
