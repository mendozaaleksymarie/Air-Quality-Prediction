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

def check_alarm_conditions(pm25, pm10, temp, mq2=None):
    """Check if alarm conditions are met"""
    alarm = False
    
    if pm25 and pm25 > config['pm25_threshold']:
        alarm = True
    if pm10 and pm10 > config['pm10_threshold']:
        alarm = True
    if mq2 and mq2 > config.get('gas_threshold_caution', 400):
        alarm = True  # Hazard level > 400
    if temp:
        if temp > config['temp_max'] or temp < config['temp_min']:
            alarm = True
            
    return alarm

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

# ==================== NETWORK FUNCTIONS ====================
def send_to_server(data):
    """Send data to ML inference server"""
    if not wlan or not wlan.isconnected():
        return False
        
    try:
        headers = {'Content-Type': 'application/json'}
        response = urequests.post(
            config['server_url'],
            data=ujson.dumps(data),
            headers=headers
        )
        
        if response.status_code == 200:
            result = response.json()
            print(f"Server response: {result}")
            response.close()
            return result
        else:
            print(f"Server error: {response.status_code}")
            response.close()
            return None
    except Exception as e:
        print(f"Network error: {e}")
        return None

def send_to_blynk(data):
    """Send data to Blynk cloud platform"""
    if not wlan or not wlan.isconnected():
        return False
        
    try:
        # Virtual pins: V0=PM2.5, V1=PM10, V2=Temp, V3=Humidity, V4=Pressure, V5=Alarm
        base_url = f"http://{config['blynk_server']}/external/api/batch/update"
        
        params = {
            'token': config['blynk_token'],
            'V0': data['pm25'],
            'V1': data['pm10'],
            'V2': data['temp'],
            'V3': data['humidity'],
            'V4': data['pressure'],
            'V5': data['alarm']
        }
        
        # Build URL with query parameters
        url = base_url + '?' + '&'.join([f"{k}={v}" for k, v in params.items()])
        response = urequests.get(url)
        
        if response.status_code == 200:
            print("Blynk updated successfully")
            response.close()
            return True
        else:
            print(f"Blynk error: {response.status_code}")
            response.close()
            return False
    except Exception as e:
        print(f"Blynk error: {e}")
        return False

# ==================== MAIN LOOP ====================
def get_timestamp():
    """Get current timestamp (seconds since epoch)"""
    return time.time()

def main():
    """Main monitoring loop"""
    print("ESP32 Air Quality Monitor Starting...")
    print("=" * 50)
    
    # Connect to WiFi
    wifi_connected = connect_wifi()
    
    print("\nStarting monitoring loop...")
    print(f"Sampling interval: {config['sampling_interval']} seconds")
    print("=" * 50)
    
    cycle_count = 0
    
    while True:
        try:
            cycle_count += 1
            print(f"\n--- Cycle {cycle_count} ---")
            
            # Read all sensors
            pm25, pm10 = read_pms5003()
            temp, humidity = read_dht22()
            pressure = read_bmp180()
            mq2, mq7 = read_mq_sensors()
            
            # Display readings
            print(f"Timestamp: {get_timestamp()}")
            print(f"PM2.5: {pm25} μg/m³" if pm25 else "PM2.5: ERROR")
            print(f"PM10: {pm10} μg/m³" if pm10 else "PM10: ERROR")
            print(f"Temperature: {temp}°C" if temp else "Temperature: ERROR")
            print(f"Humidity: {humidity}%" if humidity else "Humidity: ERROR")
            print(f"Pressure: {pressure} hPa" if pressure else "Pressure: ERROR")
            print(f"MQ-2: {mq2}, MQ-7: {mq7}")
            
            # Control fan based on temperature
            control_fan(temp)
            
            # Check alarm conditions
            alarm = check_alarm_conditions(pm25, pm10, temp, mq2)
            
            if alarm:
                print("⚠️ ALARM TRIGGERED!")
                trigger_alarm(2000)
            else:
                print("✓ Normal conditions")
            
            # Prepare data package
            data = {
                'timestamp': get_timestamp(),
                'pm25': pm25 if pm25 is not None else 0,
                'pm10': pm10 if pm10 is not None else 0,
                'temp': temp if temp is not None else 0,
                'humidity': humidity if humidity is not None else 0,
                'pressure': pressure if pressure is not None else 0,
                'mq2': mq2 if mq2 is not None else 0,
                'mq7': mq7 if mq7 is not None else 0,
                'alarm': 1 if alarm else 0
            }
            
            # Save to SD card
            if config['enable_sd_card']:
                if save_to_sd(data):
                    print("✓ Saved to SD card")
            
            # Send to server for ML prediction
            if wifi_connected and config['enable_wifi']:
                server_result = send_to_server(data)
                if server_result:
                    print(f"ML Prediction: {server_result.get('prediction', 'N/A')}")
                    print(f"AQI Category: {server_result.get('aqi_category', 'N/A')}")
                
                # Send to Blynk
                send_to_blynk(data)
            
            # Wait for next cycle
            print(f"\nWaiting {config['sampling_interval']} seconds...")
            time.sleep(config['sampling_interval'])
            
        except KeyboardInterrupt:
            print("\n\nStopping monitoring...")
            break
        except Exception as e:
            print(f"Error in main loop: {e}")
            time.sleep(5)
    
    # Cleanup
    fan.duty(0)
    buzzer.off()
    print("Monitoring stopped")

# ==================== ENTRY POINT ====================
if __name__ == '__main__':
    main()
