# DECISION TREES IN RANDOM FOREST MODEL
## How Individual Trees Make Decisions & Arduino Implementation

---

## What is a Decision Tree?

A decision tree is a flowchart where:
- **Each node asks a question**: "Is PM2.5 > 65?"
- **Each branch is an answer**: Yes (left) or No (right)
- **Leaves are the output**: SAFE (0), CAUTION (1), or HAZARDOUS (2)

The Random Forest trains **100 independent trees**, each learning different sensor combinations from your 20,568 training rows.

---

## Example: What ONE Decision Tree Might Look Like

Based on your 8-scenario training, a single tree might look like this:

```
                    🌳 TREE #37 (Example from Random Forest)
                    
                         IS GAS > 140 ppm? ⭐ (Gas is high indicator)
                              /           \
                            YES            NO
                            /               \
                           /                 \
                    IS PM2.5 > 100?      IS HUMIDITY >= 95%?
                        /     \            /        \
                      YES     NO         YES        NO
                      /       \         /          \
                     [2]   IS CO > 30  [0]    IS PM2.5 > 100?
                  HAZARD    ppm?    SAFE      /         \
                            /   \           YES         NO
                          YES   NO           /           \
                          /     \           /             \
                        [2]     [1]       [2]             [0]
                      HAZARD  CAUTION   HAZARD          SAFE
```

### What Each Decision Point Means:

1. **GAS > 140 ppm** (Node 1)
   - Learned from Scenarios 4, 5, 6 (fire, combustion, VOC)
   - If gas sensors high → Risk of chemical/combustion hazard
   - Split here first because gas is 21.8% important feature

2. **PM2.5 > 100** (Node 2, goes with high gas)
   - When gas IS high: Check PM2.5 to confirm multi-sensor spike
   - High gas + High PM = likely fire or combustion → HAZARDOUS
   - High gas + Low PM = might be VOC only → still HAZARDOUS but reason is gas

3. **HUMIDITY >= 95%** (Node 3, goes with low gas)
   - When gas is LOW: Extreme humidity + extreme PM = MISTING (Scenario 3)
   - This is the **false alarm defense branch**
   - Model learned: "If humidity is extreme AND gas is normal → SAFE (water droplets)"

4. **CO > 30 ppm** (Node 4, low gas, low humidity)
   - Additional check for chemical hazards even when MQ-2 below threshold
   - Scenario 6 teaches: "Gas-based hazards need multiple indicators"

---

## Random Forest Ensemble: 100 Cooperating Trees

Your model has **100 trees**, and they vote:

```
INPUT: PM2.5=150, PM10=120, Gas=160, CO=35, Humidity=42, Temp=25, Tw=26.5, Hour=14

Tree #1:  Votes → HAZARDOUS (2)  ✓
Tree #2:  Votes → HAZARDOUS (2)  ✓
Tree #3:  Votes → CAUTION (1)    (disagrees, but minority)
Tree #37: Votes → HAZARDOUS (2)  ✓
...
Tree #99: Votes → HAZARDOUS (2)  ✓

FINAL DECISION (Majority vote):
  ├─ HAZARDOUS (2): 96 trees
  ├─ CAUTION (1):   4 trees
  └─ SAFE (0):      0 trees
  
OUTPUT: HAZARDOUS [Confidence: 96%]
```

**Why ensemble voting?** 
- Single trees can overfit to noise
- 100 trees voting = robust decision
- If most trees agree, high confidence
- If trees split 50-50, lower confidence → shows ambiguity

---

## The 8 Decision Patterns Trees Learned

Your trees learned to recognize these 8 distinct sensor signatures:

### Pattern 1: SCENARIO 1 - BASELINE (Safe)
```
Tree Decision Chain:
IF gas < 100 AND pm2_5 < 50 AND humidity < 80
  → SAFE (0)
  
Real-world: All sensors in normal ranges
Example: PM2.5=15, Gas=85, Humidity=55, CO=2
Output: SAFE ✓
```

### Pattern 2: SCENARIO 2 - PURE DUST (Hazardous)
```
Tree Decision Chain:
IF pm2_5 > 100 AND humidity < 60 AND gas < 120
  → HAZARDOUS (2)
  
Why? High PM + low humidity = dust particles floating (not mist)
Real-world: Dust storm or demolition debris
Example: PM2.5=180, Humidity=42, Gas=105, CO=8  
Output: HAZARDOUS ✓ (Reason: dust hazard)
```

