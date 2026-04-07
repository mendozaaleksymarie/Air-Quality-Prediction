# MILES Deployment Procedure

## Quick Start: 5 Steps to Production

### Step 1: Prepare Server Environment (Linux/Ubuntu)

```bash
# 1.1 Install Python 3.8+ and dependencies
sudo apt-get update
sudo apt-get install python3 python3-pip

# 1.2 Install required Python packages
pip3 install flask numpy scikit-learn

# 1.3 Create application directory
mkdir -p /home/miles/app
mkdir -p /home/miles/app/models
cd /home/miles/app
```

### Step 2: Deploy ML Inference Server

```bash
# 2.1 Copy server files from your development machine
scp ml_inference_server.py user@server:/home/miles/app/
scp models/random_forest_model.pkl user@server:/home/miles/app/models/
scp models/scaler.pkl user@server:/home/miles/app/models/

# 2.2 Verify files are present
ssh user@server
ls -lh /home/miles/app/
ls -lh /home/miles/app/models/

# 2.3 Start the server in background
python3 ml_inference_server.py &

# Or use nohup to persist after SSH logout
nohup python3 ml_inference_server.py > server.log 2>&1 &
```

### Step 3: Verify Server is Running

```bash
# 3.1 Check health endpoint (from server or any machine on network)
curl http://localhost:5000/health

# Expected output:
# {
#   "status": "healthy",
#   "model_loaded": true,
#   "scaler_loaded": true,
#   "features": 35
# }

# 3.2 If running on different machine, replace localhost with server IP
curl http://192.168.1.100:5000/health
```

### Step 4: Prepare ESP32 Device

```bash
# 4.1 Update config.json with server IP
# File: configuration/config.json
{
  "ml_server_url": "http://192.168.1.100:5000/data",
  "ml_server_health_url": "http://192.168.1.100:5000/health",
  "ml_server_timeout": 5000,
  "enable_ml_inference": true,
  "ml_confidence_threshold": 0.90,
  ...
  (keep all other settings)
}

# 4.2 Flash firmware to ESP32
ampy --port /dev/ttyUSB0 put "core source/esp32_air_quality_sensor.py" main.py
ampy --port /dev/ttyUSB0 put configuration/config.json config.json

# Windows alternative using esptool:
python -m esptool --chip esp32 --port COM3 write_flash 0x0 firmware.bin
```

### Step 5: Test Integration

```bash
# 5.1 Monitor ESP32 serial output
picocom -b 115200 /dev/ttyUSB0
# or on Windows:
# Use PuTTY with COM3 @ 115200 baud

# 5.2 Look for this output (indicates success):
# ============================================================
# ESP32 MILES Air Quality Prediction System v2.0
# ============================================================
#
# ✓ WiFi connected
# ✓ ML Server is ready for predictions
#
# Cycle 1 - 1234567890
# ──────────────────────────────────────
# 📊 RAW SENSOR READINGS:
#   PM2.5:     45 μg/m³
#   PM10:      70 μg/m³
#   Gas (VOC): 120 ppm
#   CO:        0.9 ppm
#   ...
#
# 🤖 ML INFERENCE (35 Features):
#   Class probabilities:
#     Safe:      0.95%
#     Caution:   0.04%
#     Hazardous: 0.01%
```

---

## Detailed Configuration Guide

### Server Configuration (config.json)

**Location on Server:** `/home/miles/app/config.json`

```json
{
  "flask_port": 5000,
  "flask_host": "0.0.0.0",
  "model_path": "models/random_forest_model.pkl",
  "scaler_path": "models/scaler.pkl",
  "feature_buffer_size": 10,
  "enable_logging": true,
  "log_level": "INFO"
}
```

