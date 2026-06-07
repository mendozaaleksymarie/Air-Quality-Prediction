#!/usr/bin/env python3
"""
UPDATE TESTING DATASET REMARKS
Corrects outdated remarks in all Testing Dataset CSV files to match
MILES_DECISION_TABLE_COMPLETE.md definitions.

Uses the 200-tree Random Forest model's decision logic:
1. Compute Wet-Bulb Temperature (Stull 2011 formula)
2. Evaluate sensor ranges against thresholds
3. Apply decision tree logic to determine Class (0/1/2)
4. Assign correct Remark based on Class and sensor combinations
"""

import os
import pandas as pd
import numpy as np
from pathlib import Path

# ═══════════════════════════════════════════════════════════════════════════
# WET-BULB TEMPERATURE CALCULATION (Stull 2011)
# ═══════════════════════════════════════════════════════════════════════════
def compute_wet_bulb_temperature(temp_c, humidity_rh):
    """
    Compute wet-bulb temperature using Stull (2011) formula.
    Valid range: T = 5–50 °C, RH = 5–100 %
    Mean absolute error < 0.3 °C
    """
    try:
        if pd.isna(temp_c) or pd.isna(humidity_rh):
            return np.nan
        
        temp_c = float(temp_c)
        humidity_rh = float(humidity_rh)
        
        # Stull (2011) formula
        tw = (
            temp_c * np.arctan(0.151977 * (humidity_rh + 8.313659) ** 0.5) +
            np.arctan(temp_c + humidity_rh) -
            np.arctan(humidity_rh - 1.676331) +
            0.00391838 * humidity_rh ** 1.5 * np.arctan(0.023101 * humidity_rh) -
            4.686035
        )
        
        return float(tw)
    except (TypeError, ValueError):
        return np.nan


# ═══════════════════════════════════════════════════════════════════════════
# DECISION LOGIC FROM MILES_DECISION_TABLE_COMPLETE.md
# ═══════════════════════════════════════════════════════════════════════════

