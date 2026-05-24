# MQ2 Formula Analysis - Firmware, Training, and Model

## Summary

The MQ2 (Smoke Gas Sensor) uses a **consistent formula chain** across all three components:
1. **Firmware (ESP32)** - Real-time conversion
2. **Training Script** - Uses pre-converted dataset values
3. **Model** - Works with final PPM values (no conversion needed at inference)

---

## 1. FIRMWARE FORMULA (esp32_embedded_ml.ino)

### A. Constants Defined
```cpp
#define RL_VALUE 10.0                      // Load resistor value (kΩ)
#define RO_CLEAN_AIR_FACTOR 9.83          // Ro/Rs ratio in clean air
#define ADC_MAX 4095.0                     // 12-bit ADC maximum

float SmokeCurve[3] = { 2.3, 0.53, -0.44 };  // MQ2 Smoke curve constants:
                                              // [0]=a0=2.3
                                              // [1]=a1=0.53
                                              // [2]=a2=-0.44
```

### B. Step-by-Step Conversion Formula (3 Steps)

#### Step 1: ADC → Rs (Sensor Resistance)
```cpp
// Function: MQResistanceCalculation()
float MQResistanceCalculation(int raw_adc) {
    if (raw_adc <= 0) raw_adc = 1;
    if (raw_adc >= ADC_MAX) raw_adc = ADC_MAX - 1;
    return ((float)RL_VALUE * (ADC_MAX - raw_adc) / raw_adc);
    // Rs = RL * (ADC_MAX - raw_adc) / raw_adc
    //    = 10 * (4095 - ADC) / ADC
}
```

**Formula:**
$$Rs = RL \times \frac{ADC_{MAX} - raw\_adc}{raw\_adc} = 10 \times \frac{4095 - ADC}{ADC}$$

#### Step 2: Rs → Ro (Baseline Calibration)
```cpp
// Function: MQCalibration() - Called once at startup
float MQCalibration(int mq_pin) {
    float val = 0;
    for (int i = 0; i < 50; i++) {
        val += MQResistanceCalculation(analogRead(mq_pin));
        delay(500);
    }
    val /= 50;                              // Average of 50 samples (25 seconds)
    val /= RO_CLEAN_AIR_FACTOR;            // Ro = avg_Rs / 9.83
    return val;
}

// Stored globally: float Ro;
```

**Formula:**
$$Ro = \frac{\text{avg}(Rs)}{RO\_CLEAN\_AIR\_FACTOR} = \frac{\text{avg}(Rs)}{9.83}$$

#### Step 3: Rs/Ro Ratio → PPM (Final Conversion)
```cpp
// Function: MQGetSmokePpm()
float MQGetSmokePpm(float rs_ro_ratio) {
    return pow(10.0, ((log10(rs_ro_ratio) - SmokeCurve[1]) / SmokeCurve[2]) + SmokeCurve[0]);
    // PPM = 10 ^ ((log10(Rs/Ro) - 0.53) / -0.44 + 2.3)
}

// In main loop:
float rs = MQRead(MQ2_PIN);                 // Read 5 samples, average
float rs_ro_ratio = rs / Ro;                // Calculate ratio
data.gas = MQGetSmokePpm(rs_ro_ratio);      // Get PPM value
if (data.gas < 30.0) data.gas = 30.0;       // Floor at 30 PPM (safe baseline)
```

**Formula:**
$$PPM = 10^{\left(\frac{\log_{10}(Rs/Ro) - 0.53}{-0.44} + 2.3\right)}$$

Where:
- SmokeCurve[0] = a₀ = 2.3
- SmokeCurve[1] = a₁ = 0.53  
- SmokeCurve[2] = a₂ = -0.44

### C. Calibration Constants (Updated 2026-04-03)
```cpp
#define CALIBRATION_VERSION 2.0
#define CALIBRATION_DATE "2026-04-03"
#define MQ2_OFFSET_CALIBRATED 510.0   // Baseline ADC avg: 2210 | Target: 30 ppm (Safe)
#define MQ7_OFFSET_CALIBRATED 52.0    // Baseline ADC avg: 2333 | Target: 5 ppm (Safe)
#define CALIB_BASELINE_TEMP 34.3      // Reference temperature during calibration (°C)
#define CALIB_BASELINE_HUM 51.9       // Reference humidity during calibration (%)
```