**Key Parameters:**
- `flask_port`: Port where server listens (5000 is default)
- `flask_host`: "0.0.0.0" means listen on all interfaces (required for network access)
- `model_path`: Must point to trained Random Forest model
- `scaler_path`: Must point to fitted feature scaler
- `feature_buffer_size`: 10 readings for lagged features (don't change)

### Device Configuration (config.json)

**Location on Device:** `configuration/config.json`

```json
{
  "wifi_ssid": "YOUR_WIFI_SSID",
  "wifi_password": "YOUR_PASSWORD",
  "ml_server_url": "http://192.168.1.100:5000/data",
  "ml_server_health_url": "http://192.168.1.100:5000/health",
  "ml_server_timeout": 5000,
  "enable_ml_inference": true,
  "ml_confidence_threshold": 0.90,
  "blynk_token": "YOUR_BLYNK_TOKEN",
  "blynk_server": "blynk-cloud.com",
  "sampling_interval": 30,
  "enable_wifi": true,
  "enable_sd_card": true,
  "enable_fan": true
}
```

**Critical Settings:**
- `ml_server_url`: Must match server IP and port (192.168.1.100:5000)
- `enable_ml_inference`: Set to true to enable ML predictions
- `ml_confidence_threshold`: Only trust predictions with confidence >= 0.90
- `sampling_interval`: 30 seconds is default (can be 15-60)

---

## Network Setup

### Finding Server IP Address

```bash
# On server machine
ifconfig  # Linux/Mac
# or
ipconfig  # Windows

# Look for inet addr (Linux) or IPv4 Address (Windows)
# Example: 192.168.1.100
```

### Firewall Configuration

```bash
# On server machine - allow port 5000
sudo ufw allow 5000
sudo ufw allow 5000/tcp

# Verify firewall rules
sudo ufw status
```

### Testing Connectivity

```bash
# From ESP32 or any device on network
ping 192.168.1.100  # Should work

# From server, verify port is listening
netstat -tuln | grep 5000
# Should show: 0.0.0.0:5000 LISTEN
```

---

## Running the Server

### Option 1: Direct Execution

```bash
cd /home/miles/app
python3 ml_inference_server.py
```

**Output should show:**
```
 * Running on http://0.0.0.0:5000
 * Press CTRL+C to quit
```

### Option 2: Background with nohup

```bash
nohup python3 ml_inference_server.py > server.log 2>&1 &
echo $!  # Note the process ID

# Check if running
ps aux | grep ml_inference_server
tail -f server.log  # View logs in real-time
```

### Option 3: System Service (Recommended for Production)

Create `/etc/systemd/system/miles-ml-server.service`:

```ini
[Unit]
Description=MILES ML Inference Server
After=network.target

[Service]
Type=simple
User=miles
WorkingDirectory=/home/miles/app
ExecStart=/usr/bin/python3 /home/miles/app/ml_inference_server.py
Restart=on-failure
RestartSec=10

[Install]
WantedBy=multi-user.target
```

Then run:
```bash
sudo systemctl enable miles-ml-server
sudo systemctl start miles-ml-server
sudo systemctl status miles-ml-server
```

---

## API Endpoints Reference

### GET /health
**Purpose:** Check server and model status

**Request:**
```bash
curl http://192.168.1.100:5000/health
```

**Response:**
```json
{
  "status": "healthy",
  "model_loaded": true,
  "scaler_loaded": true,
  "features": 35,
  "timestamp": 1634567890.123
}
```

### POST /data
**Purpose:** Send sensor data and get prediction

**Request:**
```bash
curl -X POST http://192.168.1.100:5000/data \
  -H "Content-Type: application/json" \
  -d '{
    "pm25": 42.5,
    "pm10": 58.3,
    "gas": 120.5,
    "co": 0.8,
    "temp": 25.3,
    "humidity": 65.2,
    "pressure": 1013.25
  }'
```

**Response:**
```json
{
  "class": "Caution",
  "confidence": 0.92,
  "alarm_triggered": true,
  "probabilities": {
    "safe": 0.05,
    "caution": 0.92,
    "hazardous": 0.03
  },
  "aqi_category": "Moderate",
  "features_used": 35,
  "timestamp": 1634567890.456,
  "computation_time_ms": 12.5
}
```

### GET /features
**Purpose:** List all 35 features used

**Request:**
```bash
curl http://192.168.1.100:5000/features
```

**Response:**
```json
{
  "count": 35,
  "features": [
    "pm25", "pm10", "gas", "co", "temp", "humidity", "pressure", "site_id",
    "pm_ratio", "gas_co_ratio", "pm_sum",
    "pm25_delta", "pm10_delta", "gas_delta", "co_delta", "pm25_accel", "gas_accel",
    "pm25_lag_1", "pm25_lag_3", "pm25_lag_5", "gas_lag_1", "gas_lag_3", "gas_lag_5", "co_lag_1", "co_lag_3", "co_lag_5",
    "pm25_volatility", "gas_volatility",
    "pm_trend", "gas_trend", "pm_acceleration", "gas_acceleration",
    "pm25_health", "gas_health"
  ]
}
```

### GET /info
**Purpose:** Get server information

**Request:**
```bash
curl http://192.168.1.100:5000/info
```

**Response:**
```json
{
  "server_version": "2.0",
  "model_version": "RandomForest-200est",
  "features": 35,
  "classes": ["safe", "caution", "hazardous"],
  "training_accuracy": 1.0,
  "cross_validation_f1": 0.9992,
  "timestamp": 1634567890.789
}
```

---

## Logs and Monitoring

### Server Logs

```bash
# If running with nohup
tail -f /home/miles/app/server.log

# View last 50 lines
tail -50 /home/miles/app/server.log

# Search for errors
grep ERROR /home/miles/app/server.log

# Monitor in real-time (with colors if available)
tail -f /home/miles/app/server.log | grep -E "(ERROR|WARNING|INFO)"
```

### ESP32 Logs (Serial Monitor)

```bash
# Linux/Mac
picocom -b 115200 /dev/ttyUSB0

# Press Ctrl+A then Ctrl+X to exit

# Windows: Use PuTTY
# Serial line: COM3
# Speed: 115200
# Connection type: Serial
```

### Common Log Messages

**Expected (Good):**
```
✓ WiFi connected
✓ ML Server is ready for predictions
🤖 ML INFERENCE (35 Features):
💾 Data saved to SD card
📡 Blynk updated successfully
```

**Warnings (Investigate):**
```
⚠ WiFi disconnected - ML inference not available
⚠ ML server not accessible
⚠ ML prediction failed, using local logic
```

**Errors (Fix Immediately):**
```
❌ Cannot read PM sensor
❌ ML Server error: 500
❌ Feature shape mismatch
```

---

## Troubleshooting Deployment

### Problem 1: "Connection refused" from device

```bash
# Server side:
# 1. Check server is running
ps aux | grep ml_inference_server

# 2. Check listening port
netstat -tuln | grep 5000

# 3. Check firewall
sudo ufw status
sudo ufw allow 5000

# 4. Restart server
pkill -f ml_inference_server
python3 ml_inference_server.py &
```

### Problem 2: "Model not loaded"

```bash
# Check files exist
ls -l models/random_forest_model.pkl
ls -l models/scaler.pkl

# Check file size (shouldn't be 0 bytes)
du -h models/
# Should show ~2-5 MB for model and ~10-20 KB for scaler

# Check permissions (must be readable)
chmod 644 models/*.pkl
```

### Problem 3: "Feature shape mismatch: got X, expected 35"

```bash
# Check you're sending exactly 7 values:
# ["pm25", "pm10", "gas", "co", "temp", "humidity", "pressure"]

# Test manually:
curl -X POST http://localhost:5000/data \
  -H "Content-Type: application/json" \
  -d '{"pm25":45,"pm10":70,"gas":120,"co":0.9,"temp":25,"humidity":65,"pressure":1013}'

# Should work with no errors
```

### Problem 4: ESP32 can't reach server

```bash
# From device, test connectivity
# Option A: Ping server IP (from MicroPython)
import network
import socket
sock = socket.socket()
sock.connect(("192.168.1.100", 5000))

# Option B: Verify WiFi connection
import network
wlan = network.WLAN(network.STA_IF)
print(wlan.isconnected())
print(wlan.ifconfig())  # Should show valid IP
```

### Problem 5: All predictions are "Safe" (low confidence)

```bash
# 1. Check scaler is correct (trained with same data)
# 2. Wait for buffer to warm up (first 5 readings are fallback)
# 3. Use test data that mimics training distribution
# 4. Check feature order matches exactly

# Test with known good data:
curl -X POST http://localhost:5000/data \
  -d '{"pm25":150,"pm10":200,"gas":500,"co":5,"temp":25,"humidity":60,"pressure":1013}'
# Should predict Hazardous with high confidence
```

---

## Performance Tuning

### Response Time Optimization

**Current Performance:**
- Feature computation: 2-4 ms
- Model inference: 8-15 ms
- Total server latency: 20-40 ms

**To improve:**

```python
# In ml_inference_server.py
# 1. Use joblib for faster model loading
import joblib
model = joblib.load('model.pkl')  # Faster than pickle

# 2. Enable multithreading
app.run(threaded=True)

# 3. Use werkzeug production server
# pip install gunicorn
gunicorn -w 4 -b 0.0.0.0:5000 ml_inference_server:app
```

### Memory Optimization

```bash
# Check memory usage
free -h

# Monitor with top
top -b -p $(pgrep -f ml_inference_server)
```

---

## Production Checklist

- [ ] Server machine (Linux with Python 3.8+)
- [ ] Dependencies installed: flask, numpy, scikit-learn
- [ ] Model files exist and readable: random_forest_model.pkl (2-5 MB)
- [ ] Scaler file exists and readable: scaler.pkl (10-20 KB)
- [ ] Firewall allows port 5000: `sudo ufw allow 5000`
- [ ] Server running: `python3 ml_inference_server.py &`
- [ ] Health endpoint responds: `curl http://localhost:5000/health`
- [ ] All model checks return true (model_loaded, scaler_loaded)
- [ ] Config.json on server has correct paths
- [ ] Config.json on device has correct server IP
- [ ] ESP32 firmware flashed with updated code
- [ ] WiFi credentials configured on device
- [ ] Device connects to WiFi successfully
- [ ] Device can reach server (/health check passes)
- [ ] Predictions received and logged
- [ ] Blynk app receives updates (if enabled)
- [ ] SD card logging working
- [ ] Alarm triggers on test data
- [ ] Buffer warm-up period understood (5+ readings)
- [ ] Monitoring logs are being generated
- [ ] Performance is acceptable (20-40 ms latency)

---

## Quick Reference Commands

```bash
# Server monitoring
tail -f server.log
ps aux | grep ml_inference_server
netstat -tuln | grep 5000
curl http://localhost:5000/health

# Server management
sudo systemctl start miles-ml-server
sudo systemctl stop miles-ml-server
sudo systemctl status miles-ml-server
sudo systemctl restart miles-ml-server

# Device monitoring (serial)
picocom -b 115200 /dev/ttyUSB0
# Ctrl+A then Ctrl+X to exit

# Testing
curl -X POST http://192.168.1.100:5000/data \
  -H "Content-Type: application/json" \
  -d '{"pm25":50,"pm10":75,"gas":150,"co":1.5,"temp":25,"humidity":60,"pressure":1013}'

# Check files
ls -lh models/
du -h models/
file models/random_forest_model.pkl
```

---

**Ready to Deploy! ✅**

Follow the 5-step quick start above, then reference this guide for detailed configuration and troubleshooting.
