# 🚀 ML-INTEGRATED FIRMWARE SETUP GUIDE
## Complete Integration Steps for Testing Phase

> **Status**: Testing Phase - Trained model is now being used in production firmware

---

## 📋 QUICK OVERVIEW

### Old System (Threshold-Based)
```
ESP32 → Read Sensors → Compare to Fixed Thresholds → LED/Buzzer
        ❌ Limited accuracy (85-90%)
        ❌ Many false alarms (misting, sensor variations)
        ❌ No contextual understanding
```

### New System (ML-Integrated)
```
ESP32 → Read Sensors → WiFi → ML Server → Model Inference → Decision
                                              ✓ 99.98% accuracy
                                              ✓ Context-aware
                                              ✓ Adaptive to conditions
```

---

## 🎯 SYSTEM ARCHITECTURE (ML-Integrated)

```
┌─────────────────────────────────────────────────────────────────────┐
│                    TESTING PHASE ARCHITECTURE                        │
└─────────────────────────────────────────────────────────────────────┘

LAYER 1: HARDWARE (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  Sensors                                  Controls                   │
│  ├─ DHT22 (Temp/Humidity)      GPIO4     │  ├─ Green LED    GPIO18   │
│  ├─ MQ2 (Gas)                  GPIO34    │  ├─ Yellow LED   GPIO19   │
│  ├─ MQ7 (CO)                   GPIO35    │  ├─ Red LED      GPIO32   │
│  └─ PMS5003 (PM2.5/PM10)       UART2    │  └─ Buzzer       GPIO25   │
│                                          │                          │
│  ✓ Warm-up: 120 seconds (sensors stabilize)                     │
│  ✓ Fallback: Threshold logic if server unavailable              │
└─────────────────────────────────────────────────────────────────────┘
                             ↓↑ (WiFi)
LAYER 2: ML SERVER (Local Laptop/PC)
┌─────────────────────────────────────────────────────────────────────┐
│  Flask Server @ http://192.168.1.X:5000                            │
│                                                                      │
│  Endpoints:                                                         │
│  ├─ GET  /health              → Server status                      │
│  ├─ GET  /model-info          → Model metadata                     │
│  ├─ POST /predict             → Single prediction                  │
│  └─ POST /predict-batch       → Multiple predictions               │
│                                                                      │
│  ✓ Loads random_forest_model.pkl                                   │
│  ✓ Loads scaler.pkl                                                │
│  ✓ Performs preprocessing                                          │
│  ✓ Returns: Class (0/1/2) + Confidence                            │
└─────────────────────────────────────────────────────────────────────┘
                             ↑↓ (Decision)
LAYER 3: ACTIONS (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  Class 0 (SAFE):              Class 1 (CAUTION):                   │
│  ├─ Green LED: ON             ├─ Yellow LED: BLINKING              │
│  └─ Buzzer: OFF               ├─ Buzzer: 1 beep/10s                │
│                               └─ Action: Monitor area              │
│                                                                      │
│  Class 2 (HAZARDOUS):                                              │
│  ├─ Red LED: FLASHING                                              │
│  ├─ Buzzer: CONTINUOUS ALARM                                       │
│  └─ Action: IMMEDIATE EVACUATION                                   │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 📦 FILES TO DOWNLOAD FROM VSCODE

Create a `firmware` folder and download these files:

### 1. **Firmware Code** (Most Important)
```
FROM: Notebooks/../Air-Quality-Prediction/firmware/
FILE: esp32_ml_integrated.ino
```
**What it does:**
- Main Arduino firmware for ESP32
- Handles sensor reading
- Communicates with ML server
- Controls LED/Buzzer responses

### 2. **ML Inference Server** (Runs on Laptop)
```
FROM: Notebooks/../Air-Quality-Prediction/core source/
FILE: ml_inference_server_v2.py
```
**What it does:**
- Loads the trained model
- Receives sensor data from ESP32
- Performs predictions
- Returns class & confidence

### 3. **Model Files** (Pre-trained)
```
FROM: Notebooks/../Air-Quality-Prediction/models/
FILES: 
  ├─ random_forest_model.pkl     (The trained model - 3.2 MB)
  └─ scaler.pkl                  (Feature scaling - 2 KB)
