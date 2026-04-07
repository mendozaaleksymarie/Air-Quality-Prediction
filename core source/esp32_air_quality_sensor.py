"""
ESP32 Air Quality Monitoring System with WiFi and SD Card
Sensors: PMS5003 (PM2.5/PM10), MQ-2, MQ-7, DHT22, BMP180

Blynk Configuration:
  Template ID: TMPL66fm4nCL-
  Template Name: MILES Air Quality Prediction System
  Auth Token: vKF0tDJwkknKj38WjeibW4rqdjr5pNUy
"""

import time
import machine
from machine import Pin, PWM, I2C, UART, SPI
import network
import urequests
import ujson
import dht
import sdcard
import os
import uos

# ==================== PIN CONFIGURATION ====================
# Sensor Pins
DHT_PIN = 4           # DHT22 temperature/humidity sensor
BUZZER_PIN = 25       # Buzzer for alarm
FAN_PIN = 26          # Fan PWM control
MQ2_PIN = 34          # MQ-2 gas sensor (ADC)
MQ7_PIN = 35          # MQ-7 CO sensor (ADC)

# UART for PMS5003 dust sensor
UART_NUM = 2
PMS_RX = 16
PMS_TX = 17

# I2C for BMP180 pressure sensor
I2C_SCL = 22
I2C_SDA = 21

# SD Card SPI pins
SD_SCK = 18
SD_MOSI = 23
SD_MISO = 19
SD_CS = 5

# ==================== CONFIGURATION ====================
# Load config from JSON file
def load_config():
    try:
        with open('config.json', 'r') as f:
            return ujson.load(f)
    except:
        # Default config if file doesn't exist
        return {
            'wifi_ssid': 'YOUR_WIFI_SSID',
            'wifi_password': 'YOUR_WIFI_PASSWORD',
            'server_url': 'http://YOUR_SERVER_IP:5000/data',
            'blynk_token': 'YOUR_BLYNK_TOKEN',
            'blynk_server': 'blynk.cloud',
            'sampling_interval': 15,  # seconds
            'pm25_threshold': 100,
            'pm10_threshold': 230,
            'co_threshold_safe': 9,
            'co_threshold_caution': 30,
            'gas_threshold_safe': 130,
            'gas_threshold_caution': 175,
            'temp_min': 0,
            'temp_max': 35,
            'enable_local_alarm': True,
            'enable_wifi': True,
            'enable_sd_card': True
        }

config = load_config()

# ==================== HARDWARE INITIALIZATION ====================
# DHT22 sensor
dht_sensor = dht.DHT22(Pin(DHT_PIN))

# Buzzer
buzzer = Pin(BUZZER_PIN, Pin.OUT)
buzzer.off()

# Fan with PWM
fan = PWM(Pin(FAN_PIN), freq=25000, duty=0)

# MQ sensors (ADC)
mq2_adc = machine.ADC(Pin(MQ2_PIN))
mq2_adc.atten(machine.ADC.ATTN_11DB)  # 0-3.3V range
mq7_adc = machine.ADC(Pin(MQ7_PIN))
mq7_adc.atten(machine.ADC.ATTN_11DB)

# PMS5003 UART
pms_uart = UART(UART_NUM, baudrate=9600, rx=PMS_RX, tx=PMS_TX)

# I2C for BMP180
i2c = I2C(0, scl=Pin(I2C_SCL), sda=Pin(I2C_SDA), freq=100000)

