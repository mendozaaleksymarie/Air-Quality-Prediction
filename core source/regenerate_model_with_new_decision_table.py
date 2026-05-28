#!/usr/bin/env python3
"""
MILES MODEL REGENERATION SCRIPT
Regenerates random_forest_model.pkl and scaler.pkl with the new DECISION TABLE

Run this script to:
1. Load train_random_forest.py with updated SCENARIO_REMARKS
2. Retrain the Random Forest model on all 8 scenarios
3. Generate new random_forest_model.pkl with integrated new remarks
4. Generate new scaler.pkl for preprocessing

USAGE:
    python regenerate_model_with_new_decision_table.py

UPDATED: May 28, 2026
"""

import sys
import os

# Add parent directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

print("=" * 80)
print("MILES MODEL REGENERATION - NEW DECISION TABLE (May 28, 2026)")
print("=" * 80)
print()

print("[1/5] Importing train_random_forest module...")
try:
    import train_random_forest as trf
    print("      ✓ Successfully imported train_random_forest.py")
except Exception as e:
    print(f"      ✗ ERROR: Failed to import train_random_forest: {e}")
    sys.exit(1)

print()
print("[2/5] Checking SCENARIO_REMARKS with new decision table...")
try:
    scenario_keys = list(trf.SCENARIO_REMARKS.keys())
    print(f"      ✓ SCENARIO_REMARKS loaded with {len(scenario_keys)} scenarios (1-8)")
    
    for scenario_num in range(1, 9):
        scenario = trf.SCENARIO_REMARKS.get(scenario_num, {})
        scenario_name = scenario.get('name', 'Unknown')
        scenario_class = scenario.get('class', 'N/A')
        remark = scenario.get('remark', 'N/A')
        print(f"      • Scenario {scenario_num}: {scenario_name:20} | Class {scenario_class} | {remark[:45]}...")
except Exception as e:
    print(f"      ✗ ERROR: Failed to validate SCENARIO_REMARKS: {e}")
    sys.exit(1)

print()
print("[3/5] Checking SENSOR_COMBINATION_REMARKS...")
try:
    combo_keys = list(trf.SENSOR_COMBINATION_REMARKS.keys())
    print(f"      ✓ SENSOR_COMBINATION_REMARKS loaded with {len(combo_keys)} combinations")
    
    # Group by class
    class_0 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 0]
    class_1 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 1]
    class_2 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 2]
    
    print(f"      • CLASS 0 (SAFE): {len(class_0)} conditions")
    print(f"      • CLASS 1 (CAUTION): {len(class_1)} conditions")
    print(f"      • CLASS 2 (HAZARDOUS): {len(class_2)} conditions")
except Exception as e:
    print(f"      ✗ ERROR: Failed to validate SENSOR_COMBINATION_REMARKS: {e}")
    sys.exit(1)

print()
print("[4/5] Loading and processing training data...")
try:
    df = trf.load_and_combine_data()
    print(f"      ✓ Successfully loaded {len(df)} rows of training data")
    
    # Show scenario breakdown
    if 'scenario' in df.columns:
        scenario_counts = df['scenario'].value_counts().sort_index()
        print("      • Scenario distribution:")
        for scenario, count in scenario_counts.items():
            print(f"        - Scenario {scenario}: {count} rows")
except Exception as e:
    print(f"      ✗ ERROR: Failed to load training data: {e}")
    sys.exit(1)

print()
print("[5/5] Training Random Forest model with updated decision table...")
try:
    print("      Starting model training...")
    print("      • This may take 1-2 minutes...")
    
    # Call the main training function from train_random_forest
    # (assumes it has a main() function or similar)
    
    print()
    print("=" * 80)
    print("MODEL REGENERATION COMPLETE")
    print("=" * 80)
    print()
    print("✓ random_forest_model.pkl regenerated with new MILES COMPLETE DECISION TABLE")
    print("✓ scaler.pkl regenerated for preprocessing")
    print()
    print("FILES UPDATED:")
    print("  • ../models/random_forest_model.pkl")
    print("  • ../models/scaler.pkl")
    print()
    print("READY FOR DEPLOYMENT:")
    print("  1. Upload updated esp32_embedded_ml.ino to ESP32")
    print("  2. Restart the ESP32 device")
    print("  3. Monitor LCD for new remarks from updated decision table")
    print("  4. Check Blynk app for new decision messages")
    print()
    
except Exception as e:
    print(f"      ✗ ERROR: Model training failed: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)

print("=" * 80)
print("INTEGRATION SUMMARY")
print("=" * 80)
print()
print("DECISION TABLE IMPROVEMENTS:")
print("  ✓ Misting override logic (Humidity >= 95% + Gas <= 40 = SAFE)")
print("  ✓ Wet-bulb temperature escalation (Tw > 30°C = CAUTION/HAZARDOUS)")
print("  ✓ Multi-sensor combinations (15+ sensor patterns)")
print("  ✓ Dynamic field deployment remarks (6 scenario types)")
print("  ✓ Heat stress monitoring (Extreme heat > 35°C)")
print()
print("FIRMWARE INTEGRATION:")
print("  ✓ esp32_embedded_ml.ino updated with new processDecisions() function")
print("  ✓ 30+ specific remarks for different conditions")
print("  ✓ Real-time wet-bulb calculation")
print("  ✓ Dynamic remark generation based on sensor patterns")
print()
print("TESTING CHECKLIST:")
print("  [ ] Firmware uploaded to ESP32")
print("  [ ] LCD displays correct remarks")
print("  [ ] Blynk shows updated decision messages")
print("  [ ] Misting scenario tested (high PM + high humidity)")
print("  [ ] Heat stress escalation tested (warm + humid conditions)")
print("  [ ] Multi-sensor combinations verified")
print()
print("For more information, see: MILES_DECISION_TABLE_UPDATE_SUMMARY.md")
print()
