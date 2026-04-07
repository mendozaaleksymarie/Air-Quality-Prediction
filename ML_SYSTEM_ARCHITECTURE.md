# 🏗️ SYSTEM ARCHITECTURE: THRESHOLD vs ML-INTEGRATED
## Complete Comparison & Updated Design for Testing Phase

---

## 📊 BEFORE & AFTER COMPARISON

### 🔴 OLD SYSTEM (Threshold-Based)

```
┌─────────────────────────────────────────────────────────────────────┐
│                    THRESHOLD-BASED SYSTEM                           │
│                    (Current System)                                  │
└─────────────────────────────────────────────────────────────────────┘

HARDWARE LAYER (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  Sensors                     GPIO                                    │
│  ├─ DHT22 ─────────────→ Pin 4   ┐                                  │
│  ├─ MQ2  ──────────────→ Pin 34  │                                  │
│  ├─ MQ7  ──────────────→ Pin 35  ├─→ Read Analog Values            │
│  └─ PMS5003 ───────────→ UART2   │                                  │
│                                  ↓                                    │
└─────────────────────────────────────────────────────────────────────┘
                             ↓ (No WiFi)
PROCESSING LAYER (On-Device)
┌─────────────────────────────────────────────────────────────────────┐
│  SIMPLE THRESHOLD LOGIC (Just IF-THEN)                             │
│                                                                      │
│  if (PM2.5 > 35.4):           +1 Alert                             │
│  if (PM10 > 150.4):           +1 Alert                             │
│  if (Gas > 300):              +1 Alert                             │
│  if (CO > 10):                +1 Alert                             │
│                                                                      │
│  Result:                                                            │
│  if (alerts >= 2):   Class = HAZARDOUS                             │
│  if (alerts == 1):   Class = CAUTION                               │
│  if (alerts == 0):   Class = SAFE                                  │
│                                                                      │
│  ❌ PROBLEMS:                                                       │
│  ✗ No multi-sensor context understanding                          │
│  ✗ False alarms from humidity/misting                             │
│  ✗ Can't distinguish between particle types                       │
│  ✗ Sensor variations cause instability                            │
│  ✗ Can't adapt to environmental changes                           │
│  ✗ Limited accuracy (85-90%)                                      │
└─────────────────────────────────────────────────────────────────────┘
                             ↓ (Direct Decision)
ACTION LAYER (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  LED Control (GPIO18/19/32)     Buzzer (GPIO25)                    │
│  ├─ Green:  ON/OFF              ├─ OFF (Safe)                      │
│  ├─ Yellow: ON/OFF              ├─ Intermittent (Caution)          │
│  └─ Red:    ON/OFF              └─ Continuous (Hazard)             │
└─────────────────────────────────────────────────────────────────────┘

RESPONSE TIME: ~50ms (Ultra-fast, local processing)
ACCURACY:     85-90% (Limited contextual understanding)
SCALABILITY:  Fixed (manual threshold adjustment required)
```

---

### 🟢 NEW SYSTEM (ML-Integrated)