### Pattern 3: SCENARIO 3 - MISTING (Safe, CRITICAL)
```
Tree Decision Chain:
IF pm2_5 > 300 AND humidity >= 95 AND gas < 100 AND temp < 35
  → SAFE (0)  ⭐⭐⭐ FALSE ALARM DEFENSE
  
Why? Extreme PM + extreme humidity = water droplets, not pollution
Real-world: Cooling misting system, spray humidifier
Example: PM2.5=500, Humidity=98, Gas=92, CO=3
Output: SAFE ✓ (Reason: misting detected, not hazard)

This is THE KEY ADVANTAGE over thresholds!
```

### Pattern 4: SCENARIO 4 - FIRE (Hazardous)
```
Tree Decision Chain:
IF (gas > 180 AND pm2_5 > 200 AND temp > 30) OR (co > 50)
  → HAZARDOUS (2)
  
Why? Multi-sensor spike = fire signature (not just one sensor)
Real-world: Active fire, flash point reached
Example: PM2.5=400, Gas=210, CO=45, Temp=32  
Output: HAZARDOUS ✓ (Reason: FIRE → EVACUATE)
```

### Pattern 5: SCENARIO 5 - COMBUSTION GRADUAL (Hazardous)
```
Tree Decision Chain:
IF (gas > 150 AND pm2_5 > 120) OR 
   (time_diff_from_previous > 0 AND gas_trend_up AND pm_trend_up)
  → HAZARDOUS (2)
  
Why? Gradual coordinated rise = developing combustion
Real-world: Slow ignition, controllable fire starting
Example: PM2.5=140, Gas=155, CO=15 (increasing over 10 min)
Output: HAZARDOUS ✓ (Reason: developing hazard)
```

### Pattern 6: SCENARIO 6 - VOC/CHEMICAL (Hazardous)
```
Tree Decision Chain:
IF (gas > 160 AND co > 25) OR (gas > 200)
  → HAZARDOUS (2)
  
Why? High gas ALONE indicates chemical hazard (no visible smoke needed)
Real-world: Paint fumes, solvent vapors, pesticides
Example: PM2.5=50, Gas=180, CO=28, Humidity=45
Output: HAZARDOUS ✓ (Reason: chemical hazard)

Critical: PM2.5 is LOW but still HAZARDOUS due to gas!
```

### Pattern 7: SCENARIO 7 - HIGH HUMIDITY (Safe)
```
Tree Decision Chain:
IF (humidity >= 75 AND gas < 110 AND pm2_5 < 80)
  → SAFE (0)
  
Why? High humidity alone is not hazard in tropical climate
Real-world: Rainy season, aircon condensation
Example: PM2.5=45, Humidity=88, Gas=95, CO=5
Output: SAFE ✓ (Reason: humidity context OK)
```

### Pattern 8: SCENARIO 8 - FIELD DEPLOYMENT (Mixed)
```
Trees learned real-world complexity from 5 construction sites:
- Sensor drift (day-to-day calibration changes)
- Multi-hazard interactions (dust + heat)
- Site-specific baselines (warehouse different from outside)
- Time patterns (busy hours have more pollution)

Example Caution Decision:
IF pm2_5 > 60 AND pm2_5 < 100 AND hour_of_day between 8-17
  → CAUTION (1)
  
Meaning: Single dust spike during work hours = monitor, not emergency
```

---

## How Arduino Firmware Will Use These Trees

Your ESP32 firmware will need to:

### 1. Load the Model (at startup)
```cpp
// Arduino pseudo-code
void setup() {
  // Load the 100 trained trees and scaler from SPIFFS memory
  RandomForestModel model = LoadModel("rf_model.bin");
  StandardScaler scaler = LoadScaler("scaler.bin");
}
```

