# MQ2_ADC to MQ2_PPM Conversion Summary

## Execution Date
May 24, 2026

## Objective
Convert all MQ2_ADC (ADC readings) values to MQ2_PPM (Smoke Parts Per Million) across all CSV files in the dataset folder using the MQ2 sensor formula chain.

## Conversion Formula

### Step 1: ADC → Rs (Sensor Resistance)
```
Rs = RL * (ADC_MAX - MQ2_ADC) / MQ2_ADC
   = 10 * (4095 - MQ2_ADC) / MQ2_ADC
```
- RL = 10 kΩ (Load Resistance)
- ADC_MAX = 4095 (12-bit ADC maximum)

### Step 2: Rs → Ratio (Rs/Ro)
```
ratio = Rs / Ro
      = Rs / 1.2925
```
- Ro = 1.2925 kΩ (Calibrated baseline resistance in clean air)

### Step 3: Ratio → MQ2_PPM (Smoke PPM)
```
MQ2_PPM = 10 ^ ( (log10(ratio) - pcurve[1]) / pcurve[2] + pcurve[0] )
        = 10 ^ ( (log10(ratio) - 0.53) / -0.44 + 2.3 )
```
- pcurve[0] = 2.3
- pcurve[1] = 0.53
- pcurve[2] = -0.44

## Files Converted

### Dataset CSV Files (5 Location-based Files)
1. ✅ 03-16-2026 (Inside of Temfacil).csv - 2,945 rows
2. ✅ 03-17-2026 (Warehouse).csv - 2,943 rows
3. ✅ 03-18-2026 (Outside of Temfacil).csv - 3,096 rows
4. ✅ 03-19-2026 (Fabrication Area).csv - 3,125 rows
5. ✅ 03-30-2026 (Active Floor Area).csv - 2,880 rows

### Training Simulation Data Files (7 Files)
6. ✅ TRAINING SIMULATION DATA - Hazardous - Combustion .csv - 996 rows
7. ✅ TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv - 700 rows
8. ✅ TRAINING SIMULATION DATA - Hazardous - Pure Dust.csv - 730 rows
9. ✅ TRAINING SIMULATION DATA - Hazardous - VOC.csv - 804 rows
10. ✅ TRAINING SIMULATION DATA - Safe - Clean Air (High Humidity).csv - 673 rows
11. ✅ TRAINING SIMULATION DATA - Safe - Clean Air.csv - 622 rows
12. ✅ TRAINING SIMULATION DATA - Safe - Misting.csv - 1,054 rows

### Combined Dataset Files (2 Files)
13. ✅ combined_data.csv - 20,568 rows (with feature recalculation)
14. ✅ combined_dataset.csv - 20,568 rows

**Total: 14 CSV files converted successfully**

## Changes Applied to Each File

### All CSV Files (14 total)
- **Column Header Change**: MQ2_ADC → MQ2_PPM
- **Value Conversion**: All MQ2_ADC values converted to MQ2_PPM using the formula chain
- **Precision**: All values rounded to 2 decimal places
- **In-Place Update**: Original column values replaced (no new columns created)

### Additional Changes to combined_data.csv
The following gas-related derived features were recalculated based on the new MQ2_PPM values:

1. **gas_co_ratio** - Ratio of MQ2_PPM to MQ7_ADC
2. **gas_delta** - Change in gas value from previous row
3. **gas_lag_1** - MQ2_PPM value from 1 reading ago
4. **gas_lag_3** - MQ2_PPM value from 3 readings ago
5. **gas_lag_5** - MQ2_PPM value from 5 readings ago
6. **gas_acceleration** - Indicator if |gas_delta| > 2
7. **gas_volatility** - Standard deviation of last 5 gas readings
8. **gas_trend** - Direction of change (+1, -1, or 0)
9. **is_gas_accelerating** - Indicator of sustained rise in gas values

## Sample Verification

### Conversion Test
- Input ADC: 1780.67
- Expected PPM: 16.84 ✓
- Calculation verification passed

### File Samples
- **03-16-2026 (Inside of Temfacil).csv**: Row 1 converted from 1780.67 ADC → 16.84 PPM ✓
- **TRAINING SIMULATION DATA - Hazardous - Fire Hazard.csv**: Rows converted to PPM values (49.2, 36.06, etc.) ✓
- **combined_data.csv**: MQ2_PPM values and gas-related features recalculated ✓

## Notes

- All values are maintained with 2 decimal place precision
- No data loss during conversion
- All CSV files maintain their original structure (row count unchanged)
- Gas-related features in combined_data.csv have been properly recalculated to reflect the new MQ2_PPM values
- The conversion is reversible if needed (inverse formula available)

## Conversion Script
- Script location: `convert_mq2_adc_to_ppm.py`
- Execution completed successfully on: 2026-05-24
- Status: ✅ Complete

---
**All CSV files in the dataset folder have been successfully converted from MQ2_ADC to MQ2_PPM.**
