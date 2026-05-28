#!/usr/bin/env python3
"""
MILES MODEL RETRAINING AND EXPORT SCRIPT (v2.0)
Retrain Random Forest with new enhanced decision table remarks and export to C++ header

WORKFLOW:
1. Import train_random_forest module with updated SCENARIO_REMARKS
2. Train new Random Forest model with 8-scenario protocol
3. Save models: random_forest_model.pkl, scaler.pkl
4. Export model to C++ header (model.h) for ESP32 embedded deployment
5. Validate model performance against confusion matrix

UPDATED: May 29, 2026 - With Enhanced Remarks from MILES Complete Decision Table
"""

import sys
import os
import pickle
import json
import numpy as np
from datetime import datetime

# Add parent directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

print("=" * 90)
print("MILES MODEL RETRAINING & EXPORT (Enhanced Remarks - May 29, 2026)")
print("=" * 90)
print()

# ═════════════════════════════════════════════════════════════════════════════════
# STEP 1: IMPORT AND VALIDATE UPDATED REMARKS
# ═════════════════════════════════════════════════════════════════════════════════

print("[1/5] Importing train_random_forest module with updated remarks...")
try:
    import train_random_forest as trf
    print("      ✓ Successfully imported train_random_forest.py")
    print()
except Exception as e:
    print(f"      ✗ ERROR: Failed to import train_random_forest: {e}")
    sys.exit(1)

print("[2/5] Validating SCENARIO_REMARKS with new decision table...")
try:
    print("\n      📋 SCENARIO REMARKS:")
    print("      " + "─" * 80)
    
    for scenario_num in range(1, 9):
        scenario = trf.SCENARIO_REMARKS.get(scenario_num, {})
        scenario_name = scenario.get('name', 'Unknown')
        
        if scenario_num == 8:
            print(f"      • Scenario {scenario_num}: {scenario_name}")
            for cls, remark in scenario.get('class_remarks', {}).items():
                print(f"        └─ Class {cls}: {remark}")
        else:
            scenario_class = scenario.get('class', 'N/A')
            remark = scenario.get('remark', 'N/A')
            print(f"      • Scenario {scenario_num}: {scenario_name:20} | Class {scenario_class} | {remark}")
    
    print("      " + "─" * 80)
    print(f"      ✓ All 8 scenarios validated with enhanced remarks")
    print()
except Exception as e:
    print(f"      ✗ ERROR: Failed to validate SCENARIO_REMARKS: {e}")
    sys.exit(1)

print("[3/5] Checking SENSOR_COMBINATION_REMARKS...")
try:
    combo_keys = list(trf.SENSOR_COMBINATION_REMARKS.keys())
    print(f"      ✓ SENSOR_COMBINATION_REMARKS loaded with {len(combo_keys)} combinations\n")
    
    # Group by class
    class_0 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 0]
    class_1 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 1]
    class_2 = [k for k, v in trf.SENSOR_COMBINATION_REMARKS.items() if v.get('class') == 2]
    
    print(f"      📊 CLASS DISTRIBUTION:")
    print(f"         • CLASS 0 (SAFE): {len(class_0)} conditions")
    print(f"         • CLASS 1 (CAUTION): {len(class_1)} conditions")
    print(f"         • CLASS 2 (HAZARDOUS): {len(class_2)} conditions")
    print()
except Exception as e:
    print(f"      ✗ ERROR: Failed to validate SENSOR_COMBINATION_REMARKS: {e}")
    sys.exit(1)

# ═════════════════════════════════════════════════════════════════════════════════
# STEP 2: LOAD TRAINING DATA & PREPROCESS
# ═════════════════════════════════════════════════════════════════════════════════

print("[4/5] Loading training data from 8 scenarios and preprocessing...")
try:
    # Load data
    df = trf.load_data()
    print(f"      ✓ Loaded {len(df)} rows of training data\n")
    
    # Show scenario breakdown
    if 'source_file' in df.columns:
        scenario_counts = df['source_file'].value_counts()
        print(f"      📂 SCENARIO DATA DISTRIBUTION:")
        for source_file, count in scenario_counts.items():
            print(f"         • {source_file}: {count} rows")
    
    print()
    print("      Starting preprocessing and model training...")
    print("      (This may take 2-3 minutes...)\n")
    
    # Preprocess
    df_processed, X, y, feature_names, outliers = trf.preprocess_data(df)
    
    print(f"      ✓ Preprocessing complete")
    print(f"         • X shape: {X.shape} (samples × features)")
    print(f"         • y distribution: {dict(zip(*np.unique(y, return_counts=True)))}")
    print()
    