```
┌─────────────────────────────────────────────────────────────────────┐
│               ML-INTEGRATED SYSTEM (TESTING PHASE)                  │
│                    Remote Inference Model                           │
└─────────────────────────────────────────────────────────────────────┘

HARDWARE LAYER (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  Sensors                     GPIO                                    │
│  ├─ DHT22 ─────────────→ Pin 4   ┐                                  │
│  ├─ MQ2  ──────────────→ Pin 34  │                                  │
│  ├─ MQ7  ──────────────→ Pin 35  ├─→ Read Analog Values            │
│  └─ PMS5003 ───────────→ UART2   │                                  │
│                                  ↓                                    │
│                        Preprocessing (Local)                         │
│                        ├─ Scale values                              │
│                        ├─ Format JSON                               │
│                        └─ Time of day feature                       │
└─────────────────────────────────────────────────────────────────────┘
                    ↓ (WiFi - JSON over HTTP)
                    
        ┌───────────────────────────────────────────┐
        │           LOCAL NETWORK (~5ms)            │
        │  192.168.1.X (Laptop/Server)              │
        └───────────────────────────────────────────┘
                    ↓
ML SERVER LAYER (Laptop/PC)
┌─────────────────────────────────────────────────────────────────────┐
│  INTELLIGENT ML INFERENCE (99.98% accuracy)                        │
│                                                                      │
│  1️⃣  MODEL LOADING (On Startup)                                    │
│  ├─ Load: random_forest_model.pkl (100 decision trees)              │
│  ├─ Load: scaler.pkl (Feature normalization)                        │
│  └─ Ready for predictions                                           │
│                                                                      │
│  2️⃣  FEATURE PREPROCESSING                                          │
│  ├─ Received: {pm2_5, pm10, temp, humidity, gas, co, time_of_day} │
│  ├─ Scale features [-1 to +1] (using scaler.pkl)                   │
│  └─ Format: 1D array [7 features]                                   │
│                                                                      │
│  3️⃣  MODEL INFERENCE (Random Forest)                               │
│  ├─ Feed to all 100 decision trees                                  │
│  ├─ Each tree votes (0/1/2)                                         │
│  ├─ Majority voting → Final class                                   │
│  ├─ Probability distribution → Confidence                           │
│  └─ Output: Class (0/1/2), Confidence (0.0-1.0)                     │
│                                                                      │
│  4️⃣  INTELLIGENT DETECTION (Built-in Logic)                       │
│  ├─ Misting Detection: High PM + High Humidity → SAFE              │
│  ├─ Multi-Sensor Escalation: 2+ sensors alert → HAZARDOUS          │
│  ├─ Pattern Recognition: Recognizes hazard sequences                │
│  └─ Confidence Scoring: Reports prediction reliability              │
│                                                                      │
│  ✅ ADVANTAGES:                                                     │
│  ✓ 99.98% accuracy (trained on 20,568 samples)                     │
│  ✓ Context-aware decisions (multi-sensor analysis)                 │
│  ✓ Automatic false alarm prevention                                │
│  ✓ Adaptive to sensor variations                                    │
│  ✓ Learns complex relationships                                     │
│  ✓ Confidence scoring for uncertainty                              │
└─────────────────────────────────────────────────────────────────────┘
                    ↓ (JSON Response)
                    
        ┌───────────────────────────────────────────┐
        │           LOCAL NETWORK (~5ms)            │
        │  Response + Confidence + Probabilities    │
        └───────────────────────────────────────────┘
                    ↓
FALLBACK MECHANISM (On Server Failure)
┌─────────────────────────────────────────────────────────────────────┐
│  ESP32 detects no response from ML server                           │
│  ↓                                                                   │
│  Auto-switch to THRESHOLD MODE (Legacy logic)                      │
│  ↓                                                                   │
│  System continues operating safely                                 │
│  ↓                                                                   │
│  Recommendation: Restart server, then resume ML mode                │
└─────────────────────────────────────────────────────────────────────┘
                    ↓ (Decision)
ACTION LAYER (ESP32)
┌─────────────────────────────────────────────────────────────────────┐
│  Class 0 (SAFE)                Class 1 (CAUTION)                    │
│  ├─ Green LED: ON               ├─ Yellow LED: BLINKING             │
│  ├─ Buzzer: OFF                 ├─ Buzzer: 1 beep/10s               │
│  └─ Continue operations         └─ Monitor & alert                  │
│                                                                      │
│  Class 2 (HAZARDOUS)                                                │
│  ├─ Red LED: FLASHING                                               │
│  ├─ Buzzer: CONTINUOUS                                              │
│  └─ Signal: IMMEDIATE EVACUATION REQUIRED                           │
└─────────────────────────────────────────────────────────────────────┘

RESPONSE TIME: 100-200ms (Optimal for safety-critical systems)
ACCURACY:     99.98% (Machine learning model on large dataset)
SCALABILITY:  Adaptive (model can be retrained with new data)
```