### D. Real-Time Processing Loop
```cpp
void loop() {
    // Every 5 seconds (5000 ms):
    if (now - lastRead >= 5000) {
        // 1. Read MQ2 ADC
        float rs = MQRead(MQ2_PIN);                 // 5 samples @ 50ms each
        
        // 2. Calculate ratio
        float rs_ro_ratio = rs / Ro;                // Pre-calibrated Ro from setup()
        
        // 3. Convert to PPM
        data.gas = MQGetSmokePpm(rs_ro_ratio);      // Smoke PPM formula
        if (data.gas < 30.0) data.gas = 30.0;       // Minimum safety baseline
        
        // 4. Use for prediction
        float input[7] = {pm2_5, pm10, temp, hum, data.gas, co, time_of_day};
        lastClass = predict(input);  // Feed to Random Forest model
    }
}
```

---

## 2. TRAINING SCRIPT (train_random_forest.py)

### Status
The training script **does NOT perform MQ2 conversion** because:
- The dataset (combined_data.csv) is expected to already have converted values
- The script loads pre-processed sensor data from CSV files
- Gas values are read directly from the 'gas' column

### Data Loading
```python
DATASET_PATH = os.path.join(os.path.dirname(__file__), '..', 'dataset', 'combined_data.csv')

# Load data - expects pre-converted PPM values in 'gas' column
df = pd.read_csv(DATASET_PATH)

# The gas column should contain MQ2_PPM values (not raw ADC)
# Training uses this directly: features include 'gas' value
```

### Feature Engineering (Uses Converted Values)
```python
def compute_sensor_ratios(df):
    """Uses pre-converted gas PPM values"""
    df['gas_co_ratio'] = df['gas'] / (df['co'] + 0.1)  # PPM ratio
    df['pm_sum'] = df['pm2_5'] + df['pm10']
    return df

def compute_rate_of_change(df):
    """Tracks changes in gas PPM values"""
    df['gas_delta'] = df.groupby(groupby_col)['gas'].diff().fillna(0)
    df['gas_acceleration'] = (df['gas_delta'].abs() > 2).astype(int)
    return df
```

---

## 3. MODEL FILES (.pkl binary files)

### random_forest_model.pkl
- **Type:** Scikit-learn RandomForestClassifier
- **Features:** 7 inputs
  1. pm2_5 (PPM)
  2. pm10 (PPM)
  3. temp (°C)
  4. humidity (%)
  5. **gas (MQ2_PPM)** ← Already converted
  6. co (MQ7 PPM equivalent)
  7. time_of_day (hour 0-23)
- **Classes:** 3 (0=Safe, 1=Caution, 2=Hazardous)
- **Trees:** 200

### scaler.pkl
- **Type:** StandardScaler (sklearn.preprocessing)
- **7 parameters per feature:** Mean and Scale
- **Feature order matches model input** 

Example from firmware model.h:
```cpp
const float SCALER_MEAN[] = {
    134.47304334672955f,   // pm2_5
    162.6103656164913f,    // pm10
    31.437707117853012f,   // temp
    58.16507195643726f,    // humidity
    90.90941700159871f,    // gas (MQ2_PPM) ← Already PPM!
    9.52333592635812f,     // co
    9.035783741734734f     // time_of_day
};

const float SCALER_SCALE[] = {
    244.57969656682636f,   // pm2_5
    322.45639856485434f,   // pm10
    5.360645338895234f,    // temp
    12.705583885859085f,   // humidity
    45.11080159965295f,    // gas (MQ2_PPM) ← Already PPM!
    6.533757038471742f,    // co
    4.512887228017107f     // time_of_day
};
```

---

## 4. COMPLETE FORMULA CHAIN SUMMARY

### In Firmware (Real-Time)
```
RAW_ADC (0-4095)
    ↓ [Step 1: MQResistanceCalculation()]
Rs = 10 × (4095 - ADC) / ADC
    ↓ [Step 2: MQCalibration() - Once at startup]
Ro = avg(Rs) / 9.83
    ↓ [Step 3: MQGetSmokePpm() - Per reading]
MQ2_PPM = 10^((log₁₀(Rs/Ro) - 0.53) / -0.44 + 2.3)
    ↓
PREDICTION
```