### 2. Read Sensors (continuous loop)
```cpp
void loop() {
  // Read all 8 sensors in real-time
  float pm2_5 = readPM25();           // PMS5003 sensor
  float pm10 = readPM10();            // PMS5003 sensor  
  float temp = readTemperature();     // DHT22 sensor
  float humidity = readHumidity();    // DHT22 sensor
  float gas = readGasSensor();        // MQ-2 sensor
  float co = readCOSensor();          // MQ-7 sensor
  int hour = getHourOfDay();          // RTC
  float wet_bulb = computeWetBulb(temp, humidity); // Calculated
  
  // Create feature vector [PM2.5, PM10, Temp, Humidity, Gas, CO, Hour, Wet-Bulb]
  float features[8] = {pm2_5, pm10, temp, humidity, gas, co, hour, wet_bulb};
  
  // Normalize using scaler (mean/stddev)
  float normalized[8];
  for(int i=0; i<8; i++) {
    normalized[i] = (features[i] - scaler.mean[i]) / scaler.stddev[i];
  }
```

### 3. Make Predictions (run through 100 trees)
```cpp
// For each of 100 trees in ensemble:
int votes[3] = {0, 0, 0}; // vote counts for classes [Safe, Caution, Hazardous]

for(int tree_id = 0; tree_id < 100; tree_id++) {
  // Traverse ONE tree from root to leaf
  int prediction = TraverseTree(tree_id, normalized);
  votes[prediction]++;  // Record this tree's vote
}

// Find majority vote
int final_class = ArgMax(votes);  // 0, 1, or 2
float confidence = votes[final_class] / 100.0 * 100; // 0-100%
```

### 4. Traverse Example Tree in Arduino
```cpp
// Example: Simplified version of Tree #37
int TreeLogic_37(float* normalized_features) {
  // normalized_features[4] = Gas (after normalization)
  // normalized_features[0] = PM2.5
  // etc.
  
  // if (gas > threshold_learned_from_training)
  if(normalized_features[4] > 0.85) {  // High gas branch
    if(normalized_features[0] > 0.70) {  // AND PM2.5 high
      return 2;  // HAZARDOUS
    }
    if(normalized_features[5] > 0.80) {  // OR CO high
      return 2;  // HAZARDOUS
    }
    return 1;  // CAUTION
  } else {  // Low gas branch
    if(normalized_features[3] > 1.20) {  // High humidity
      if(normalized_features[0] < 1.10) {  // PM2.5 not TOO high
        return 0;  // SAFE (misting likely)
      }
    }
    if(normalized_features[0] > 0.50) {
      return 1;  // CAUTION
    }
    return 0;  // SAFE
  }
}
```

### 5. Output Alarm Status
```cpp
// Determine device state
switch(final_class) {
  case 0:  // SAFE
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_RED, LOW);
    buzzer.off();
    break;
    
  case 1:  // CAUTION
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
    buzzer.beep(500ms);  // Single beep every 30 seconds
    lcd.print("CAUTION: Monitor");
    break;
    
  case 2:  // HAZARDOUS
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, LOW);
    buzzer.continuousAlarm();  // Rapid beeps
    lcd.print("HAZARDOUS: EVACUATE");
    break;
}
```

---

## Feature Importance: Where Trees Split Most

The trained model learned this splitting priority:

```
FEATURE IMPORTANCE (from 20,568 training rows):

1. MQ-2 Gas (21.8%)   ⭐⭐⭐ Trees split on this FIRST (Scenarios 4,5,6)
2. MQ-7 CO (21.4%)    ⭐⭐⭐ Second most important (Scenarios 4,6)
3. Wet-Bulb Temp (15%) ⭐⭐  Heat stress interaction (NEW)
4. Humidity (18%)      ⭐⭐  Misting detection (Scenario 3)
5. PM2.5 (16.4%)       ⭐⭐  Dust/smoke (Scenarios 2,3,4)
6. PM10 (14.0%)        ⭐   Coarse dust (Scenario 2)
7. Temperature (4.5%)  ·   Context only
8. Time of Day (4.1%)  ·   Circadian patterns
```

**Arduino optimization hint:**
Even if you only have limited RAM on ESP32, you could optimize by:
- Checking gas sensors first (highest importance)
- Quick exit if result is clear
- Only check humidity/temp if gas is ambiguous

---

## Key Advantages Over Threshold-Based System

### Threshold Approach (Simple but Flawed):
```
IF PM2.5 > 100 → Alert (always the same)
IF Humidity > 90 → Maybe alert? (ambiguous)
If Gas > 150 → Alert (always the same)
```

**Problem:** No context, can't distinguish scenarios, frequent false alarms