def apply_classification_and_remarks(row):
    """
    Apply intelligent classification and remark assignment based on:
    - Sensor readings (PM2.5, PM10, Gas, CO)
    - Wet-bulb temperature
    - Decision table definitions
    
    Returns: (class_label, remark)
    """
    
    pm2_5 = float(row['PM2.5'])
    pm10 = float(row['PM10'])
    gas = float(row['Gas'])
    co = float(row['CO'])
    temp = float(row['Temp'])
    humidity = float(row['Hum'])
    
    # Compute Wet-Bulb Temperature
    tw = compute_wet_bulb_temperature(temp, humidity)
    
    # ═════════════════════════════════════════════════════════════════════
    # SENSOR THRESHOLDS (from decision table)
    # ═════════════════════════════════════════════════════════════════════
    PM25_CAUTION = 51
    PM25_HAZARDOUS = 101
    
    PM10_CAUTION = 151
    PM10_HAZARDOUS = 231
    
    GAS_CAUTION = 40
    GAS_HAZARDOUS = 63
    
    CO_CAUTION = 10
    CO_HAZARDOUS = 31
    
    # ═════════════════════════════════════════════════════════════════════
    # STEP 1: CHECK MISTING OVERRIDE (Highest Priority)
    # Humidity ≥ 95% AND Gas ≤ 40 AND Tw ≤ 35°C
    # ═════════════════════════════════════════════════════════════════════
    if humidity >= 95 and gas <= 40 and tw <= 35:
        return 0, "SAFE: HIGH HUMIDITY MIST DETECTED. CONTINUE OPERATIONS"
    
    # ═════════════════════════════════════════════════════════════════════
    # STEP 2: CHECK SINGLE HAZARDOUS SENSORS (Highest Priority)
    # Any single sensor > hazardous threshold = Class 2
    # ═════════════════════════════════════════════════════════════════════
    
    if pm2_5 > 100:
        return 2, "HAZARDOUS: HEAVY FINE DUST. REQUIRE N95 MASKS & ACTIVATE WATER SPRAY"
    
    if pm10 > 230:
        return 2, "HAZARDOUS: HEAVY COARSE DUST. REQUIRE N95 MASKS & ACTIVATE WATER SPRAY"
    
    if gas >= 63:
        return 2, "HAZARDOUS: CRITICAL GAS LEVELS. SUSPEND ALL WELDING & HOT WORKS"
    
    if co > 30:
        return 2, "HAZARDOUS: CRITICAL CO LEVELS. EQUIP RESPIRATORS"
    
    # ═════════════════════════════════════════════════════════════════════
    # STEP 3: EVALUATE MULTI-SENSOR HAZARDOUS COMBINATIONS
    # ═════════════════════════════════════════════════════════════════════
    
    # Count sensors in caution and hazardous ranges
    hazardous_count = 0
    caution_count = 0
    
    # PM2.5 evaluation
    pm25_hazardous = pm2_5 >= 101
    pm25_caution = pm2_5 >= 51 and pm2_5 < 101
    if pm25_hazardous:
        hazardous_count += 1
    elif pm25_caution:
        caution_count += 1
    
    # PM10 evaluation
    pm10_hazardous = pm10 >= 231
    pm10_caution = pm10 >= 151 and pm10 < 231
    if pm10_hazardous:
        hazardous_count += 1
    elif pm10_caution:
        caution_count += 1
    
    # Gas evaluation
    gas_hazardous = gas >= 63
    gas_caution = gas >= 40 and gas < 63
    if gas_hazardous:
        hazardous_count += 1
    elif gas_caution:
        caution_count += 1
    
    # CO evaluation
    co_hazardous = co > 30
    co_caution = co >= 10 and co <= 30
    if co_hazardous:
        hazardous_count += 1
    elif co_caution:
        caution_count += 1
    
    # ═════════════════════════════════════════════════════════════════════
    # HAZARDOUS COMBINATIONS
    # ═════════════════════════════════════════════════════════════════════
    
    # PM2.5 + Gas (Smoke Detected)
    if pm25_caution and gas_caution:
        return 2, "HAZARDOUS: COMBUSTION RISK. EQUIP MASKS & SUSPEND HOT WORKS"
    
    # PM2.5 + CO (Fire Hazard)
    if pm25_caution and co_caution:
        return 2, "HAZARDOUS: FINE DUST + CO DETECTED. EQUIP MASKS & INSPECT FOR FIRE"
    
    # Gas + CO (Chemical Vapors)
    if gas_caution and co_caution:
        return 2, "HAZARDOUS: POISONOUS GAS. EQUIP RESPIRATORS & CLEAR THE ZONE"
    
    # PM2.5 + PM10 (Dust Storm)
    if pm25_caution and pm10_caution and humidity < 95:
        return 2, "HAZARDOUS: SEVERE DUST. REQUIRE N95 MASKS & SUPPRESS DUST SOURCE"
    
    # 3+ sensors in caution range
    if caution_count >= 3:
        return 2, "HAZARDOUS: TOXIC ATMOSPHERE. REQUIRE FULL PPE & SECURE ZONE"
    
    # ═════════════════════════════════════════════════════════════════════
    # WET-BULB ESCALATION: Override with heat stress
    # ═════════════════════════════════════════════════════════════════════
    
    # Critical heat stress (Tw > 35°C)
    if tw > 35:
        return 2, "HAZARDOUS: EXTREME HEAT. REQUIRE SHADED REST & MONITOR WORKERS"
    
    # Extreme heat stress (Tw > 30°C) - escalates to hazardous
    if tw > 30:
        return 2, "HAZARDOUS: HIGH HEAT INDEX. ROTATE WORKERS & REQUIRE HYDRATION"
    
    # ═════════════════════════════════════════════════════════════════════
    # NO HAZARDOUS SENSORS: Check for CAUTION conditions
    # ═════════════════════════════════════════════════════════════════════
    
    if caution_count == 0:
        # All sensors in safe range
        if humidity >= 60 and humidity < 95:
            return 0, "SAFE: ELEVATED HUMIDITY ONLY. CONTINUE OPERATIONS WITH HYDRATION"
        else:
            return 0, "SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS"
    
    # ═════════════════════════════════════════════════════════════════════
    # CAUTION CLASSIFICATIONS
    # ═════════════════════════════════════════════════════════════════════
    
    # Single PM2.5 in caution
    if pm25_caution and caution_count == 1:
        return 1, "CAUTION: FINE DUST DETECTED. EQUIP N95 MASKS"
    
    # Single PM10 in caution
    if pm10_caution and caution_count == 1:
        return 1, "CAUTION: HIGH DUST LEVELS. EQUIP N95 MASKS & DAMPEN THE GROUND"
    
    # Single Gas in caution
    if gas_caution and caution_count == 1:
        return 1, "CAUTION: TRACE GAS DETECTED. CHECK THE SOURCE"
    
    # Single CO in caution
    if co_caution and caution_count == 1:
        return 1, "CAUTION: ELEVATED CO. EQUIP N95 MASKS & MONITOR EXPOSURE"
    
    # PM10 + Gas combination
    if pm10_caution and gas_caution:
        return 1, "CAUTION: DUST & GAS TRACES. EQUIP N95 MASKS"
    
    # PM10 + CO combination
    if pm10_caution and co_caution:
        return 1, "CAUTION: FINE DUST + CO DETECTED. EQUIP MASKS & STANDBY"
    
    # 2-3 sensors in caution range
    if caution_count >= 2:
        return 1, "CAUTION: DECLINING AIR QUALITY. REQUIRE BASIC PPE"
    
    # Heat stress escalation (Tw 27-30°C)
    if tw > 26 and tw <= 30:
        return 1, "CAUTION: HIGH TEMPERATURE. REQUIRE HYDRATION BREAKS"
    
    # Default safe if nothing triggered
    if humidity >= 60 and humidity < 95:
        return 0, "SAFE: ELEVATED HUMIDITY ONLY. CONTINUE OPERATIONS WITH HYDRATION"
    else:
        return 0, "SAFE: AIR QUALITY OPTIMAL. CONTINUE OPERATIONS"


