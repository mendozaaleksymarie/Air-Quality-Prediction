"""
Test Script: Connect ESP32 with ML Model
This simulates ESP32 sending data to the ML inference server
"""

import requests
import json
import time
import random

# Server configuration
SERVER_URL = "http://localhost:5000/data"  # Change to your server IP

def simulate_sensor_reading():
    """Simulate sensor data from ESP32"""
    # Generate realistic sensor values
    scenarios = [
        # Normal conditions
        {
            'pm25': random.uniform(5, 15),
            'pm10': random.uniform(10, 25),
            'temp': random.uniform(20, 25),
            'humidity': random.uniform(40, 60),
            'pressure': random.uniform(1010, 1020),
        },
        # High pollution
        {
            'pm25': random.uniform(40, 80),
            'pm10': random.uniform(60, 120),
            'temp': random.uniform(28, 32),
            'humidity': random.uniform(30, 50),
            'pressure': random.uniform(1000, 1010),
        },
        # Mixed conditions
        {
            'pm25': random.uniform(20, 35),
            'pm10': random.uniform(30, 50),
            'temp': random.uniform(22, 28),
            'humidity': random.uniform(45, 65),
            'pressure': random.uniform(1005, 1015),
        }
    ]
    
    return random.choice(scenarios)

def send_data_to_server(sensor_data):
    """Send sensor data to ML inference server (same as ESP32 does)"""
    try:
        print("\n" + "="*60)
        print("📡 Sending sensor data to ML server...")
        print(f"Server: {SERVER_URL}")
        print(f"Data: {json.dumps(sensor_data, indent=2)}")
        
        # Send POST request
        response = requests.post(
            SERVER_URL,
            json=sensor_data,
            headers={'Content-Type': 'application/json'},
            timeout=5
        )
        
        if response.status_code == 200:
            result = response.json()
            print("\n✅ Server Response:")
            print(f"  Status: {result.get('status')}")
            print(f"  AQI Category: {result.get('aqi_category')}")
            print(f"  Prediction: {result.get('prediction')} (0=No Alarm, 1=Alarm)")
            print(f"  Alarm Status: {'🚨 ALARM TRIGGERED!' if result.get('alarm') else '✓ Normal'}")
            
            if 'confidence' in result:
                print(f"  Confidence: {result.get('confidence')*100:.1f}%")
            if 'probability' in result:
                print(f"  Alarm Probability: {result.get('probability')*100:.1f}%")
            
            return result
        else:
            print(f"❌ Server error: {response.status_code}")
            print(f"Response: {response.text}")
            return None
            
    except requests.exceptions.ConnectionError:
        print("❌ Connection Error: Cannot connect to server")
        print("   Make sure the ML inference server is running:")
        print("   python src/ml_inference_server.py")
        return None
    except Exception as e:
        print(f"❌ Error: {e}")
        return None

def test_server_health():
    """Check if server is running"""
    try:
        health_url = SERVER_URL.replace('/data', '/health')
        response = requests.get(health_url, timeout=2)
        if response.status_code == 200:
            health = response.json()
            print("✅ Server is healthy!")
            print(f"   Model loaded: {health.get('model_loaded')}")
            print(f"   Scaler loaded: {health.get('scaler_loaded')}")
            return True
        return False
    except:
        return False

def simulate_esp32_loop(cycles=5, interval=3):
    """Simulate ESP32 sending data in a loop"""
    print("\n" + "="*60)
    print("🔄 ESP32 SIMULATION - Real-time ML Prediction Testing")
    print("="*60)
    
    # Check server health first
    print("\n🔍 Checking server status...")
    if not test_server_health():
        print("\n⚠️  ML Inference Server is not running!")
        print("\nTo start the server, run:")
        print("   python src/ml_inference_server.py")
        return
    
    print(f"\n🚀 Starting simulation: {cycles} cycles, {interval}s interval")
    print("="*60)
    
    results = []
    
    for i in range(cycles):
        print(f"\n--- Cycle {i+1}/{cycles} ---")
        
        # Simulate reading sensors (like ESP32 does)
        sensor_data = simulate_sensor_reading()
        
        # Add timestamp
        sensor_data['timestamp'] = time.time()
        
        # Send to server (like ESP32 does)
        result = send_data_to_server(sensor_data)
        
        if result:
            results.append({
                'cycle': i+1,
                'sensor_data': sensor_data,
                'prediction': result.get('prediction'),
                'alarm': result.get('alarm'),
                'aqi_category': result.get('aqi_category')
            })
        
        # Wait before next reading (like ESP32 sampling interval)
        if i < cycles - 1:
            print(f"\n⏳ Waiting {interval} seconds...")
            time.sleep(interval)
    
    # Summary
    print("\n" + "="*60)
    print("📊 SIMULATION SUMMARY")
    print("="*60)
    
    if results:
        alarm_count = sum(1 for r in results if r['alarm'])
        print(f"Total readings: {len(results)}")
        print(f"Alarms triggered: {alarm_count}")
        print(f"Normal readings: {len(results) - alarm_count}")
        
        print("\nAQI Categories:")
        categories = {}
        for r in results:
            cat = r['aqi_category']
            categories[cat] = categories.get(cat, 0) + 1
        for cat, count in categories.items():
            print(f"  {cat}: {count}")
    
    print("="*60)

def test_specific_scenario():
    """Test with specific sensor values"""
    print("\n" + "="*60)
    print("🧪 TESTING SPECIFIC SCENARIOS")
    print("="*60)
    
    scenarios = [
        {
            'name': 'Clean Air',
            'data': {
                'pm25': 8,
                'pm10': 15,
                'temp': 22,
                'humidity': 50,
                'pressure': 1013
            }
        },
        {
            'name': 'Moderate Pollution',
            'data': {
                'pm25': 30,
                'pm10': 45,
                'temp': 25,
                'humidity': 55,
                'pressure': 1010
            }
        },
        {
            'name': 'High Pollution',
            'data': {
                'pm25': 75,
                'pm10': 120,
                'temp': 30,
                'humidity': 45,
                'pressure': 1005
            }
        },
        {
            'name': 'Hazardous',
            'data': {
                'pm25': 150,
                'pm10': 200,
                'temp': 35,
                'humidity': 40,
                'pressure': 1000
            }
        }
    ]
    
    for scenario in scenarios:
        print(f"\n📋 Scenario: {scenario['name']}")
        send_data_to_server(scenario['data'])
        time.sleep(1)

if __name__ == '__main__':
    import sys
    
    print("""
╔════════════════════════════════════════════════════════════╗
║  ESP32 ↔ ML Model Connection Test                         ║
║  Simulates real-time sensor data and predictions          ║
╚════════════════════════════════════════════════════════════╝
    """)
    
    if len(sys.argv) > 1:
        if sys.argv[1] == 'scenarios':
            test_specific_scenario()
        elif sys.argv[1] == 'health':
            test_server_health()
        else:
            cycles = int(sys.argv[1])
            simulate_esp32_loop(cycles=cycles)
    else:
        # Default: run 5 cycles
        simulate_esp32_loop(cycles=5, interval=3)
        
        # Ask if user wants to test specific scenarios
        print("\n\nRun specific scenarios? (python test_esp32_ml_connection.py scenarios)")
