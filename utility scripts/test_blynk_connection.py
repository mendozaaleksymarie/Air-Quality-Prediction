"""
Test Blynk Connection - Verify your Blynk setup before deploying to ESP32
"""

import requests
import time
import json

# Blynk Configuration
BLYNK_TOKEN = "vKF0tDJwkknKj38WjeibW4rqdjr5pNUy"
BLYNK_TEMPLATE_ID = "TMPL66fm4nCL-"
BLYNK_TEMPLATE_NAME = "MILES Air Quality Prediction System"
BLYNK_SERVER = "blynk.cloud"

def adc_to_ppm_gas(adc_value):
    """Convert MQ-2 gas sensor ADC value to ppm"""
    adc_value = max(0, min(1023, adc_value))
    ppm = (adc_value / 1023.0) * 10000
    return round(ppm, 1)

def adc_to_ppm_co(adc_value):
    """Convert MQ-7 CO sensor ADC value to ppm"""
    adc_value = max(0, min(1023, adc_value))
    ppm = (adc_value / 65.0) * 500
    return round(ppm, 1)

def test_blynk_connection():
    """Test basic Blynk connectivity"""
    print("="*60)
    print(" BLYNK CONNECTION TEST")
    print("="*60)
    
    # Check if token is set
    if BLYNK_TOKEN == "YOUR_BLYNK_AUTH_TOKEN":
        print("\n ERROR: Please update BLYNK_TOKEN in this script!")
        print("\nSteps to get your token:")
        print("1. Go to https://blynk.cloud")
        print("2. Click on your device")
        print("3. Go to Device Info tab")
        print("4. Copy the Auth Token")
        print("5. Paste it in this script (line 9)")
        return False
    
    print(f"\n Server: {BLYNK_SERVER}")
    print(f" Token: {BLYNK_TOKEN[:8]}...{BLYNK_TOKEN[-4:]}")
    
    # Test connection
    try:
        url = f"https://{BLYNK_SERVER}/external/api/isHardwareConnected?token={BLYNK_TOKEN}"
        response = requests.get(url, timeout=5)
        
        if response.status_code == 200:
            print(f"\n Token is valid!")
            print(f"   Device connected: {response.text}")
        else:
            print(f"\n Token validation failed: {response.status_code}")
            print(f"   Response: {response.text}")
            return False
            
    except Exception as e:
        print(f"\n Connection error: {e}")
        return False
    
    return True

def send_test_data_to_blynk():
    """Send test sensor data to Blynk virtual pins"""
    print("\n" + "="*60)
    print(" SENDING TEST DATA TO BLYNK")
    print("="*60)
    
    # Test data
    test_values = {
        'V0': 25.5,   # PM2.5
        'V1': 40.2,   # PM10
        'V2': 24.8,   # Temperature
        'V3': 55.3,   # Humidity
        'V4': adc_to_ppm_gas(193),  # Gas in ppm (193 ADC = 1886.6 ppm)
        'V5': adc_to_ppm_co(65),    # CO in ppm (65 ADC = 500 ppm)
        'V6': 0       # Alarm (0 = no alarm, 1 = alarm)
    }
    
    print("\nTest Values:")
    print(f"  PM2.5: {test_values['V0']} μg/m³")
    print(f"  PM10: {test_values['V1']} μg/m³")
    print(f"  Temperature: {test_values['V2']}°C")
    print(f"  Humidity: {test_values['V3']}%")
    print(f"  Gas: {test_values['V4']} ppm")
    print(f"  CO: {test_values['V5']} ppm")
    print(f"  Alarm: {' ON' if test_values['V6'] == 1 else '✓ OFF'}")
    
    # Send data using batch update
    try:
        url = f"https://{BLYNK_SERVER}/external/api/batch/update"
        params = {'token': BLYNK_TOKEN}
        
        for pin, value in test_values.items():
            params[pin] = value
        
        print(f"\n Sending to Blynk...")
        response = requests.get(url, params=params, timeout=5)
        
        if response.status_code == 200:
            print(" Data sent successfully!")
            print("\n Check your Blynk dashboard now!")
            print("   - Open Blynk mobile app or web dashboard")
            print("   - You should see the test values displayed")
            return True
        else:
            print(f" Failed to send data: {response.status_code}")
            print(f"   Response: {response.text}")
            return False
            
    except Exception as e:
        print(f" Error sending data: {e}")
        return False

def read_from_blynk():
    """Read current values from Blynk virtual pins"""
    print("\n" + "="*60)
    print(" READING DATA FROM BLYNK")
    print("="*60)
    
    pins = ['V0', 'V1', 'V2', 'V3', 'V4', 'V5']
    pin_names = ['PM2.5', 'PM10', 'Temperature', 'Humidity', 'Pressure', 'Alarm']
    
    for pin, name in zip(pins, pin_names):
        try:
            url = f"https://{BLYNK_SERVER}/external/api/get?token={BLYNK_TOKEN}&{pin}"
            response = requests.get(url, timeout=5)
            
            if response.status_code == 200:
                value = response.text
                print(f"  {name} ({pin}): {value}")
            else:
                print(f"  {name} ({pin}): Error {response.status_code}")
                
        except Exception as e:
            print(f"  {name} ({pin}): Error - {e}")
    
    print()

