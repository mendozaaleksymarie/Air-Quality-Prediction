"""
Send Real Sensor Data from CSV to Blynk Dashboard
Uses actual data from combined_data.csv instead of hardcoded values
"""

import pandas as pd
import requests
import time
import os

# Blynk Configuration
BLYNK_TOKEN = "vKF0tDJwkknKj38WjeibW4rqdjr5pNUy"
BLYNK_TEMPLATE_ID = "TMPL66fm4nCL-"
BLYNK_TEMPLATE_NAME = "MILES Air Quality Prediction System"
BLYNK_SERVER = "blynk.cloud"

# Dataset path
DATASET_PATH = os.path.join(os.path.dirname(__file__), '..', 'dataset', 'combined_data.csv')

def adc_to_ppm_gas(adc_value):
    """
    Convert MQ-2 gas sensor ADC value (0-1023) to ppm
    Calibrated conversion: ADC 193 -> 1886.6 ppm
    """
    # Clamp ADC value
    adc_value = max(0, min(1023, adc_value))
    
    # Calibrated conversion for MQ-2 gas sensor
    # Formula: ppm = (ADC / 1023) * 10000
    ppm = (adc_value / 1023.0) * 10000
    
    return round(ppm, 1)

def adc_to_ppm_co(adc_value):
    """
    Convert MQ-7 CO sensor ADC value (0-1023) to ppm
    Calibrated conversion: ADC 65 -> 500 ppm
    """
    # Clamp ADC value
    adc_value = max(0, min(1023, adc_value))
    
    # Calibrated conversion for MQ-7 CO sensor
    # Formula: ppm = (ADC / 65) * 500 = ADC * 7.692
    ppm = (adc_value / 65.0) * 500
    
    return round(ppm, 1)

def load_sensor_data():
    """Load sensor data from CSV file"""
    print("="*60)
    print(" LOADING SENSOR DATA FROM CSV")
    print("="*60)
    
    if not os.path.exists(DATASET_PATH):
        print(f"\n ERROR: Dataset not found at {DATASET_PATH}")
        return None
    
    df = pd.read_csv(DATASET_PATH)
    print(f"\n Loaded {len(df)} records from combined_data.csv")
    print(f" Columns: {', '.join(df.columns)}")
    
    # Display data range
    print(f"\n Data Summary:")
    print(f"   PM2.5: {df['pm2_5'].min():.1f} - {df['pm2_5'].max():.1f} μg/m³")
    print(f"   PM10:  {df['pm10'].min():.1f} - {df['pm10'].max():.1f} μg/m³")
    print(f"   Temp:  {df['temp'].min():.1f} - {df['temp'].max():.1f} °C")
    print(f"   Humidity: {df['humidity'].min():.1f} - {df['humidity'].max():.1f} %")
    print(f"   Gas:   {df['gas'].min():.1f} - {df['gas'].max():.1f}")
    print(f"   CO:    {df['co'].min():.1f} - {df['co'].max():.1f}")
    print(f"   Alarms: {df['alarm_status'].sum()} / {len(df)} records")
    
    return df

def send_data_to_blynk(row_data):
    """Send a single row of sensor data to Blynk"""
    
    # Map CSV columns to Blynk virtual pins
    blynk_data = {
        'V0': float(row_data['pm2_5']),      # PM2.5
        'V1': float(row_data['pm10']),       # PM10
        'V2': float(row_data['temp']),       # Temperature
        'V3': float(row_data['humidity']),   # Humidity
        'V4': adc_to_ppm_gas(float(row_data['gas'])),  # Gas converted to ppm
        'V5': adc_to_ppm_co(float(row_data['co'])),    # CO converted to ppm
        'V6': int(row_data['alarm_status'])  # Alarm status
    }
    
    try:
        url = f"https://{BLYNK_SERVER}/external/api/batch/update"
        params = {'token': BLYNK_TOKEN}
        
        for pin, value in blynk_data.items():
            params[pin] = value
        
        response = requests.get(url, params=params, timeout=5)
        
        if response.status_code == 200:
            return True, blynk_data
        else:
            return False, None
            
    except Exception as e:
        print(f" Error: {e}")
        return False, None

def send_single_record():
    """Send a single record from the dataset"""
    print("\n" + "="*60)
    print(" SEND SINGLE RECORD TO BLYNK")
    print("="*60)
    
    df = load_sensor_data()
    if df is None:
        return
    
    # Let user choose record or pick random
    print("\nOptions:")
    print("  1. Send first record")
    print("  2. Send last record")
    print("  3. Send random record")
    print("  4. Send record with alarm")
    print("  5. Send record without alarm")
    
    choice = input("\nEnter choice (1-5): ").strip()
    
    if choice == '1':
        row = df.iloc[0]
        index = 0
    elif choice == '2':
        row = df.iloc[-1]
        index = len(df) - 1
    elif choice == '3':
        index = df.sample(1).index[0]
        row = df.iloc[index]
    elif choice == '4':
        alarm_records = df[df['alarm_status'] == 1]
        if len(alarm_records) == 0:
            print("No alarm records found!")
            return
        index = alarm_records.sample(1).index[0]
        row = df.iloc[index]
    elif choice == '5':
        safe_records = df[df['alarm_status'] == 0]
        if len(safe_records) == 0:
            print("No safe records found!")
            return
        index = safe_records.sample(1).index[0]
        row = df.iloc[index]
    else:
        print("Invalid choice")
        return
    
    print(f"\nSending record #{index}:")
    print(f"  Time: {row['created_at']}")
    print(f"  PM2.5: {row['pm2_5']:.1f} μg/m³")
    print(f"  PM10: {row['pm10']:.1f} μg/m³")
    print(f"  Temperature: {row['temp']:.1f} °C")
    print(f"  Humidity: {row['humidity']:.1f} %")
    print(f"  Gas: {row['gas']:.1f}")
    print(f"  CO: {row['co']:.1f}")
    print(f"  Alarm: {'🔴 ON' if row['alarm_status'] == 1 else '🟢 OFF'}")
    
    success, data = send_data_to_blynk(row)
    
    if success:
        print("\n✅ Data sent successfully to Blynk!")
        print("   Check your dashboard to see the real sensor data")
    else:
        print("\n❌ Failed to send data")