```
**What they are:**
- Random Forest with 100 trees
- Trained on 20,568 samples (8 scenarios)
- 99.98% accuracy
- Handles 3-class classification (Safe/Caution/Hazardous)

### 4. **Configuration File** (Optional but Recommended)
```
Create: firmware/config.h
```
Store WiFi credentials and server IP here.

---

## 🔧 STEP-BY-STEP SETUP

### STEP 1: Download Files from VSCode

```bash
# In VSCode, open the Air-Quality-Prediction folder
# Download these files to your computer:

1. Navigate to: Notebooks/../firmware/
   ✓ Download: esp32_ml_integrated.ino

2. Navigate to: Notebooks/../core source/
   ✓ Download: ml_inference_server_v2.py

3. Navigate to: Notebooks/../models/
   ✓ Download: random_forest_model.pkl
   ✓ Download: scaler.pkl
```

---

### STEP 2: Setup ML Server (Laptop)

**Requirements:**
```bash
pip install flask flask-cors numpy scikit-learn pandas
```

**File Structure:**
```
your-project-folder/
├── ml_inference_server_v2.py
└── models/
    ├── random_forest_model.pkl
    └── scaler.pkl
```

**Start the Server:**
```bash
cd your-project-folder
python ml_inference_server_v2.py
```

**Expected Output:**
```
╔════════════════════════════════════════════════════════════╗
║  ML INFERENCE SERVER FOR ESP32 AIR QUALITY PREDICTION     ║
║  Status: STARTING...                                      ║
╚════════════════════════════════════════════════════════════╝

═══════════════════════════════════════════════════════════════
LOADING ML MODEL AND SCALER
═══════════════════════════════════════════════════════════════
✓ Model loaded: RandomForestClassifier
  - Trees: 100
  - Features: 7
  - Classes: 3

✓ Scaler loaded successfully

✓ MODEL READY FOR INFERENCE

═══════════════════════════════════════════════════════════════
STARTING FLASK SERVER
═══════════════════════════════════════════════════════════════
Server Address: http://0.0.0.0:5000
Accessible from ESP32 at: http://192.168.1.100:5000
```

**Find Your Laptop IP:**
```
Windows (PowerShell):
  ipconfig
  (Look for "IPv4 Address" under your WiFi adapter - e.g., 192.168.1.100)

Mac/Linux (Terminal):
  ifconfig
  (Look for "inet" under en0/eth0)
```

---

### STEP 3: Setup ESP32 Firmware

**Requirements:**
- Arduino IDE (download from arduino.cc)
- ESP32 Board Support in Arduino IDE

**Install ESP32 Support:**
1. Open Arduino IDE
2. File → Preferences
3. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
4. Tools → Board Manager → Search "ESP32" → Install

**Configure Firmware:**

1. Open `esp32_ml_integrated.ino` in Arduino IDE
2. Modify these lines (around line 20-30):
   ```cpp
   const char* SSID = "YOUR_WIFI_SSID";
   const char* PASSWORD = "YOUR_WIFI_PASSWORD";
   const char* ML_SERVER_URL = "http://192.168.1.100:5000/predict";  // Your laptop IP
   ```

3. Select Board:
   - Tools → Board → esp32 → ESP32 Dev Module

4. Select Port:
   - Tools → Port → COM3 (or whichever port your ESP32 is on)

5. Upload:
   - Click Upload button (or Ctrl+U)

**Expected Upload Output:**
```
Connecting to COM3...
Chip is ESP32-D0WD-V3 (revision 3)
Features: WiFi, BT, Dual Core
Uploading...
✓ Upload Complete
```

---

### STEP 4: Test the System

**Console Output:**
1. Open Arduino IDE → Tools → Serial Monitor
2. Set Baud Rate to 115200
3. Watch for messages like:
   ```
   ╔════════════════════════════════════════════════════════════╗
   ║  AIR QUALITY PREDICTION - ML-INTEGRATED SYSTEM (ESP32)    ║
   ║  Status: INITIALIZING...                                 ║
   ╚════════════════════════════════════════════════════════════╝

   ✓ System Ready - Entering 2-minute warm-up phase...
   ```

**After Warm-up (120 seconds):**
```
✓ WARM-UP COMPLETE - ML MODE ACTIVATED

══════════════════════════════════════════════════════════════════
Reading Sensors...
══════════════════════════════════════════════════════════════════