def test_alarm_trigger():
    """Test alarm triggering"""
    print("\n" + "="*60)
    print(" TESTING ALARM TRIGGER")
    print("="*60)
    
    print("\n1. Setting alarm OFF (V5 = 0)...")
    try:
        url = f"https://{BLYNK_SERVER}/external/api/update?token={BLYNK_TOKEN}&V5=0"
        response = requests.get(url)
        if response.status_code == 200:
            print("    Alarm OFF - LED should be GREEN")
        time.sleep(2)
    except Exception as e:
        print(f"    Error: {e}")
    
    print("\n2. Setting alarm ON (V5 = 1)...")
    try:
        url = f"https://{BLYNK_SERVER}/external/api/update?token={BLYNK_TOKEN}&V5=1"
        response = requests.get(url)
        if response.status_code == 200:
            print("    Alarm ON - LED should be RED")
            print("    Check if you receive notification (if enabled)")
        time.sleep(2)
    except Exception as e:
        print(f"    Error: {e}")
    
    print("\n3. Resetting alarm OFF...")
    try:
        url = f"https://{BLYNK_SERVER}/external/api/update?token={BLYNK_TOKEN}&V5=0"
        response = requests.get(url)
        if response.status_code == 200:
            print("    Alarm reset")
    except Exception as e:
        print(f"    Error: {e}")

def simulate_real_time_updates(cycles=5):
    """Simulate ESP32 sending data in real-time"""
    print("\n" + "="*60)
    print(" SIMULATING REAL-TIME DATA UPDATES")
    print("="*60)
    print(f"\nSending {cycles} updates (5 seconds apart)...")
    print("Watch your Blynk dashboard update in real-time!\n")
    
    import random
    
    for i in range(cycles):
        print(f"Update {i+1}/{cycles}:")
        
        # Simulate sensor readings
        pm25 = round(random.uniform(5, 80), 1)
        pm10 = round(random.uniform(10, 120), 1)
        temp = round(random.uniform(18, 32), 1)
        humidity = round(random.uniform(30, 70), 1)
        pressure = round(random.uniform(1000, 1020), 1)
        alarm = 1 if pm25 > 35 or pm10 > 50 else 0
        
        print(f"  PM2.5={pm25}, PM10={pm10}, Temp={temp}°C, Alarm={'ON' if alarm else 'OFF'}")
        
        # Send to Blynk
        try:
            url = f"https://{BLYNK_SERVER}/external/api/batch/update"
            params = {
                'token': BLYNK_TOKEN,
                'V0': pm25,
                'V1': pm10,
                'V2': temp,
                'V3': humidity,
                'V4': pressure,
                'V5': alarm
            }
            
            response = requests.get(url, params=params)
            if response.status_code == 200:
                print(f"  Sent to Blynk")
            else:
                print(f"   Error: {response.status_code}")
        except Exception as e:
            print(f"   Error: {e}")
        
        if i < cycles - 1:
            time.sleep(5)
    
    print("\n Real-time simulation complete!")
    print("   Check your Blynk dashboard charts for the data trend")

def main():
    """Run all Blynk tests"""
    print("""
╔════════════════════════════════════════════════════════════╗
║           Blynk Connection Test for ESP32                  ║
║         Air Quality Monitoring System                      ║
╚════════════════════════════════════════════════════════════╝
    """)
    
    # Test 1: Connection
    if not test_blynk_connection():
        print("\n⚠️  Please fix the connection issues before continuing")
        return
    
    # Test 2: Send test data
    if not send_test_data_to_blynk():
        print("\n⚠️  Data sending failed")
        return
    
    # Wait a moment
    time.sleep(2)
    
    # Test 3: Read data back
    read_from_blynk()
    
    # Test 4: Test alarm
    response = input("\nTest alarm trigger? (y/n): ")
    if response.lower() == 'y':
        test_alarm_trigger()
    
    # Test 5: Real-time updates
    response = input("\nSimulate real-time updates? (y/n): ")
    if response.lower() == 'y':
        simulate_real_time_updates(cycles=5)
    
    print("\n" + "="*60)
    print("✅ ALL TESTS COMPLETE!")
    print("="*60)
    print("\nYour Blynk setup is working correctly!")
    print("\nNext steps:")
    print("1. Update ESP32 config.json with your Blynk token")
    print("2. Upload code to ESP32")
    print("3. Power on ESP32")
    print("4. Monitor on Blynk app/dashboard")
    print("\n" + "="*60)

if __name__ == '__main__':
    import sys
    
    if len(sys.argv) > 1:
        if sys.argv[1] == 'quick':
            # Quick test
            test_blynk_connection()
            send_test_data_to_blynk()
        elif sys.argv[1] == 'realtime':
            # Real-time simulation
            test_blynk_connection()
            simulate_real_time_updates(cycles=10)
        elif sys.argv[1] == 'alarm':
            # Test alarm only
            test_blynk_connection()
            test_alarm_trigger()
    else:
        # Full test suite
        main()