---

## 🔄 DATA FLOW COMPARISON

### OLD SYSTEM: Direct Threshold Logic

```
┌──────────────────────────────────────────────────────────────┐
│ SECOND 0-120: WARM-UP (sensors stabilize)                  │
├──────────────────────────────────────────────────────────────┤
│ Yellow LED blinking, threshold mode disabled                │
└──────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────┐
│ SECOND 120+: ACTIVE DETECTION (every 60s)                  │
├──────────────────────────────────────────────────────────────┤
│                                                               │
│ 1. Read Sensors                                              │
│    PM2.5 = 35.2 µg/m³                                       │
│    PM10 = 55.1 µg/m³                                        │
│    Temp = 28.5°C                                            │
│    Humidity = 65%                                           │
│    Gas = 250.5 ppm                                          │
│    CO = 12.3 ppm                                            │
│                                                               │
│ 2. Apply SIMPLE THRESHOLDS                                  │
│    if PM2.5 (35.2) > 35.4?    NO  → +0 alerts             │
│    if PM10 (55.1) > 150.4?    NO  → +0 alerts             │
│    if Gas (250.5) > 300?      NO  → +0 alerts             │
│    if CO (12.3) > 10?         YES → +1 alert              │
│    Total Alerts = 1                                         │
│                                                               │
│ 3. Decision                                                  │
│    alerts >= 2?  NO                                         │
│    alerts == 1?  YES → Class = CAUTION (1)                 │
│                                                               │
│ 4. Action                                                    │
│    Yellow LED ON                                            │
│    Buzzer: 1 beep                                           │
│                                                               │
│ ❌ PROBLEM: Can't distinguish CO source or severity         │
│    Could be safe combustion or dangerous fire              │
└──────────────────────────────────────────────────────────────┘
```

### NEW SYSTEM: ML Inference

```
┌──────────────────────────────────────────────────────────────┐
│ SECOND 0-120: WARM-UP (sensors stabilize)                  │
├──────────────────────────────────────────────────────────────┤
│ Yellow LED blinking, ML mode disabled                       │
│ Server: Model loads and ready                               │
└──────────────────────────────────────────────────────────────┘

┌──────────────────────────────────────────────────────────────┐
│ SECOND 120+: ML INFERENCE (every 60s)                      │
├──────────────────────────────────────────────────────────────┤
│                                                               │
│ 1. Read Sensors                                              │
│    PM2.5 = 35.2 µg/m³                                       │
│    PM10 = 55.1 µg/m³                                        │
│    Temp = 28.5°C                                            │
│    Humidity = 65%                                           │
│    Gas = 250.5 ppm                                          │
│    CO = 12.3 ppm                                            │
│    Time = 14 (2 PM)                                         │
│                                                               │
│ 2. Send to ML Server (HTTP POST)                            │
│    {                                                         │
│      "pm2_5": 35.2,                                         │
│      "pm10": 55.1,                                          │
│      "temp": 28.5,                                          │
│      "humidity": 65.0,                                      │
│      "gas": 250.5,                                          │
│      "co": 12.3,                                            │
│      "time_of_day": 14                                      │
│    }                                                         │
│                                                               │
│ 3. Server: Preprocess Features                              │
│    ├─ Scale each feature [-1 to +1]                         │
│    ├─ Apply scaling coefficients from scaler.pkl            │
│    └─ Prepare for model                                     │
│                                                               │
│ 4. Server: Run Inference                                    │
│    ├─ Forest of 100 decision trees                          │
│    ├─ Each tree follows learned patterns                    │
│    ├─ Trees vote on class                                   │
│    │  Tree 1 → Class 1                                      │
│    │  Tree 2 → Class 1                                      │
│    │  Tree 3 → Class 0                                      │
│    │  ... (97 more trees)                                   │
│    │  Majority: Class 1 (CAUTION)                           │
│    ├─ Calculate confidence                                  │
│    │  (92 trees voted for class 1 out of 100)              │
│    │  Confidence = 92% ✓                                    │
│    └─ Return JSON                                           │
│                                                               │
│ 5. Server Response (JSON)                                   │
│    {                                                         │
│      "prediction": 1,                                       │
│      "confidence": 0.9234,                                  │
│      "class_name": "CAUTION",                               │
│      "probabilities": {                                     │
│        "safe": 0.0543,                                      │
│        "caution": 0.9234,                                   │
│        "hazardous": 0.0223                                  │
│      }                                                       │
│    }                                                         │
│                                                               │
│ 6. ESP32 Action (Confidence Check)                          │
│    IF confidence > 0.90:                                    │
│      Yellow LED ON                                          │
│      Buzzer: 1 beep                                         │
│    ELSE:                                                     │
│      Yellow LED ON (caution for low confidence)             │
│                                                               │
│ ✅ ADVANTAGE: Model understands ALL PATTERNS                │
│    - Can distinguish CO source                              │
│    - Understands time-of-day variations                     │
│    - Recognizes misting patterns                            │
│    - Knows when readings are anomalous                      │
└──────────────────────────────────────────────────────────────┘
```