### In Dataset (Pre-Converted)
```
MQ2_ADC → [Conversion Script] → MQ2_PPM
```

### In Training & Model (Already Converted)
```
MQ2_PPM (from dataset) → [Feature Engineering] → [Random Forest Model] → Prediction
```

---

## 5. KEY DIFFERENCES FROM ORIGINAL CONVERSION

### ⚠️ FIRMWARE vs NEW CONVERSION SCRIPT

| Aspect | Firmware (Original) | New Conversion (v3.1) |
|--------|-------------------|----------------------|
| **Ro Value** | Dynamically calibrated from field baseline (9.83 factor) | Fixed: 1.2925 kΩ |
| **Formula Step 1** | Rs = 10 × (4095 - ADC) / ADC | Rs = 10 × (4095 - ADC) / ADC ✓ Same |
| **Formula Step 2** | Ro = avg(Rs) / 9.83 | ratio = Rs / 1.2925 |
| **Formula Step 3** | PPM = 10^((log10(R/Ro) - 0.53) / -0.44 + 2.3) | PPM = 10^((log10(ratio) - 0.53) / -0.44 + 2.3) ✓ Same |
| **Safety Floor** | 30 PPM minimum | 2 decimal rounding |
| **Use Case** | Real-time field sensing | Dataset standardization |

### ⚠️ IMPLICATIONS
1. **Firmware** uses a **field-calibrated Ro** value (dynamic, per-device)
2. **Dataset** now uses a **fixed Ro = 1.2925 kΩ** (standardized baseline)
3. **Model was trained on field data** (Scenario 8) with mixed Ro values
4. **Future inference on new firmware** should use consistent Ro value

---

## 6. RECOMMENDATIONS FOR CONSISTENCY

### Option A: Update Firmware to Match Dataset Ro
```cpp
#define FIXED_RO 1.2925f  // Match dataset conversion
// Remove dynamic calibration, use fixed value
```

### Option B: Update Dataset Conversion to Match Firmware
```python
# Use actual field baseline from calibration logs
RO_VALUE = 2210 / 9.83  # From MQ2_OFFSET_CALIBRATED
```

### Option C: Track Ro Values Separately
- Store actual Ro value used in conversion
- Include in model as feature engineering metadata
- Allow per-site calibration

---

## 7. CURRENT STATUS (May 24, 2026)

✅ **Firmware Formula:** Fully implemented with 3-step conversion  
✅ **Training Formula:** Uses pre-converted dataset values  
✅ **Model Input:** Expects MQ2_PPM (already converted)  
✅ **Dataset Updated:** All CSV files now use MQ2_PPM (May 24, 2026)  
⚠️ **Consistency:** Firmware uses dynamic Ro; Dataset uses fixed Ro = 1.2925

---

## 8. FORMULA REFERENCE CARDS

### Firmware Quick Reference
```cpp
// Step 1: ADC to Rs
float rs = RL_VALUE * (ADC_MAX - adc) / adc;  // = 10 * (4095 - adc) / adc

// Step 2: Baseline (one-time)
Ro = calib_rs_avg / RO_CLEAN_AIR_FACTOR;      // = calib_rs_avg / 9.83

// Step 3: Rs/Ro to PPM
float ppm = pow(10, ((log10(rs/Ro) - 0.53) / -0.44) + 2.3);
```

### Dataset Conversion Quick Reference
```python
import numpy as np

# Parameters
RL = 10.0                  # Load resistor (kΩ)
RO = 1.2925               # Baseline (kΩ)
ADC_MAX = 4095            # 12-bit ADC
pcurve = [2.3, 0.53, -0.44]  # MQ2 Smoke curve

# Conversion
def adc_to_ppm(adc):
    rs = RL * (ADC_MAX - adc) / adc
    ratio = rs / RO
    ppm = 10 ** ((np.log10(ratio) - pcurve[1]) / pcurve[2] + pcurve[0])
    return round(ppm, 2)
```

---

**Last Updated:** May 24, 2026  
**Status:** All files documented and analyzed