📊 SENSOR READINGS:
─────────────────────────────────────────────────────────────────
  📍 PM2.5:              35.2 µg/m³
  📍 PM10:               55.1 µg/m³
  🌡️  Temperature:        28.5 °C
  💧 Humidity:           65.0 %
  ⚠️  Gas (MQ-2):        250.5 ppm
  ⚠️  CO (MQ-7):          12.3 ppm
─────────────────────────────────────────────────────────────────

🤖 PERFORMING ML INFERENCE...
  Sending to local ML server at: http://192.168.1.100:5000/predict
  ✓ Prediction: Class 0 (SAFE) | Confidence: 99.50%

══════════════════════════════════════════════════════════════════
🎯 FINAL PREDICTION:
══════════════════════════════════════════════════════════════════
  Class: 0 (SAFE)
  Confidence: 99.50%
  Mode: ML INFERENCE
══════════════════════════════════════════════════════════════════
```

---

## 🔄 DATA FLOW DURING TESTING

```
┌────────────────────────────────────────────────────────────┐
│ SECOND 1-120: WARM-UP PHASE                               │
├────────────────────────────────────────────────────────────┤
│ ESP32: Reads sensors, Yellow LED blinking                 │
│ Server: Optional (not required)                           │
│ Output: Nothing (sensors stabilizing)                     │
└────────────────────────────────────────────────────────────┘

┌────────────────────────────────────────────────────────────┐
│ SECOND 120+: ML INFERENCE PHASE (Every 60 seconds)        │
├────────────────────────────────────────────────────────────┤
│ 1. ESP32 reads sensors                                    │
│    ├─ DHT22: Temp=28.5°C, Humidity=65%                   │
│    ├─ MQ2:   Gas=250.5 ppm                               │
│    ├─ MQ7:   CO=12.3 ppm                                 │
│    └─ PMS:   PM2.5=35.2, PM10=55.1                       │
│                                                            │
│ 2. ESP32 sends JSON to ML Server:                        │
│    POST http://192.168.1.100:5000/predict               │
│    {                                                       │
│      "pm2_5": 35.2,                                       │
│      "pm10": 55.1,                                        │
│      "temp": 28.5,                                        │
│      "humidity": 65.0,                                    │
│      "gas": 250.5,                                        │
│      "co": 12.3,                                          │
│      "time_of_day": 14                                    │
│    }                                                       │
│                                                            │
│ 3. Server receives, preprocesses, predicts:              │
│    ├─ Load model                                          │
│    ├─ Scale features with scaler.pkl                      │
│    ├─ Run model.predict()                                 │
│    └─ Get probabilities                                   │
│                                                            │
│ 4. Server returns JSON:                                   │
│    {                                                       │
│      "prediction": 0,           ← Class (SAFE)           │
│      "confidence": 0.9950,      ← 99.50%                 │
│      "class_name": "SAFE",                               │
│      "probabilities": {                                   │
│        "safe": 0.9950,                                    │
│        "caution": 0.0045,                                 │
│        "hazardous": 0.0005                               │
│      }                                                    │
│    }                                                       │
│                                                            │
│ 5. ESP32 executes action:                                │
│    if (prediction == 0 && confidence > 0.90):            │
│      ├─ Green LED: ON                                     │
│      └─ Buzzer: OFF                                       │
└────────────────────────────────────────────────────────────┘
```

---

## 🛡️ FALLBACK MECHANISM

**If ML Server is Unavailable:**

```
ESP32 detects no response from:
  http://192.168.1.100:5000/predict
          ↓
  System automatically switches to FALLBACK THRESHOLD MODE
          ↓
  Uses legacy logic:
  - PM2.5 > 35.4 µg/m³? Alert +1
  - PM10 > 150.4 µg/m³? Alert +1
  - Gas > 300 ppm? Alert +1
  - CO > 10 ppm? Alert +1
          ↓
  Classification:
  - Alerts ≥ 2 → HAZARDOUS
  - Alerts = 1 → CAUTION
  - Alerts = 0 → SAFE
```

**Advantages:**
✓ System never completely fails
✓ Always has fallback safety measures
✓ Can continue testing even if server crashes
✓ Hybrid approach (ML + Threshold)

---

## 📊 PERFORMANCE METRICS

### Model Performance (from notebook):
```
Training Accuracy:   100.00%
Test Accuracy:       99.98%
CV Mean Accuracy:    99.98%