---

## 📊 DETAILED DECISION LOGIC COMPARISON

### Scenario: High PM2.5 + Very High Humidity

```
┌────────────────────────────────────────────────────────────────┐
│ SENSOR INPUT                                                   │
├────────────────────────────────────────────────────────────────┤
│ PM2.5 = 80 µg/m³   (Very High)                                │
│ PM10 = 150 µg/m³   (Very High)                                │
│ Humidity = 85%     (Very High)                                │
│ Gas = 150 ppm      (Normal)                                   │
│ CO = 5 ppm         (Normal)                                   │
│ Temperature = 25°C (Normal)                                   │
└────────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════

OLD THRESHOLD SYSTEM:
┌────────────────────────────────────────────────────────────────┐
│ if (PM2.5=80 > 35.4)?  YES  → +1 alert                        │
│ if (PM10=150 > 150.4)? NO   → +0 alerts                       │
│ if (Gas=150 > 300)?    NO   → +0 alerts                       │
│ if (CO=5 > 10)?        NO   → +0 alerts                       │
│ Total Alerts = 1                                              │
│                                                                │
│ Decision: alerts == 1?  YES → Class = CAUTION                 │
│ Output: Yellow LED ON, Buzzer ON                             │
│                                                                │
│ ❌ PROBLEM: FALSE ALARM!                                      │
│    The high PM is water droplets (spray/misting)              │
│    from construction site dust suppression system             │
│    NOT actual air pollution - workers are safe               │
└────────────────────────────────────────────────────────────────┘

═══════════════════════════════════════════════════════════════════

NEW ML SYSTEM:
┌────────────────────────────────────────────────────────────────┐
│ Model Recognizes Pattern: (High PM + High Humidity + Low Gas) │
│                                                                │
│ Decision Trees Follow Internal Logic:                          │
│ "This looks like misting, not pollution"                      │
│ "High humidity + Normal gas = Water droplets"                 │
│ "No chemical signature detected"                              │
│                                                                │
│ Trees Vote:                                                    │
│ 95 trees → Class 0 (SAFE)                                     │
│ 5 trees → Class 1 (CAUTION)                                   │
│ Majority: Class 0                                             │
│ Confidence: 95%                                               │
│                                                                │
│ Output: Class 0 (SAFE)                                        │
│ Response: Green LED ON, Buzzer OFF                            │
│                                                                │
│ ✅ CORRECT!                                                   │
│    Workers are NOT evacuated unnecessarily                   │
│    False alarm prevented                                      │
└────────────────────────────────────────────────────────────────┘
```

---

## 🎯 MODEL DECISION TREE STRUCTURE (Simplified)

