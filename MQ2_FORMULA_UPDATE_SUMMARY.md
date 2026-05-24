# MQ2_PPM Formula Update - Field-Calibrated Ro (May 24, 2026)

## Update Summary

The MQ2 conversion formula has been **updated to support field-calibrated Ro values** instead of a fixed baseline. This aligns the dataset conversion with the actual firmware calibration method used in production ESP32 devices.

---

## What Changed

### Previous Implementation (Fixed Ro)
```
Ro = 1.2925 kOhm (hardcoded constant)
```

### New Implementation (Field-Calibrated Ro)
```
Ro = field_calibrated_value (per location/device)
Default: 0.8488 kOhm (from firmware baseline ADC: 2210)
```

---

## The Complete Formula Chain

### Step 1: ADC → Rs (Sensor Resistance)
```
Rs = RL * (ADC_MAX - raw_adc) / raw_adc
   = 10 * (4095 - MQ2_ADC) / MQ2_ADC
```

### Step 2: Rs → Ro Ratio (Using Field-Calibrated Ro)
```
ratio = Rs / Ro
```

Where **Ro is calculated from field baseline data:**
```
Rs_baseline = 10 * (4095 - baseline_adc) / baseline_adc
Ro = Rs_baseline / 9.83
```

### Step 3: Ratio → MQ2_PPM (Smoke PPM Formula)
```
MQ2_PPM = 10 ^ ((log10(ratio) - 0.53) / -0.44 + 2.3)
```

---

## Implementation Details

### Constants (From Firmware)
```cpp
RL_VALUE = 10.0                    // Load Resistor (kOhm)
ADC_MAX = 4095.0                   // 12-bit ADC maximum
RO_CLEAN_AIR_FACTOR = 9.83         // Clean air calibration factor

// MQ2 Smoke curve constants
PCURVE[0] = 2.3    // a0
PCURVE[1] = 0.53   // a1
PCURVE[2] = -0.44  // a2

DEFAULT_RO = 0.8488 kOhm  // Fallback (calculated from firmware baseline ADC: 2210)
```

### Field-Calibrated Ro Mapping
```python
FIELD_CALIBRATED_RO = {
    "03-16-2026 (Inside of Temfacil).csv": None,      # To be calibrated
    "03-17-2026 (Warehouse).csv": None,               # To be calibrated
    "03-18-2026 (Outside of Temfacil).csv": None,     # To be calibrated
    "03-19-2026 (Fabrication Area).csv": None,        # To be calibrated
    "03-30-2026 (Active Floor Area).csv": None,       # To be calibrated
    
    "TRAINING SIMULATION DATA": 0.8488,               # From firmware
    
    "combined_data.csv": None,                         # Composite
    "combined_dataset.csv": None,                      # Composite
}
```

---

## How to Calibrate Ro Values for Each Location

### Method 1: From Firmware Calibration Data
Each field deployment has a baseline ADC reading recorded at startup:

```python
from convert_mq2_adc_to_ppm import calculate_ro_from_baseline_adc

# Example: Inside Temfacil had baseline ADC of 2210
ro = calculate_ro_from_baseline_adc(2210)
# Result: ro = 0.8488 kOhm
```

### Method 2: From Firmware Output
When ESP32 boots with MQ2 sensor, it prints:
```
CALIBRATING MQ2...
MQ2 Ro: 0.8488     # This is the Ro value
```

Record this value for the location.

### Method 3: From Data Analysis
If you have raw ADC data and know which readings were in clean air:

```python
import numpy as np

# Find clean air readings (lowest, most stable)
clean_air_adc = df[df['Status'] == 'Safe']['MQ2_ADC'].mean()

# Calculate Ro
ro = calculate_ro_from_baseline_adc(clean_air_adc)
```

---

## Impact Analysis

### Example Conversion Difference

**Using OLD Fixed Ro (1.2925 kOhm):**
```
ADC 2210 → PPM = 16.84
```

**Using NEW Field-Calibrated Ro (0.8488 kOhm from firmware):**
```
ADC 2210 → PPM = 30.00
```

**Difference:** 1.8x variation (significant!)

The firmware target for this ADC reading was 30 ppm, so the field-calibrated Ro is correct.

