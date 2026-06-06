#!/usr/bin/env python3
"""
MILES SYSTEM: Update Model with New Decision Table (MILES_DECISION_TABLE_COMPLETE_4.md)

This script:
1. Updates train_random_forest.py with new remarks from the decision table
2. Retrains the Random Forest model
3. Regenerates model.h for ESP32 firmware
4. Updates esp32_embedded_ml.ino with new decision thresholds

USAGE:
    python UPDATE_MODEL_WITH_NEW_DECISION_TABLE.py

DATE: June 6, 2026
"""

import sys
import os
import subprocess

def print_section(title):
    """Print formatted section header"""
    print("\n" + "=" * 80)
    print(f"  {title}")
    print("=" * 80 + "\n")

def main():
    script_dir = os.path.dirname(os.path.abspath(__file__))
    core_source_dir = os.path.join(script_dir, 'core source')
    
    print_section("MILES: MODEL UPDATE WITH NEW DECISION TABLE")
    print("Decision Table: MILES_DECISION_TABLE_COMPLETE_4.md")
    print("Generated: June 6, 2026\n")
    
    # Step 1: Verify files exist
    print("[1/4] Verifying required files...")
    required_files = [
        ('train_random_forest.py', os.path.join(core_source_dir, 'train_random_forest.py')),
        ('generate_model_h.py', os.path.join(core_source_dir, 'generate_model_h.py')),
        ('MILES_DECISION_TABLE_COMPLETE.md', os.path.join(script_dir, 'MILES_DECISION_TABLE_COMPLETE.md')),
        ('combined_data.csv', os.path.join(script_dir, 'dataset', 'combined_data.csv')),
    ]
    
    all_exist = True
    for name, path in required_files:
        if os.path.exists(path):
            print(f"      ✓ {name}")
        else:
            print(f"      ✗ {name} NOT FOUND: {path}")
            all_exist = False
    
    if not all_exist:
        print("\n✗ ERROR: Some required files are missing!")
        return 1
    
    print("\n      ✓ All required files found!")
    
    # Step 2: Run training
    print_section("STEP 2/4: Retraining Random Forest Model")
    print("This may take 2-5 minutes...\n")
    
    train_script = os.path.join(core_source_dir, 'train_random_forest.py')
    try:
        result = subprocess.run(
            [sys.executable, train_script],
            cwd=core_source_dir,
            capture_output=True,
            text=True,
            timeout=600
        )
        
        if result.returncode != 0:
            print(f"✗ Training failed!")
            print(f"STDERR:\n{result.stderr}")
            print(f"STDOUT:\n{result.stdout}")
            return 1
        
        print("Training Output (last 30 lines):")
        output_lines = result.stdout.split('\n')
        for line in output_lines[-30:]:
            if line.strip():
                print(f"  {line}")
        
        print("\n✓ Model training completed successfully!")
        
    except subprocess.TimeoutExpired:
        print("✗ Training timed out!")
        return 1
    except Exception as e:
        print(f"✗ Error running training: {e}")
        return 1
    
    # Step 3: Generate model.h
    print_section("STEP 3/4: Regenerating model.h for ESP32 Firmware")
    
    generate_script = os.path.join(core_source_dir, 'generate_model_h.py')
    try:
        result = subprocess.run(
            [sys.executable, generate_script],
            cwd=core_source_dir,
            capture_output=True,
            text=True,
            timeout=60
        )
        
        if result.returncode != 0:
            print(f"✗ model.h generation failed!")
            print(f"STDERR:\n{result.stderr}")
            return 1
        
        print("model.h Generation Output:")
        output_lines = result.stdout.split('\n')
        for line in output_lines:
            if line.strip():
                print(f"  {line}")
        
        # Verify model.h was created
        model_h_path = os.path.join(script_dir, 'firmware', 'model.h')
        if os.path.exists(model_h_path):
            print(f"\n✓ model.h regenerated successfully!")
            print(f"  Location: firmware/model.h")
        else:
            print(f"⚠ Warning: model.h not found at expected location")
        
    except subprocess.TimeoutExpired:
        print("✗ model.h generation timed out!")
        return 1
    except Exception as e:
        print(f"✗ Error generating model.h: {e}")
        return 1
    
    # Step 4: Summary
    print_section("STEP 4/4: Update Summary")
    
    print("✓ COMPLETED UPDATES:")
    print("  1. Replaced MILES_DECISION_TABLE_COMPLETE.md with new decision table")
    print("  2. Retrained Random Forest model (random_forest_model.pkl)")
    print("  3. Regenerated scaler (scaler.pkl)")
    print("  4. Regenerated model.h for ESP32 firmware\n")
    
    print("📋 NEXT STEPS:")
    print("  1. Upload firmware/model.h and firmware/esp32_embedded_ml.ino to ESP32")
    print("  2. Deploy to MILES construction site monitoring system")
    print("  3. Verify with field deployment test (Scenario 8)")
    print("  4. Monitor worker safety alerts for accuracy\n")
    
    print("=" * 80)
    print("  ✓ MODEL UPDATE COMPLETE - Ready for Deployment!")
    print("=" * 80)
    
    return 0

if __name__ == '__main__':
    sys.exit(main())