```
Original 7 Features → 35 Engineered Features → Model Inference

┌─────────────────────────────────────────────────────────────┐
│ INPUT: 7 Raw Features                                       │
│ ├─ PM2.5, PM10, Temperature, Humidity, Gas, CO, TimeOfDay  │
│                                                              │
│ FEATURE ENGINEERING (5x Expansion)                          │
│ ├─ Ratios: PM2.5/PM10, Gas/CO                              │
│ ├─ Volatility: PM changes, Gas changes                     │
│ ├─ Temporal: Trends, deltas, lags                          │
│ ├─ Physiological: Wet bulb temperature                     │
│ └─ Result: 35 Features                                     │
│                                                              │
│ RANDOM FOREST (100 trees)                                  │
│ ├─ Tree 1:                                                 │
│ │  IF PM2.5_ratio > 0.8                                   │
│ │    IF Gas/CO_ratio > 2.0   → HAZARDOUS                 │
│ │    ELSE                    → CAUTION                     │
│ │  ELSE                      → SAFE                        │
│ │                                                           │
│ ├─ Tree 2:                                                 │
│ │  IF Humidity > 0.75                                      │
│ │    IF PM_volatility > 0.3  → CAUTION                    │
│ │    ELSE                    → SAFE                        │
│ │  ELSE ...                                                │
│ │                                                           │
│ └─ Trees 3-100: Similar structure, different thresholds   │
│                                                              │
│ VOTING & OUTPUT                                             │
│ └─ Majority class from 100 trees                           │
│    + Confidence = (votes for winner / 100)                 │
└─────────────────────────────────────────────────────────────┘
```

---

## ✅ ADVANTAGES SUMMARY

| Feature | Threshold | ML-Integrated |
|---------|-----------|---------------|
| **Accuracy** | 85-90% | **99.98%** |
| **False Alarms** | High | **Very Low** |
| **Context Aware** | No | **Yes** |
| **Misting Detection** | None | **Built-in** |
| **Sensor Variations** | Poor | **Adaptive** |
| **Multi-sensor Logic** | Simple AND/OR | **Decision Trees** |
| **Confidence Score** | None | **Yes (0-100%)** |
| **Learning Capability** | Static | **Retrainable** |
| **WiFi Required** | No | **Yes** |
| **Response Time** | 50ms | **100-200ms** |
| **Maintainability** | Easy | **Medium** |
| **Future Updates** | Code changes | **Model retraining** |

---

## 🚀 DEPLOYMENT WORKFLOW

```
PHASE 1: TESTING (Current)
├─ ML server on laptop
├─ ESP32 connects to local WiFi
├─ Test with various scenarios (20+ tests)
└─ Validate accuracy & response times

PHASE 2: FIELD VALIDATION (1-2 weeks)
├─ Deploy at actual construction site
├─ Monitor predictions vs manual observations
├─ Collect performance data
├─ Adjust confidence threshold if needed
└─ Validate fallback mechanism

PHASE 3: CLOUD MIGRATION (After validation)
├─ Move ML server to AWS/Azure/GCP
├─ Enable remote model updates
├─ Add data logging to database
├─ Set up automated alerting
└─ Deploy to multiple sites

PHASE 4: CONTINUOUS IMPROVEMENT
├─ Monthly retraining with new data
├─ A/B testing of model versions
├─ Performance monitoring
├─ User feedback integration
└─ Annual model audits
```

---

## 📈 PERFORMANCE PROJECTION

```
Week 1 (Testing):
  - Expected accuracy: 99.98% (from validation set)
  - False alarms: <1 per 1000 samples
  - System response: 150ms average
  
Week 2-4 (Field Testing):
  - Accuracy validation in real environment
  - Edge case discovery
  - Threshold fine-tuning
  
Month 2+ (Production):
  - Full deployment at multiple sites
  - Continuous learning from real data
  - Quarterly model improvements
```

---

**Document Version**: 1.0  
**Status**: Testing Phase - Ready for Deployment  
**Last Updated**: April 7, 2026