# BMP180 implementation
class BMP180:
    def __init__(self, i2c):
        self.i2c = i2c
        self.addr = 0x77
        # Calibration coefficients
        self._read_calibration()
        
    def _read_calibration(self):
        # Read calibration data (simplified version)
        cal = self.i2c.readfrom_mem(self.addr, 0xAA, 22)
        self.ac1 = int.from_bytes(cal[0:2], 'big', True)
        self.ac2 = int.from_bytes(cal[2:4], 'big', True)
        self.ac3 = int.from_bytes(cal[4:6], 'big', True)
        self.ac4 = int.from_bytes(cal[6:8], 'big', False)
        self.ac5 = int.from_bytes(cal[8:10], 'big', False)
        self.ac6 = int.from_bytes(cal[10:12], 'big', False)
        self.b1 = int.from_bytes(cal[12:14], 'big', True)
        self.b2 = int.from_bytes(cal[14:16], 'big', True)
        self.mb = int.from_bytes(cal[16:18], 'big', True)
        self.mc = int.from_bytes(cal[18:20], 'big', True)
        self.md = int.from_bytes(cal[20:22], 'big', True)
        
    def read_raw_temp(self):
        self.i2c.writeto_mem(self.addr, 0xF4, b'\x2E')
        time.sleep_ms(5)
        msb = self.i2c.readfrom_mem(self.addr, 0xF6, 1)[0]
        lsb = self.i2c.readfrom_mem(self.addr, 0xF7, 1)[0]
        return (msb << 8) + lsb
        
    def read_raw_pressure(self):
        self.i2c.writeto_mem(self.addr, 0xF4, b'\x34')
        time.sleep_ms(8)
        msb = self.i2c.readfrom_mem(self.addr, 0xF6, 1)[0]
        lsb = self.i2c.readfrom_mem(self.addr, 0xF7, 1)[0]
        xlsb = self.i2c.readfrom_mem(self.addr, 0xF8, 1)[0]
        return ((msb << 16) + (lsb << 8) + xlsb) >> 8
        
    def read_temperature(self):
        ut = self.read_raw_temp()
        x1 = ((ut - self.ac6) * self.ac5) >> 15
        x2 = (self.mc << 11) // (x1 + self.md)
        self.b5 = x1 + x2
        return ((self.b5 + 8) >> 4) / 10.0
        
    def read_pressure(self):
        ut = self.read_raw_temp()
        up = self.read_raw_pressure()
        x1 = ((ut - self.ac6) * self.ac5) >> 15
        x2 = (self.mc << 11) // (x1 + self.md)
        self.b5 = x1 + x2
        b6 = self.b5 - 4000
        x1 = (self.b2 * ((b6 * b6) >> 12)) >> 11
        x2 = (self.ac2 * b6) >> 11
        x3 = x1 + x2
        b3 = (((self.ac1 * 4 + x3) << 0) + 2) // 4
        x1 = (self.ac3 * b6) >> 13
        x2 = (self.b1 * ((b6 * b6) >> 12)) >> 16
        x3 = ((x1 + x2) + 2) >> 2
        b4 = (self.ac4 * (x3 + 32768)) >> 15
        b7 = (up - b3) * 50000
        if b7 < 0x80000000:
            p = (b7 * 2) // b4
        else:
            p = (b7 // b4) * 2
        x1 = (p >> 8) * (p >> 8)
        x1 = (x1 * 3038) >> 16
        x2 = (-7357 * p) >> 16
        return p + ((x1 + x2 + 3791) >> 4)

# Initialize BMP1804 
try:
    bmp180 = BMP180(i2c)
    print("BMP180 initialized")
except Exception as e:
    print(f"BMP180 init error: {e}")
    bmp180 = None

# SD Card initialization
sd = None
if config['enable_sd_card']:
    try:
        spi = SPI(1, baudrate=1000000, polarity=0, phase=0, 
                  sck=Pin(SD_SCK), mosi=Pin(SD_MOSI), miso=Pin(SD_MISO))
        sd = sdcard.SDCard(spi, Pin(SD_CS))
        vfs = uos.VfsFat(sd)
        uos.mount(vfs, '/sd')
        print("SD card mounted at /sd")
    except Exception as e:
        print(f"SD card init error: {e}")
        sd = None

# ==================== WIFI CONNECTION ====================
wlan = None
def connect_wifi():
    global wlan
    if not config['enable_wifi']:
        return False
        
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    
    if not wlan.isconnected():
        print(f"Connecting to WiFi: {config['wifi_ssid']}...")
        wlan.connect(config['wifi_ssid'], config['wifi_password'])
        
        timeout = 10
        while not wlan.isconnected() and timeout > 0:
            print('.', end='')
            time.sleep(1)
            timeout -= 1
        print()
        
    if wlan.isconnected():
        print(f"WiFi connected: {wlan.ifconfig()[0]}")
        return True
    else:
        print("WiFi connection failed")
        return False

# ==================== SENSOR READING FUNCTIONS ====================
def read_pms5003():
    """Read PM2.5 and PM10 from PMS5003 sensor"""
    try:
        while pms_uart.any():
            pms_uart.read()  # Clear buffer
        
        time.sleep_ms(100)
        
        # Wait for start bytes 0x42 0x4D
        while True:
            if pms_uart.any() >= 2:
                header = pms_uart.read(2)
                if header == b'\x42\x4d':
                    break
            time.sleep_ms(10)
        
        # Read remaining 30 bytes
        data = pms_uart.read(30)
        if len(data) == 30:
            # PM2.5 and PM10 values (atmospheric environment)
            pm25 = (data[6] << 8) | data[7]
            pm10 = (data[8] << 8) | data[9]
            return pm25, pm10
        else:
            return None, None
    except Exception as e:
        print(f"PMS5003 error: {e}")
        return None, None

def read_dht22():
    """Read temperature and humidity from DHT22"""
    try:
        dht_sensor.measure()
        temp = dht_sensor.temperature()
        humidity = dht_sensor.humidity()
        return temp, humidity
    except Exception as e:
        print(f"DHT22 error: {e}")
        return None, None

def read_bmp180():
    """Read pressure from BMP180"""
    try:
        if bmp180:
            pressure = bmp180.read_pressure() / 100.0  # Convert to hPa
            return pressure
        return None
    except Exception as e:
        print(f"BMP180 error: {e}")
        return None

def read_mq_sensors():
    """Read MQ-2 and MQ-7 gas sensors (returns ADC values)"""
    try:
        mq2_value = mq2_adc.read()  # 0-4095
        mq7_value = mq7_adc.read()  # 0-4095
        return mq2_value, mq7_value
    except Exception as e:
        print(f"MQ sensor error: {e}")
        return None, None

# ==================== CONTROL FUNCTIONS ====================
def control_fan(temp):
    """Control fan speed based on temperature"""
    if temp is None:
        return
        
    if temp > config['temp_max']:
        duty = min(1023, int((temp - config['temp_max']) * 100) + 256)
        fan.duty(duty)
        print(f"Fan ON (duty: {duty})")
    else:
        fan.duty(0)

def trigger_alarm(duration_ms=2000):
    """Sound the buzzer alarm"""
    if config['enable_local_alarm']:
        buzzer.on()
        time.sleep_ms(duration_ms)
        buzzer.off()

def check_alarm_conditions_deprecated(pm25, pm10, temp, mq2=None):
    """
    DEPRECATED: Old threshold-based alarm logic
    
    Now replaced by ML-based predictions from ml_inference_server.py
    This function is kept for reference/debugging only.
    
    Use main() loop instead which calls send_to_ml_server() for predictions.
    """
    alarm = False
    reason = ""
    
    # Local fallback thresholds (if ML server unavailable)
    if pm25 and pm25 > 100:  # WHO guideline
        alarm = True
        reason = f"PM2.5 high: {pm25} μg/m³"
    if pm10 and pm10 > 150:  # WHO guideline
        alarm = True
        reason = f"PM10 high: {pm10} μg/m³"
    if temp:
        if temp > 40 or temp < 5:
            alarm = True
            reason = f"Temperature extreme: {temp}°C"
            
    return alarm, reason

# ==================== DATA LOGGING ====================
def save_to_sd(data):
    """Save sensor data to SD card CSV file"""
    if sd is None:
        return False
        
    try:
        filename = '/sd/sensor_data.csv'
        file_exists = False
        try:
            os.stat(filename)
            file_exists = True
        except:
            pass
            
        with open(filename, 'a') as f:
            if not file_exists:
                # Write header
                f.write('timestamp,pm25,pm10,temp,humidity,pressure,mq2,mq7,alarm\n')
            
            # Write data
            f.write(f"{data['timestamp']},{data['pm25']},{data['pm10']},"
                   f"{data['temp']},{data['humidity']},{data['pressure']},"
                   f"{data['mq2']},{data['mq7']},{data['alarm']}\n")
        return True
    except Exception as e:
        print(f"SD write error: {e}")
        return False

# ==================== ML INFERENCE SERVER INTEGRATION ====================
def send_to_ml_server(pm25, pm10, gas, co, temp, humidity, pressure):
    """
    Send 7 raw sensor readings to ML Inference Server.
    Server computes all 35 features and returns prediction.
    
    Args:
        pm25: PM2.5 from MQ-130 (μg/m³)
        pm10: PM10 from MQ-130 (μg/m³)
        gas: VOC from MQ-135 (ppm)
        co: CO from MQ-7 (ppm)
        temp: Temperature from DHT-22 (°C)
        humidity: Relative humidity from DHT-22 (%)
        pressure: Pressure from BMP180 (hPa)
    
    Returns:
        dict: {class, confidence, alarm_triggered} or None if failed
    """
    if not wlan or not wlan.isconnected():
        print("❌ WiFi not connected, skipping ML inference")
        return None
    
    if not config.get('enable_ml_inference', True):
        print("ML inference disabled in config")
        return None
    
    try:
        # Format 7 raw sensors for ML server
        data = {
            'pm25': pm25 if pm25 is not None else 0,
            'pm10': pm10 if pm10 is not None else 0,
            'gas': gas if gas is not None else 0,
            'co': co if co is not None else 0,
            'temp': temp if temp is not None else 0,
            'humidity': humidity if humidity is not None else 0,
            'pressure': pressure if pressure is not None else 0
        }
        
        headers = {'Content-Type': 'application/json'}
        ml_server_url = config.get('ml_server_url', 'http://192.168.1.100:5000/data')
        timeout_ms = config.get('ml_server_timeout', 5000)
        
        print("Sending to ML server...")
        response = urequests.post(
            ml_server_url,
            data=ujson.dumps(data),
            headers=headers,
            timeout=timeout_ms // 1000  # Convert ms to seconds
        )
        
        if response.status_code == 200:
            result = response.json()
            response.close()
            
            # Extract ML prediction
            ml_pred = result.get('ml_prediction', {})
            prediction_class = ml_pred.get('class', 'Unknown')
            confidence = ml_pred.get('confidence', 0)
            alarm = result.get('alarm_triggered', False)
            
            print(f"✓ ML Prediction: {prediction_class} (confidence: {confidence:.1%})")
            print(f"  Features computed: {ml_pred.get('features_used', 0)}")
            print(f"  Alarm: {'🔴 YES' if alarm else '🟢 NO'}")
            
            return {
                'class': prediction_class,
                'confidence': confidence,
                'alarm_triggered': alarm,
                'probabilities': result.get('probabilities', {}),
                'aqi_category': result.get('aqi_category', 'Unknown')
            }
        else:
            print(f"❌ ML Server error: {response.status_code}")
            response.close()
            return None
    except Exception as e:
        print(f"❌ ML inference error: {e}")
        return None

def check_ml_server_health():
    """
    Check if ML inference server is running and ready.
    
    Returns:
        bool: True if server is healthy and model loaded
    """
    if not wlan or not wlan.isconnected():
        return False
    
    try:
        health_url = config.get('ml_server_health_url', 'http://192.168.1.100:5000/health')
        response = urequests.get(health_url, timeout=3)
        
        if response.status_code == 200:
            health = response.json()
            response.close()
            
            model_ok = health.get('model_loaded', False)
            scaler_ok = health.get('scaler_loaded', False)
            version = health.get('version', 'Unknown')
            
            if model_ok and scaler_ok:
                print(f"✓ ML Server healthy (v{version})")
                return True
            else:
                print(f"❌ ML Server not ready (model: {model_ok}, scaler: {scaler_ok})")
                return False
        else:
            print(f"❌ ML Server unhealthy: {response.status_code}")
            response.close()
            return False
    except Exception as e:
        print(f"❌ Health check error: {e}")
        return False

def send_to_blynk(data):
    """
    Send sensor data and ML predictions to Blynk cloud platform
    
    Virtual Pins:
      V0 = PM2.5 (μg/m³)
      V1 = PM10 (μg/m³)
      V2 = Temperature (°C)
      V3 = Humidity (%)
      V4 = Pressure (hPa)
      V5 = Alarm State (0=Safe, 1=Alert)
      V6 = ML Prediction Class (0=Safe, 1=Caution, 2=Hazardous)
      V7 = ML Confidence (0-100%)
    """
    if not wlan or not wlan.isconnected():
        print("⚠ Blynk: WiFi not connected")
        return False
        
    try:
        base_url = f"http://{config['blynk_server']}/external/api/batch/update"
        
        # Map ML class to numeric value for Blynk
        ml_class_map = {'safe': 0, 'caution': 1, 'hazardous': 2}
        ml_class_num = ml_class_map.get(data.get('ml_prediction', 'safe').lower(), 0)
        ml_confidence_percent = int(data.get('ml_confidence', 0) * 100)
        
        params = {
            'token': config['blynk_token'],
            'V0': data['pm25'],           # PM2.5
            'V1': data['pm10'],           # PM10
            'V2': data['temp'],           # Temperature
            'V3': data['humidity'],       # Humidity
            'V4': data['pressure'],       # Pressure
            'V5': data['alarm'],          # Alarm state
            'V6': ml_class_num,           # ML prediction (0=Safe, 1=Caution, 2=Hazardous)
            'V7': ml_confidence_percent   # ML confidence (%)
        }
        
        # Build URL with query parameters
        url = base_url + '?' + '&'.join([f"{k}={v}" for k, v in params.items()])
        response = urequests.get(url)
        
        if response.status_code == 200:
            print("📡 Blynk updated successfully (8 virtual pins)")
            response.close()
            return True
        else:
            print(f"❌ Blynk error: {response.status_code}")
            response.close()
            return False
    except Exception as e:
        print(f"❌ Blynk error: {e}")
        return False

# ==================== MAIN LOOP ====================
def get_timestamp():
    """Get current timestamp (seconds since epoch)"""
    return time.time()

def main():
    """Main monitoring loop"""
    print("=" * 60)
    print("ESP32 MILES Air Quality Prediction System v2.0")
    print("=" * 60)
    print("\nStarting MILES monitoring with ML inference...")
    print("=" * 60)
    
    # Connect to WiFi
    wifi_connected = connect_wifi()
    
    # Check ML server health if WiFi connected
    ml_server_ready = False
    if wifi_connected:
        print("\n[STARTUP] Checking ML Inference Server...")
        ml_server_ready = check_ml_server_health()
        if ml_server_ready:
            print("✓ ML Server is ready for predictions\n")
        else:
            print("⚠ ML Server not accessible (will continue with local logic)\n")
    
    print(f"Configuration:")
    print(f"  • Sampling interval: {config['sampling_interval']} seconds")
    print(f"  • ML Inference: {'🟢 ENABLED' if config.get('enable_ml_inference', True) else '🔴 DISABLED'}")
    print(f"  • WiFi: {'🟢 ENABLED' if config['enable_wifi'] else '🔴 DISABLED'}")
    print(f"  • SD Card: {'🟢 ENABLED' if config['enable_sd_card'] else '🔴 DISABLED'}")
    print("=" * 60 + "\n")
    
    cycle_count = 0
    ml_predictions = []
    
    while True:
        try:
            cycle_count += 1
            print(f"\n{'─' * 60}")
            print(f"Cycle {cycle_count} - {time.time():.0f}")
            print(f"{'─' * 60}")
            
            # Read all 7 sensors
            pm25, pm10 = read_pms5003()
            temp, humidity = read_dht22()
            pressure = read_bmp180()
            gas, co = read_mq_sensors()
            
            # Display raw sensor readings
            print("\n📊 RAW SENSOR READINGS:")
            print(f"  PM2.5:     {pm25 if pm25 is not None else '--'} μg/m³")
            print(f"  PM10:      {pm10 if pm10 is not None else '--'} μg/m³")
            print(f"  Gas (VOC): {gas if gas is not None else '--'} ppm")
            print(f"  CO:        {co if co is not None else '--'} ppm")
            print(f"  Temp:      {temp if temp is not None else '--'}°C")
            print(f"  Humidity:  {humidity if humidity is not None else '--'}%")
            print(f"  Pressure:  {pressure if pressure is not None else '--'} hPa")
            
            # Control fan based on temperature
            if temp is not None:
                control_fan(temp)
            
            # ============================================================
            # ML INFERENCE - Get prediction from server with all 35 features
            # ============================================================
            ml_result = None
            if wifi_connected and ml_server_ready:
                print("\n🤖 ML INFERENCE (35 Features):")
                ml_result = send_to_ml_server(pm25, pm10, gas, co, temp, humidity, pressure)
                
                if ml_result:
                    print(f"  Class probabilities:")
                    probs = ml_result.get('probabilities', {})
                    print(f"    Safe:      {probs.get('safe', 0):.1%}")
                    print(f"    Caution:   {probs.get('caution', 0):.1%}")
                    print(f"    Hazardous: {probs.get('hazardous', 0):.1%}")
                    ml_predictions.append(ml_result)
                else:
                    print("  ⚠ ML inference failed, using local logic")
            elif not wifi_connected:
                print("\n⚠ WiFi disconnected - ML inference not available")
            
            # ============================================================
            # ALARM DECISION
            # ============================================================
            alarm_triggered = False
            alarm_reason = None
            
            if ml_result and ml_result.get('confidence', 0) >= config.get('ml_confidence_threshold', 0.90):
                # Trust ML prediction
                if ml_result.get('alarm_triggered', False):
                    alarm_triggered = True
                    alarm_reason = f"ML: {ml_result['class']} (confidence {ml_result['confidence']:.0%})"
            else:
                # Fallback to local thresholds or low-confidence scenario
                if not wifi_connected or not ml_server_ready:
                    # Local rule-based alarm (optional backup)
                    if pm25 and pm25 > 100:
                        alarm_triggered = True
                        alarm_reason = f"Local: PM2.5 high ({pm25} μg/m³)"
            
            # ============================================================
            # ALERT SYSTEM
            # ============================================================
            print("\n🚨 ALARM STATUS:")
            if alarm_triggered:
                print(f"  🔴 ALARM TRIGGERED")
                print(f"     Reason: {alarm_reason}")
                trigger_alarm(2000)  # 2 second alarm
            else:
                print(f"  🟢 NORMAL CONDITIONS")
                buzzer.off()
            
            # Prepare data package for logging
            data_package = {
                'timestamp': get_timestamp(),
                'pm25': pm25 if pm25 is not None else 0,
                'pm10': pm10 if pm10 is not None else 0,
                'gas': gas if gas is not None else 0,
                'co': co if co is not None else 0,
                'temp': temp if temp is not None else 0,
                'humidity': humidity if humidity is not None else 0,
                'pressure': pressure if pressure is not None else 0,
                'alarm': 1 if alarm_triggered else 0,
                'ml_prediction': ml_result['class'] if ml_result else 'N/A',
                'ml_confidence': ml_result['confidence'] if ml_result else 0
            }
            
            # Save to SD card
            if config['enable_sd_card']:
                if save_to_sd(data_package):
                    print("\n💾 Data saved to SD card")
            
            # Send to Blynk (optional)
            if wifi_connected and config.get('enable_wifi', True):
                send_to_blynk(data_package)
            
            # Wait for next cycle
            remaining = config['sampling_interval']
            print(f"\n⏱ Next reading in {remaining} seconds...")
            time.sleep(remaining)
            
        except KeyboardInterrupt:
            print("\n\n⏹ Stopping MILES monitoring...")
            break
        except Exception as e:
            print(f"\n❌ Error in main loop: {e}")
            print("Retrying in 5 seconds...")
            time.sleep(5)
    
    # Cleanup
    fan.duty(0)
    buzzer.off()
    print("✓ MILES system stopped")

# ==================== ENTRY POINT ====================
if __name__ == '__main__':
    main()