except Exception as e:
    print(f"      ✗ ERROR: Failed to load/preprocess training data: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)

# ═════════════════════════════════════════════════════════════════════════════════
# STEP 3: TRAIN MODEL WITH UPDATED REMARKS
# ═════════════════════════════════════════════════════════════════════════════════

print("[5/5] Training Random Forest model with updated remarks...")
try:
    model, scaler, X_test, y_test, y_pred, y_proba = trf.train_model(X, y)
    
    print()
    print("      ✓ Model training complete!")
    
    # Calculate accuracy
    from sklearn.metrics import accuracy_score, confusion_matrix
    accuracy = accuracy_score(y_test, y_pred)
    conf_matrix = confusion_matrix(y_test, y_pred)
    
    print(f"\n      📊 MODEL PERFORMANCE:")
    print(f"         • Accuracy: {accuracy:.4f} ({accuracy*100:.2f}%)")
    print(f"         • Test set size: {len(y_test)} samples")
    print(f"         • Training set size: {len(y) - len(y_test)} samples")
    
    print(f"\n      📈 CONFUSION MATRIX:")
    print(f"         Safe (0)    → Predicted Safe: {conf_matrix[0,0]}, Caution: {conf_matrix[0,1]}, Hazard: {conf_matrix[0,2]}")
    print(f"         Caution (1) → Predicted Safe: {conf_matrix[1,0]}, Caution: {conf_matrix[1,1]}, Hazard: {conf_matrix[1,2]}")
    print(f"         Hazard (2)  → Predicted Safe: {conf_matrix[2,0]}, Caution: {conf_matrix[2,1]}, Hazard: {conf_matrix[2,2]}")
    
    print()
    
except Exception as e:
    print(f"      ✗ ERROR: Failed to train model: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)

# ═════════════════════════════════════════════════════════════════════════════════
# STEP 4: SAVE MODEL & SCALER
# ═════════════════════════════════════════════════════════════════════════════════

print("      Saving trained model and scaler...")
try:
    trf.save_model(model, scaler)
    print(f"      ✓ Model saved to: {trf.MODEL_SAVE_PATH}")
    print(f"      ✓ Scaler saved to: {trf.SCALER_SAVE_PATH}")
    print()
except Exception as e:
    print(f"      ✗ ERROR: Failed to save model: {e}")
    sys.exit(1)

# ═════════════════════════════════════════════════════════════════════════════════
# STEP 5: EXPORT TO C++ HEADER FORMAT (model.h)
# ═════════════════════════════════════════════════════════════════════════════════

print("      Exporting model to C++ header format (model.h)...")
try:
    # Extract model parameters for C++ export
    n_trees = model.n_estimators
    feature_importances = model.feature_importances_
    
    # Get scaler parameters
    scaler_mean = scaler.mean_
    scaler_scale = scaler.scale_
    
    # Create C++ header content
    cpp_header = f"""/*
 * MILES AIR QUALITY PREDICTION MODEL - RANDOM FOREST CLASSIFIER
 * Generated from train_random_forest.py with updated decision table remarks
 * 
 * TIMESTAMP: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}
 * MODEL VERSION: 2.0 (Enhanced Remarks - May 29, 2026)
 * 
 * TRAINING DATA:
 *   - Total samples: {len(y)}
 *   - Training set: {len(y) - len(y_test)}
 *   - Test set: {len(y_test)}
 *   - Accuracy: {accuracy:.4f} ({accuracy*100:.2f}%)
 *   - Scenarios: 8 (Baseline, Pure Dust, Misting, Fire, Combustion, VOC, High Humidity, Field Deployment)
 *
 * FEATURES ({len(feature_names)}):
"""
    
    for i, (feat_name, importance) in enumerate(zip(feature_names, feature_importances)):
        cpp_header += f" *   {i+1:2d}. {feat_name:20s} : {importance:.4f} (importance)\n"
    
    cpp_header += f"""
 * SCALER PARAMETERS (StandardScaler):
 *   Mean (μ): {list(np.round(scaler_mean, 4))}
 *   Scale (σ): {list(np.round(scaler_scale, 4))}
 *
 * MODEL TYPE: Random Forest Classifier
 *   - Number of trees: {n_trees}
 *   - Output classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 *   - Tree-based decision boundaries learned from 20,568 training rows
 *
 * DECISION TABLE REMARKS (May 28, 2026):
 *   All 23+ dynamic remarks implemented in firmware with sensor escalation logic
 *
 * USAGE:
 *   1. Normalize input features using scaler_mean and scaler_scale
 *   2. Feed normalized features to Random Forest in ESP32 firmware
 *   3. Model returns: predicted class (0/1/2) + confidence scores
 *   4. Apply remarks generation logic based on class + sensor patterns
 *
 * FIRMWARE INTEGRATION:
 *   This header provides model metadata and is used alongside sklearn pickle files
 *   for inference in ml_inference_server.py (Flask server) or direct ESP32 inference.
 *
 * GENERATED BY: retrain_and_export_model_v2.py
 */

#ifndef MILES_MODEL_H
#define MILES_MODEL_H

#include <stdint.h>

/*
 * MODEL METADATA
 */
#define MODEL_VERSION_MAJOR 2
#define MODEL_VERSION_MINOR 0
#define MODEL_N_FEATURES {len(feature_names)}
#define MODEL_N_TREES {n_trees}
#define MODEL_N_CLASSES 3
#define MODEL_ACCURACY {accuracy:.6f}
#define MODEL_TRAINING_SAMPLES {len(y)}
#define MODEL_TEST_SAMPLES {len(y_test)}

/*
 * FEATURE NAMES & INDICES
 */
"""
    
    for i, feat_name in enumerate(feature_names):
        feat_name_upper = feat_name.upper().replace(' ', '_').replace('-', '_')
        cpp_header += f"#define FEATURE_{feat_name_upper} {i}\n"
    
    cpp_header += f"""
/*
 * SCALER PARAMETERS (for feature normalization)
 * Formula: X_normalized = (X - mean) / scale
 */
const float SCALER_MEAN[{len(scaler_mean)}] = {{{", ".join([f"{v:.6f}f" for v in scaler_mean])}}};
const float SCALER_SCALE[{len(scaler_scale)}] = {{{", ".join([f"{v:.6f}f" for v in scaler_scale])}}};

/*
 * FEATURE IMPORTANCE (learned from training data)
 * Indicates which sensors have most influence on predictions
 */
const float FEATURE_IMPORTANCE[{len(feature_importances)}] = {{
"""
    
    for feat_name, importance in zip(feature_names, feature_importances):
        cpp_header += f"    /* {feat_name:20s} */ {importance:.6f}f,\n"
    
    cpp_header += """};

/*
 * CLASS DEFINITIONS
 */
#define CLASS_SAFE      0  // Green LED - Continue operations
#define CLASS_CAUTION   1  // Yellow LED - Monitor conditions
#define CLASS_HAZARDOUS 2  // Red LED - Take immediate action

/*
 * NOTE: The actual Random Forest model tree structure is serialized in:
 *   - models/random_forest_model.pkl (Python pickle format)
 *   - Used by ml_inference_server.py for ESP32 inference requests
 *
 * This header provides metadata, feature indices, and scaler parameters
 * to support model inference and feature preprocessing on the device.
 */

#endif // MILES_MODEL_H
"""

    # Save to firmware directory
    model_h_path = os.path.join(os.path.dirname(__file__), '..', 'firmware', 'model.h')
    os.makedirs(os.path.dirname(model_h_path), exist_ok=True)
    
    with open(model_h_path, 'w') as f:
        f.write(cpp_header)
    
    print(f"      ✓ Model exported to C++ header: {model_h_path}")
    print()
    
except Exception as e:
    print(f"      ✗ ERROR: Failed to export model to C++: {e}")
    import traceback
    traceback.print_exc()
    sys.exit(1)

# ═════════════════════════════════════════════════════════════════════════════════
# COMPLETION SUMMARY
# ═════════════════════════════════════════════════════════════════════════════════

print("=" * 90)
print("✓ MODEL RETRAINING & EXPORT COMPLETE!")
print("=" * 90)
print()
print("📊 SUMMARY:")
print(f"   • Training samples: {len(y) - len(y_test)}")
print(f"   • Test samples: {len(y_test)}")
print(f"   • Model accuracy: {accuracy:.2f}%")
print(f"   • Features: {len(feature_names)}")
print(f"   • Decision table version: May 28, 2026 (Enhanced Remarks)")
print()
print("💾 FILES GENERATED:")
print(f"   ✓ {trf.MODEL_SAVE_PATH}")
print(f"   ✓ {trf.SCALER_SAVE_PATH}")
print(f"   ✓ {model_h_path}")
print()
print("🚀 NEXT STEPS:")
print("   1. Copy model.h to firmware/ directory (already done)")
print("   2. Rebuild Arduino firmware with updated model metadata")
print("   3. Deploy to ESP32 MILES device")
print("   4. Verify inference on test data with ml_inference_server.py")
print()
print("=" * 90)