Per-Class Performance:
  Safe (0):       Precision=99.8%, Recall=100.0%, F1=99.9%
  Caution (1):    Precision=100.0%, Recall=99.9%, F1=100.0%
  Hazardous (2):  Precision=99.9%, Recall=99.9%, F1=99.9%

Mean Prediction Confidence: 99.87%
High Confidence (≥0.9): 99.95% of predictions
```

### System Performance (Expected):
```
Response Time:       100-200ms per prediction
WiFi: Stable connection required for best performance
Fallback: Works without WiFi
Model Size:          3.2 MB (suitable for cloud/server)
Server CPU Usage:    <5% during normal operation
```

---

## 🚨 TROUBLESHOOTING

### Issue 1: ESP32 Can't Connect to WiFi
```
Solution:
1. Verify SSID and PASSWORD are correct
2. Check if 2.4GHz WiFi is enabled (ESP32 doesn't support 5GHz)
3. Restart router and ESP32
4. Check signal strength near ESP32
```

### Issue 2: ESP32 Can't Reach ML Server
```bash
# Test connectivity from ESP32 console:
Ping to 192.168.1.100... 

Solution:
1. Make sure laptop and ESP32 are on SAME WiFi network
2. Disable firewalls temporarily for testing
3. Verify laptop IP: Windows → ipconfig
4. Update ML_SERVER_URL in firmware
5. Ensure ml_inference_server_v2.py is running
```

### Issue 3: Model Loading Error on Server
```
Error: FileNotFoundError: random_forest_model.pkl

Solution:
1. Verify files exist in models/ directory
2. Check file paths in ml_inference_server_v2.py (line 47-48)
3. File structure must be:
   project/
   ├─ ml_inference_server_v2.py
   └─ models/
      ├─ random_forest_model.pkl
      └─ scaler.pkl
```

### Issue 4: Sensors Not Reading Properly
```
ESP32 Serial Shows: Temperature: NaN, Humidity: NaN

Solution:
1. Check DHT22 wiring (Pin 4)
2. Verify MQ2/MQ7 ADC connections (Pins 34, 35)
3. PMS5003 UART: RXD2 (GPIO16), TXD2 (GPIO17)
4. Try uploading BasicReadSensors.ino first to verify connections
```

---

## 📝 FILES DOWNLOADED CHECKLIST

```
✓ esp32_ml_integrated.ino
  (Size: ~15 KB)
  (Location: firmware/)
  (Purpose: Main Arduino firmware)

✓ ml_inference_server_v2.py
  (Size: ~12 KB)
  (Location: core source/)
  (Purpose: Python server for ML inference)

✓ random_forest_model.pkl
  (Size: ~3.2 MB)
  (Location: models/)
  (Purpose: Trained Random Forest model)

✓ scaler.pkl
  (Size: ~2 KB)
  (Location: models/)
  (Purpose: Feature scaling transformer)
```

---

## ✅ TESTING CHECKLIST

```
Before Production Deployment:

□ ML Server starts without errors
□ Model loads successfully with 99.98% accuracy
□ ESP32 connects to WiFi
□ Sensors read values correctly
□ Communication test: ESP32 → Server → Response
□ All LEDs respond to predictions
□ Buzzer sounds at correct times
□ Warm-up phase lasts 2 minutes
□ Fallback mode works (unplug WiFi)
□ Low confidence warnings display (< 0.90)
□ Serial output shows valid predictions
□ System runs continuously for ≥1 hour without crashes
```

---

## 🎯 NEXT STEPS

### After Setup Complete:
1. **Monitor Performance**: Watch serial output for 24+ hours
2. **Validate Predictions**: Compare ML predictions with manual observations
3. **Tune Confidence Threshold**: Adjust from 0.90 if needed
4. **Collect Real Data**: Record predictions for future retraining
5. **Update Model Monthly**: Retrain with new sensor data

### For Production Deployment:
1. Move ML server to cloud (AWS/Azure/GCP)
2. Implement remote model updates over WiFi
3. Add data logging to cloud database
4. Set up automated alerting system
5. Deploy to multiple ESP32 devices

---

## 📚 DOCUMENTATION LINKS

- Model Notebook: `model_performance_visualization.ipynb`
- Training Script: `train_random_forest.py`
- Feature Engineering: `MILES_Protocol_Analysis.md`
- System Architecture: See diagram above

---

**Last Updated**: April 7, 2026  
**Status**: ✅ Testing Phase - Ready for Deployment  
**Next Review**: After 30 days of field testing