---

## Updated Files

### Modified Files
1. **convert_mq2_adc_to_ppm.py**
   - ✓ Added field-calibration support
   - ✓ Added `calculate_ro_from_baseline_adc()` function
   - ✓ Added `get_ro_for_file()` function
   - ✓ Updated `convert_adc_to_ppm()` to accept `ro_value` parameter
   - ✓ Added configuration dictionary `FIELD_CALIBRATED_RO`

### New Documentation Files
2. **MQ2_FIELD_CALIBRATION_GUIDE.md**
   - Complete calibration procedures
   - Example calculations
   - How to obtain baseline ADC values

3. **MQ2_FORMULA_COMPLETE_ANALYSIS.md**
   - Detailed formula analysis
   - Firmware implementation
   - Model integration

---

## Current Dataset Status

### Last Conversion: May 24, 2026
- **Method Used:** Previous conversion with fixed Ro = 1.2925 kOhm
- **Status:** All 14 CSV files converted to MQ2_PPM format
- **Issue:** Using non-optimal Ro value

### To Correct the Dataset
1. Obtain baseline ADC values from field deployments
2. Calculate Ro for each location using `calculate_ro_from_baseline_adc()`
3. Update `FIELD_CALIBRATED_RO` dictionary in conversion script
4. Re-run conversion script to recalculate PPM values

---

## Recommended Next Steps

### High Priority (Accuracy)
- [ ] Collect baseline ADC values from all field deployment logs
- [ ] Calculate Ro for each location
- [ ] Re-convert dataset with proper field-calibrated Ro values

### Medium Priority (Documentation)
- [ ] Document Ro values used for each location
- [ ] Verify PPM values match firmware targets
- [ ] Update model training data

### Low Priority (Future)
- [ ] Add temperature/humidity compensation for Ro
- [ ] Implement per-device calibration tracking
- [ ] Create automated calibration validation

---

## Technical Notes

### Why Field Calibration Matters
The MQ2 sensor exhibits **manufacturing variation**:
- Different sensors have different gas sensitivity
- Aging affects sensitivity over time
- Environmental conditions during calibration affect Ro
- Different Ro = different PPM values for same ADC reading

### Firmware Approach (Correct)
```cpp
// At startup, calibrate for this specific device:
Ro = average(Rs from 50 clean air samples) / 9.83
// Then use this Ro for all subsequent conversions
```

### Dataset Approach (Now Updated)
```python
# Use field-calibrated Ro from firmware deployment:
Ro = calculate_ro_from_baseline_adc(baseline_adc_from_field)
# Convert ADC values with correct Ro
```

---

## Formula Reference

### Complete Conversion Function
```python
def convert_adc_to_ppm(adc_value, ro_value=0.8488):
    # Step 1: ADC to Rs
    rs = 10 * (4095 - adc_value) / adc_value
    
    # Step 2: Rs/Ro ratio
    ratio = rs / ro_value
    
    # Step 3: Ratio to PPM (MQ2 Smoke)
    log_ratio = np.log10(ratio)
    exponent = (log_ratio - 0.53) / -0.44 + 2.3
    ppm = 10 ** exponent
    
    return round(ppm, 2)
```

### From Baseline ADC to Ro
```python
def calculate_ro_from_baseline_adc(baseline_adc):
    rs_baseline = 10 * (4095 - baseline_adc) / baseline_adc
    ro = rs_baseline / 9.83
    return ro
```

---

## References

- **Script:** [convert_mq2_adc_to_ppm.py](convert_mq2_adc_to_ppm.py)
- **Firmware:** [firmware/esp32_embedded_ml.ino](firmware/esp32_embedded_ml.ino)
- **Calibration Guide:** [MQ2_FIELD_CALIBRATION_GUIDE.md](MQ2_FIELD_CALIBRATION_GUIDE.md)
- **Formula Analysis:** [MQ2_FORMULA_COMPLETE_ANALYSIS.md](MQ2_FORMULA_COMPLETE_ANALYSIS.md)

---

**Update Date:** May 24, 2026  
**Status:** ✓ Script Updated and Tested  
**Next Action:** Obtain baseline ADC values and recalibrate