# ═══════════════════════════════════════════════════════════════════════════
# MAIN SCRIPT
# ═══════════════════════════════════════════════════════════════════════════

def update_csv_files():
    """Update all CSV files in Testing Dataset folder"""
    
    testing_dir = r"c:\Users\MAKI\Documents\GitHub\Air-Quality-Prediction\Testng Dataset"
    
    if not os.path.exists(testing_dir):
        print(f"❌ Testing Dataset directory not found: {testing_dir}")
        return
    
    csv_files = list(Path(testing_dir).glob("*.csv"))
    
    if not csv_files:
        print(f"❌ No CSV files found in {testing_dir}")
        return
    
    print("="*70)
    print("UPDATE TESTING DATASET REMARKS")
    print("="*70)
    print(f"\nFound {len(csv_files)} CSV files to update\n")
    
    for csv_file in sorted(csv_files):
        print(f"\nProcessing: {csv_file.name}")
        print("-" * 70)
        
        try:
            # Read CSV
            df = pd.read_csv(csv_file, skipinitialspace=True)
            
            print(f"  Rows: {len(df)}")
            print(f"  Columns: {list(df.columns)}")
            
            # Apply classification and remarks
            results = df.apply(
                lambda row: pd.Series(apply_classification_and_remarks(row)),
                axis=1
            )
            
            df['Class'] = results[0].astype(int)
            df['Remark'] = results[1]
            
            # Save updated CSV
            df.to_csv(csv_file, index=False)
            
            # Print summary
            class_dist = df['Class'].value_counts().sort_index()
            print(f"\n  ✓ Updated successfully")
            print(f"  Class distribution:")
            for cls in [0, 1, 2]:
                count = class_dist.get(cls, 0)
                pct = 100 * count / len(df)
                print(f"    Class {cls}: {count} rows ({pct:.1f}%)")
            
            # Show sample remarks for each class
            print(f"\n  Sample remarks:")
            for cls in [0, 1, 2]:
                sample = df[df['Class'] == cls]['Remark'].iloc[0] if len(df[df['Class'] == cls]) > 0 else "N/A"
                print(f"    Class {cls}: {sample[:60]}...")
        
        except Exception as e:
            print(f"  ❌ Error: {str(e)}")
    
    print("\n" + "="*70)
    print("✓ ALL FILES UPDATED SUCCESSFULLY")
    print("="*70)


if __name__ == '__main__':
    update_csv_files()