### Decision Tree Approach (What Your Model Does):
```
IF Gas > 150 AND PM2.5 > 100 AND Humidity < 80 AND CO > 20
  → HAZARDOUS (specific fire pattern)
ELSE IF Gas > 150 AND PM2.5 < 100 AND Humidity < 70 AND CO > 25
  → HAZARDOUS (specific VOC pattern)
ELSE IF PM2.5 > 300 AND Humidity > 95 AND Gas < 100
  → SAFE (misting pattern)
ELSE IF PM2.5 > 100 AND Humidity < 60 AND Hour between 8-17
  → CAUTION (field uncertainty during work)
```

**Advantages:**
- ✓ Context-aware (considers all sensors together)
- ✓ Captures complex interactions (what threshold systems can't)
- ✓ Learns from real data (8 scenarios = ground truth)
- ✓ Probabilistic (confidence scores, not binary)
- ✓ False alarm defense (misting scenario)
- ✓ Adapts to time of day and seasonal patterns

---

## Example Arduino Workflow: REAL SCENARIO

### Scenario: Misting System Activated at 14:30

```
SENSOR READINGS (from ESP32):
├─ PM2.5: 520 μg/m³ (EXTREME)
├─ PM10: 380 μg/m³ (EXTREME)
├─ Gas: 88 ppm (NORMAL)
├─ CO: 3 ppm (NORMAL)
├─ Temperature: 28°C
├─ Humidity: 97% (EXTREME)
├─ Time: 14:30 (2:30 PM)
└─ Wet-Bulb: 27.5°C

THRESHOLD SYSTEM RESULT:
  IF PM2.5 > 100? YES → ALERT! HAZARDOUS!
  → Evacuation alarm triggers
  → Workers stop work, leave site
  → After 5 minutes, they realize it's just misting
  → Alarm fatigue: "System always goes off for nothing"
  → Next time there's REAL fire → Alarm ignored
  → PEOPLE DIE
  
❌ FAILED DEFENSE


RANDOM FOREST DECISION TREES:
  Tree #1 checks: gas > 140? NO → goes to humidity check
  Tree #1:        humidity >= 95? YES → ✓ SAFE
  
  Tree #37 checks: gas > 150? NO → goes to humidity check  
  Tree #37:       humidity >= 95? YES → ✓ SAFE
                   (this is SCENARIO 3 pattern)
  
  Tree #84 checks: pm2_5 > 250? YES
  Tree #84:       humidity > 95? YES → ✓ SAFE
                  (recognizes misting override)
  
  ... 97 other trees agree or split close
  
RANDOM FOREST RESULT:
  ├─ SAFE: 96 trees ✓✓✓
  ├─ CAUTION: 4 trees
  └─ HAZARDOUS: 0 trees
  
  FINAL: SAFE (Confidence: 96%)
  GREEN LED turns on
  Buzzer stays silent
  Workers continue operating
  
✓ TRUE DEFENSE ACTIVATED
```

---

## Memory Footprint for Arduino

```
Model storage on ESP32 SPIFFS flash:
├─ 100 decision trees (rules): ~250 KB
├─ Scaler (means/stddevs): ~1 KB
├─ Total model size: ~251 KB
└─ ESP32 typical flash: 4 MB
   → Plenty of room! ✓

Runtime memory during prediction:
├─ Sensor readings array (8 floats): 32 bytes
├─ Normalized array (8 floats): 32 bytes
├─ Tree traversal stack: ~50 bytes
├─ Vote counter array: 12 bytes
└─ Total active RAM: ~150 bytes
   → Very efficient! ✓
```

---

## Summary: Decision Trees → Arduino Implementation

1. **Off-device (your PC):**
   - Train 100 trees on 20,568 MILES scenario rows
   - Each tree learns a sensor decision pattern
   - Export tree rules + scaler to binary files

2. **On-device (Arduino):**
   - Load 100 trees into flash memory
   - Read 8 sensors in real-time
   - Normalize using scaler
   - Run input through all 100 trees (parallel voting)
   - Output majority vote: SAFE (0), CAUTION (1), or HAZARDOUS (2)

3. **Result:**
   - ✓ Misting detected (Scenario 3) → False alarms eliminated
   - ✓ Multi-sensor patterns recognized → Hazards confirmed
   - ✓ Field data learned → Adapts to real conditions
   - ✓ Workers trust device → Real emergencies are heeded

**Your device becomes genuinely intelligent, not just triggering on numbers.**