def simulate_realtime_updates():
    """Send multiple records to simulate real-time monitoring"""
    print("\n" + "="*60)
    print(" SIMULATE REAL-TIME MONITORING")
    print("="*60)
    
    df = load_sensor_data()
    if df is None:
        return
    
    # Ask for number of updates
    try:
        num_updates = int(input("\nHow many records to send? (1-20): ").strip())
        num_updates = min(max(num_updates, 1), 20)
    except:
        num_updates = 10
    
    # Ask for delay between updates
    try:
        delay = float(input("Delay between updates (seconds, 1-10): ").strip())
        delay = min(max(delay, 1), 10)
    except:
        delay = 3
    
    # Choose data source
    print("\nData source:")
    print("  1. Sequential (starting from first record)")
    print("  2. Random records")
    print("  3. Only alarm records")
    
    source = input("Choice (1-3): ").strip()
    
    if source == '3':
        df = df[df['alarm_status'] == 1]
        if len(df) == 0:
            print("No alarm records available!")
            return
    
    print(f"\n🚀 Sending {num_updates} updates with {delay}s delay...")
    print("   Watch your Blynk dashboard update in real-time!\n")
    
    for i in range(num_updates):
        if source == '1':
            # Sequential
            index = min(i, len(df) - 1)
            row = df.iloc[index]
        else:
            # Random
            row = df.sample(1).iloc[0]
        
        print(f"Update {i+1}/{num_updates}:")
        print(f"  PM2.5={row['pm2_5']:.1f}, PM10={row['pm10']:.1f}, "
              f"Temp={row['temp']:.1f}°C, Gas={row['gas']:.1f}, "
              f"Alarm={'ON' if row['alarm_status']==1 else 'OFF'}")
        
        success, data = send_data_to_blynk(row)
        
        if success:
            print(f"  ✅ Sent to Blynk")
        else:
            print(f"  ❌ Failed")
        
        if i < num_updates - 1:
            time.sleep(delay)
    
    print(f"\n✅ Sent {num_updates} real sensor records to Blynk!")
    print("   Check your dashboard charts for the data trend")

def show_statistics():
    """Show statistics about the dataset"""
    print("\n" + "="*60)
    print(" DATASET STATISTICS")
    print("="*60)
    
    df = load_sensor_data()
    if df is None:
        return
    
    print("\nGas Threshold Analysis:")
    safe = len(df[df['gas'] <= 250])
    caution = len(df[(df['gas'] > 250) & (df['gas'] <= 400)])
    hazard = len(df[df['gas'] > 400])
    
    print(f"  Safe (≤250):      {safe:3d} records ({safe/len(df)*100:.1f}%)")
    print(f"  Caution (250-400): {caution:3d} records ({caution/len(df)*100:.1f}%)")
    print(f"  Hazard (>400):     {hazard:3d} records ({hazard/len(df)*100:.1f}%)")
    
    print("\nAlarm Distribution:")
    print(f"  No Alarm: {(df['alarm_status']==0).sum()} records")
    print(f"  Alarm ON: {(df['alarm_status']==1).sum()} records")
    
    print("\nTop 5 Highest PM2.5 readings:")
    top_pm25 = df.nlargest(5, 'pm2_5')[['created_at', 'pm2_5', 'pm10', 'temp', 'alarm_status']]
    print(top_pm25.to_string(index=False))

def main():
    """Main menu"""
    print("╔════════════════════════════════════════════════════════════╗")
    print("║      Blynk CSV Data Sender - Real Sensor Data             ║")
    print("║      MILES Air Quality Prediction System                  ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    while True:
        print("\n" + "="*60)
        print(" MAIN MENU")
        print("="*60)
        print("\n1. Send single record to Blynk")
        print("2. Simulate real-time monitoring (multiple records)")
        print("3. Show dataset statistics")
        print("4. Exit")
        
        choice = input("\nEnter choice (1-4): ").strip()
        
        if choice == '1':
            send_single_record()
        elif choice == '2':
            simulate_realtime_updates()
        elif choice == '3':
            show_statistics()
        elif choice == '4':
            print("\n👋 Goodbye!")
            break
        else:
            print("Invalid choice. Please try again.")
        
        input("\nPress Enter to continue...")

if __name__ == "__main__":
    main()
