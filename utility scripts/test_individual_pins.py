"""
Test each virtual pin individually to identify which ones are missing
"""
import requests

BLYNK_TOKEN = "vKF0tDJwkknKj38WjeibW4rqdjr5pNUy"
BLYNK_SERVER = "blynk.cloud"

print("="*60)
print("TESTING EACH VIRTUAL PIN INDIVIDUALLY")
print("="*60)

pins_to_test = {
    'V0': 25.5,    # PM2.5
    'V1': 40.2,    # PM10
    'V2': 24.8,    # Temperature
    'V3': 55.3,    # Humidity
    'V4': 2150.5,  # Gas (ppm)
    'V5': 293.3,   # CO (ppm)
    'V6': 0        # Alarm
}

pin_names = {
    'V0': 'PM2.5',
    'V1': 'PM10',
    'V2': 'Temperature',
    'V3': 'Humidity',
    'V4': 'Gas',
    'V5': 'CO',
    'V6': 'Alarm'
}

print("\nTesting each pin...")
for pin, value in pins_to_test.items():
    try:
        url = f"https://{BLYNK_SERVER}/external/api/update"
        params = {'token': BLYNK_TOKEN, 'pin': pin, 'value': value}
        response = requests.get(url, params=params, timeout=5)
        
        if response.status_code == 200:
            print(f"✅ {pin} ({pin_names[pin]}): {value} - SUCCESS")
        else:
            print(f"❌ {pin} ({pin_names[pin]}): {value} - FAILED ({response.status_code})")
            print(f"   Error: {response.text}")
    except Exception as e:
        print(f"❌ {pin} ({pin_names[pin]}): ERROR - {e}")

print("\n" + "="*60)
print("If any pin shows FAILED, you need to add it in Blynk app:")
print("  1. Open Blynk Console (blynk.cloud)")
print("  2. Go to Templates > MILES Air Quality Prediction System")
print("  3. Click 'Datastreams' tab")
print("  4. Add missing virtual pins")
print("="*60)
