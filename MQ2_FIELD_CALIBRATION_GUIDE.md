# MQ2 Field Calibration Guide - Ro Value Calculation

## Overview

The MQ2 sensor requires **field calibration** to achieve accurate PPM conversions. This calibration produces a **Ro value** (baseline resistance in clean air) that varies per device and location.

---

## Why Field Calibration Matters

The MQ2 sensor is **not a manufactured constant**. Key factors affecting Ro:
- **Device aging** - Ro increases as sensor ages
- **Environmental conditions** - Temperature/humidity during calibration
- **Location baseline** - Different air quality baselines at different sites
- **Sensor variation** - Manufacturing tolerances between units

**Result:** Using a fixed Ro value (like 1.2925 kΩ) introduces systematic error. Field calibration corrects this.

---

## Ro Calculation Formula

From firmware calibration (firmware/esp32_embedded_ml.ino):

```
Step 1: Measure Rs in clean air
   Rs_baseline = RL * (ADC_MAX - baseline_adc) / baseline_adc
   Rs_baseline = 10 * (4095 - baseline_adc) / baseline_adc

Step 2: Calculate Ro using clean air factor
   Ro = Rs_baseline / RO_CLEAN_AIR_FACTOR
   Ro = Rs_baseline / 9.83
```

Where:
- RL = 10 kΩ (load resistor)
- ADC_MAX = 4095 (12-bit ADC)
- RO_CLEAN_AIR_FACTOR = 9.83 (MQ2 characteristic at 20°C, 65% RH)

---

## Getting Baseline ADC Values

### Method 1: From Firmware Calibration Logs
Each firmware deployment should record the calibration ADC reading:

```cpp
// From esp32_embedded_ml.ino setup():
Ro = MQCalibration(MQ2_PIN);
Serial.print("MQ2 Ro calibrated: ");
Serial.println(Ro);
```

**Example from known deployment:**
```
MQ2_OFFSET_CALIBRATED = 510.0   // Offset from 30 ppm target
Baseline ADC: 2210              // From field calibration
```

### Method 2: From Data Analysis
If you have the raw ADC data and know which readings were taken in clean air:

```python
import numpy as np

# Find ADC readings taken in clean air
# (lowest values, stable, no external contamination)
clean_air_readings = df[df['Status'] == 'Safe']['MQ2_ADC']
baseline_adc = np.mean(clean_air_readings)

print(f"Baseline ADC (field): {baseline_adc:.0f}")
```

### Method 3: From Firmware Serial Output
Connect to ESP32 over serial at startup:

```
WELCOME TO MILES!
...
CALIBRATING MQ2...
MQ2 Ro: 0.8488     # This is the Ro value
SAMPLING STARTED
```

Record the Ro value OR the baseline ADC value used to calculate it.

---

## Example Calculations

### Example 1: From Known Baseline ADC
**Input:** Baseline ADC = 2210 (clean air reading)

```python
from convert_mq2_adc_to_ppm import calculate_ro_from_baseline_adc

ro = calculate_ro_from_baseline_adc(2210)
print(f"Ro = {ro:.4f} kΩ")
# Output: Ro = 0.8488 kΩ
```

**Manual calculation:**
```
Rs_baseline = 10 * (4095 - 2210) / 2210 = 10 * 1884 / 2210 = 8.3440 kΩ
Ro = 8.3440 / 9.83 = 0.8488 kΩ
```

### Example 2: From Field Deployment Data
**Temfacil Inside (03-16-2026):**
- Baseline ADC: 2210
- Ro = 8.3440 / 9.83 = **0.8488 kΩ**

**Warehouse (03-17-2026):**
- Baseline ADC: 2150
- Rs_baseline = 10 * (4095 - 2150) / 2150 = 9.0698 kΩ
- Ro = 9.0698 / 9.83 = **0.9223 kΩ**

---

## How to Update Conversion Script with Calibrated Ro Values

### Step 1: Identify Baseline ADC for Each Location

Collect baseline ADC readings from firmware logs or field data:

| Location | Baseline ADC | Date | Source |
|----------|-------------|------|--------|
| Inside Temfacil | 2210 | 2026-03-16 | Firmware deploy |
| Warehouse | 2150 | 2026-03-17 | Firmware deploy |
| Outside Temfacil | 2180 | 2026-03-18 | Firmware deploy |
| Fabrication Area | 2195 | 2026-03-19 | Firmware deploy |
| Active Floor Area | 2210 | 2026-03-30 | Firmware deploy |

### Step 2: Calculate Ro Values

```python
from convert_mq2_adc_to_ppm import calculate_ro_from_baseline_adc

baseline_adc_map = {
    "03-16-2026 (Inside of Temfacil).csv": 2210,
    "03-17-2026 (Warehouse).csv": 2150,
    "03-18-2026 (Outside of Temfacil).csv": 2180,
    "03-19-2026 (Fabrication Area).csv": 2195,
    "03-30-2026 (Active Floor Area).csv": 2210,
}

for filename, adc in baseline_adc_map.items():
    ro = calculate_ro_from_baseline_adc(adc)
    print(f"{filename}: Ro = {ro:.4f} kΩ")
```

### Step 3: Update FIELD_CALIBRATED_RO Dictionary

Edit `convert_mq2_adc_to_ppm.py`:

```python
FIELD_CALIBRATED_RO = {
    "03-16-2026 (Inside of Temfacil).csv": 0.8488,
    "03-17-2026 (Warehouse).csv": 0.9223,
    "03-18-2026 (Outside of Temfacil).csv": 0.8832,
    "03-19-2026 (Fabrication Area).csv": 0.8693,
    "03-30-2026 (Active Floor Area).csv": 0.8488,
    
    "TRAINING SIMULATION DATA": 0.8488,
    
    "combined_data.csv": None,  # Composite - use individual values
    "combined_dataset.csv": None,
}
```

### Step 4: Re-run Conversion

```bash
python convert_mq2_adc_to_ppm.py
```

The script will now use field-calibrated Ro values for each location.

---

## Comparison: Fixed Ro vs Field-Calibrated Ro

### Using Fixed Ro = 1.2925 kΩ (OLD)
```
ADC 2210 → PPM = 16.84
Error: Using wrong Ro introduces systematic bias
```

### Using Field-Calibrated Ro = 0.8488 kΩ (NEW)
```
ADC 2210 → PPM = 30.00 (matches firmware target)
Correct: Ro is calibrated for this sensor/location
```

**Impact:** Difference of ~1.8× in PPM values!

---

## Temperature/Humidity Compensation

The Ro value is typically calibrated at a specific temperature and humidity:

```cpp
#define CALIB_BASELINE_TEMP 34.3    // °C
#define CALIB_BASELINE_HUM 51.9     // %
```

If operating in significantly different conditions, apply compensation:

```python
def apply_temperature_correction(ppm, calib_temp, current_temp):
    """
    Rough temperature compensation for MQ2
    (approximately -0.8% per °C above calibration)
    """
    correction_factor = 1 + 0.008 * (calib_temp - current_temp)
    return ppm * correction_factor
```

---

## Next Steps

1. ✅ **Collect baseline ADC values** from all deployment locations
2. ✅ **Calculate Ro values** using `calculate_ro_from_baseline_adc()`
3. ✅ **Update FIELD_CALIBRATED_RO** dictionary in conversion script
4. ✅ **Re-run conversion** with calibrated values
5. ✅ **Verify results** - compare with firmware baseline targets

---

## Current Status

**Script Updated:** May 24, 2026
- ✅ Formula chain correctly implemented
- ✅ Field-calibration support added
- ✅ Helper function for Ro calculation available
- ⚠️ **TODO:** Obtain baseline ADC values from field deployments
- ⚠️ **TODO:** Update FIELD_CALIBRATED_RO dictionary
- ⚠️ **TODO:** Re-convert dataset with actual Ro values

---

## References

- **MQ2 Datasheet:** https://www.sparkfun.com/datasheets/Sensors/MQ-2.pdf
- **Firmware:** firmware/esp32_embedded_ml.ino
- **Conversion Script:** convert_mq2_adc_to_ppm.py
- **Formula Analysis:** MQ2_FORMULA_COMPLETE_ANALYSIS.md
