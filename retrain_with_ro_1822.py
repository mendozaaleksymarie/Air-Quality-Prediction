"""
RETRAIN RANDOM FOREST MODEL WITH RO = 1822
Update CO calibration and regenerate all model files
"""

import pandas as pd
import numpy as np
import pickle
import os
import sys
from pathlib import Path
from sklearn.ensemble import RandomForestClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, accuracy_score
import matplotlib.pyplot as plt
import seaborn as sns

# Constants for MQ7 conversion (RO = 1822)
VIN = 3.3
ADC_MAX = 4095
RL = 10000
RO_NEW = 1822  # Updated from old 2120
COEFF = 99.042
EXPONENT = -1.518

# Paths
PROJECT_DIR = Path(__file__).parent
DATASET_PATH = PROJECT_DIR / 'dataset' / 'combined_data.csv'
MODEL_SAVE_PATH = PROJECT_DIR / 'models' / 'random_forest_model.pkl'
SCALER_SAVE_PATH = PROJECT_DIR / 'models' / 'scaler.pkl'
MODEL_H_PATH = PROJECT_DIR / 'firmware' / 'model.h'

def convert_adc_to_ppm_ro1822(adc_value):
    """Convert MQ7_ADC to MQ7_PPM using RO = 1822"""
    try:
        if pd.isna(adc_value) or adc_value < 0:
            return np.nan
        
        # Step 1: Vout = MQ7_ADC × (3.3 / 4095)
        vout = adc_value * (VIN / ADC_MAX)
        
        # Step 2: Rs = 10,000 × (3.3 - Vout) / Vout
        if vout == 0 or vout >= VIN:
            return np.nan
        rs = RL * (VIN - vout) / vout
        
        # Step 3: ratio = Rs / 1822
        ratio = rs / RO_NEW
        
        # Step 4: MQ7_PPM = 99.042 × ratio^(-1.518)
        ppm = COEFF * pow(ratio, EXPONENT)
        
        return max(ppm, 0.0)  # Ensure non-negative
    except:
        return np.nan

def recalibrate_data(df):
    """Recalibrate CO column using RO = 1822 and update derived features"""
    print("🔄 Recalibrating CO values with RO = 1822...")
    
    # Ensure data is sorted by timestamp
    if 'created_at' in df.columns:
        df = df.sort_values('created_at').reset_index(drop=True)
    
    # Convert CO ADC values to PPM using RO = 1822
    df['co'] = df['co'].apply(convert_adc_to_ppm_ro1822)
    
    # Recalculate all CO-dependent derived features
    print("📊 Recalculating CO-dependent features...")
    
    # 1. gas_co_ratio
    df['gas_co_ratio'] = (df['gas'] / (df['co'] + 0.1)).fillna(0).round(4)
    
    # 2. co_delta (rate of change)
    df['co_delta'] = df['co'].diff().fillna(0).round(2)
    
    # 3. co_lag_1, co_lag_3, co_lag_5
    df['co_lag_1'] = df['co'].shift(1).fillna(df['co'].iloc[0] if len(df) > 0 else 0).round(2)
    df['co_lag_3'] = df['co'].shift(3).fillna(df['co'].iloc[0] if len(df) > 0 else 0).round(2)
    df['co_lag_5'] = df['co'].shift(5).fillna(df['co'].iloc[0] if len(df) > 0 else 0).round(2)
    
    # Note: gas features remain unchanged as we only updated CO calibration
    
    return df

def train_model(df):
    """Train Random Forest model with updated CO calibration"""
    print("\n🤖 Training Random Forest Model...")
    
    # Select features
    feature_cols = [col for col in df.columns if col not in 
                   ['created_at', 'source_file', 'alarm_status', '_sensor_combo_key', 
                    '_sensor_combo_remark']]
    
    # Ensure label column exists
    if 'alarm_status' not in df.columns:
        print("❌ ERROR: 'alarm_status' column not found in data")
        return None, None
    
    X = df[feature_cols].fillna(0)
    y = df['alarm_status']
    
    print(f"   Features: {len(feature_cols)}")
    print(f"   Samples: {len(X)}")
    print(f"   Classes: {y.unique()}")
    print(f"   Class distribution:\n{y.value_counts()}")
    
    # Scale features
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    
    # Train Random Forest
    print("\n   Training with 200 trees...")
    model = RandomForestClassifier(
        n_estimators=200,
        max_depth=20,
        min_samples_split=5,
        min_samples_leaf=2,
        random_state=42,
        n_jobs=-1,
        verbose=0
    )
    
    model.fit(X_scaled, y)
    
    # Evaluate
    y_pred = model.predict(X_scaled)
    accuracy = accuracy_score(y, y_pred)
    print(f"\n✓ Training Accuracy: {accuracy:.4f}")
    
    # Print classification report
    print("\nClassification Report:")
    print(classification_report(y, y_pred, 
          target_names=['Safe (0)', 'Caution (1)', 'Hazardous (2)']))
    
    # Plot confusion matrix
    cm = confusion_matrix(y, y_pred)
    plt.figure(figsize=(10, 8))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues',
                xticklabels=['Safe', 'Caution', 'Hazardous'],
                yticklabels=['Safe', 'Caution', 'Hazardous'])
    plt.title('Confusion Matrix - Random Forest with RO = 1822')
    plt.ylabel('True Label')
    plt.xlabel('Predicted Label')
    plt.tight_layout()
    plt.savefig(str(PROJECT_DIR / 'models' / 'confusion_matrix_ro1822.png'), dpi=150)
    print("✓ Confusion matrix saved")
    
    return model, scaler, X_scaled

def save_model(model, scaler):
    """Save model and scaler to pickle files"""
    print("\n💾 Saving model files...")
    
    # Create models directory if it doesn't exist
    MODEL_DIR = PROJECT_DIR / 'models'
    MODEL_DIR.mkdir(exist_ok=True)
    
    # Save model
    with open(MODEL_SAVE_PATH, 'wb') as f:
        pickle.dump(model, f)
    print(f"✓ Model saved: {MODEL_SAVE_PATH}")
    
    # Save scaler
    with open(SCALER_SAVE_PATH, 'wb') as f:
        pickle.dump(scaler, f)
    print(f"✓ Scaler saved: {SCALER_SAVE_PATH}")

def generate_cpp_model(model, feature_names, scaler):
    """Generate C++ model.h file with embedded Random Forest"""
    print("\n📝 Generating C++ model.h...")
    
    cpp_code = generate_cpp_code(model, feature_names, scaler)
    
    # Save to file with UTF-8 encoding
    with open(MODEL_H_PATH, 'w', encoding='utf-8') as f:
        f.write(cpp_code)
    
    print(f"✓ Model header saved: {MODEL_H_PATH}")
    print(f"  File size: {len(cpp_code) / 1024 / 1024:.2f} MB")

def generate_tree_cpp(tree, tree_idx):
    """Generate C++ code for a single decision tree"""
    code = f"\n// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
    code += f"// Tree {tree_idx}\n"
    code += f"// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
    code += f"int predict_tree_{tree_idx}(const float* features) {{\n"
    
    tree_struct = tree.tree_
    feature = tree_struct.feature
    threshold = tree_struct.threshold
    children_left = tree_struct.children_left
    children_right = tree_struct.children_right
    value = tree_struct.value
    
    def generate_node(node_id, depth=0):
        indent = "    " * (depth + 1)
        
        if children_left[node_id] == -1:  # Leaf node
            class_votes = value[node_id][0]
            predicted_class = int(np.argmax(class_votes))
            return f"{indent}return {predicted_class};\n"
        else:
            feature_idx = int(feature[node_id])
            threshold_val = float(threshold[node_id])
            
            code_part = f"{indent}if (features[{feature_idx}] <= {threshold_val}f) {{\n"
            code_part += generate_node(children_left[node_id], depth + 1)
            code_part += f"{indent}}} else {{\n"
            code_part += generate_node(children_right[node_id], depth + 1)
            code_part += f"{indent}}}\n"
            return code_part
    
    code += generate_node(0, 0)
    code += "}\n"
    
    return code

def generate_cpp_code(model, feature_names, scaler):
    """Generate C++ code for embedded Random Forest model"""
    
    n_trees = model.n_estimators
    n_features = model.n_features_in_
    
    # Start with header
    code = u"""/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model
 * Model Type: Random Forest Classifier with 200 trees
 * Calibration: RO = 1822 (MQ7 CO sensor)
 * Features: 36 (8 core sensors + 28 engineered features)
 * Classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 * 
 * USAGE:
 *   float features[36] = {...}; // 36 engineered features
 *   int prediction = predict(features);  // Returns 0, 1, or 2
 * 
 * ════════════════════════════════════════════════════════════════════════
 */

#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <algorithm>

// ════════════════════════════════════════════════════════════════════════
// SCALER PARAMETERS (StandardScaler)
// ════════════════════════════════════════════════════════════════════════

const float SCALER_MEAN[] = {
"""
    
    # Scaler means
    for i, mean in enumerate(scaler.mean_):
        code += f"    {float(mean)}f,  // feature_{i}\n"
    code += "};\n\n"
    
    # Scaler scales  
    code += "const float SCALER_SCALE[] = {\n"
    for i, scale in enumerate(scaler.scale_):
        code += f"    {float(scale)}f,  // feature_{i}\n"
    code += "};\n\n"
    
    # Add decision trees
    code += u"""// ════════════════════════════════════════════════════════════════════════
// EMBEDDED DECISION TREES
// ════════════════════════════════════════════════════════════════════════

"""
    
    print(f"   Generating {n_trees} tree functions...")
    for i, tree in enumerate(model.estimators_):
        if (i + 1) % 50 == 0:
            print(f"   ... processed {i + 1} trees")
        code += generate_tree_cpp(tree, i)
    
    # Add voting function
    code += u"""
// ════════════════════════════════════════════════════════════════════════
// ENSEMBLE VOTING
// ════════════════════════════════════════════════════════════════════════

int predict(float* raw_features, int n_features) {
    // Ensure correct number of features
    if (n_features < """ + str(n_features) + u""") {
        return 0;  // Default to SAFE if insufficient features
    }
    
    // Scale features
    float features[""" + str(n_features) + u"""];
    for (int i = 0; i < """ + str(n_features) + u"""; i++) {
        features[i] = (raw_features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];
    }
    
    // Vote from all trees
    int votes[3] = {0, 0, 0};
    """
    
    # Add voting calls for all trees
    for i in range(n_trees):
        code += f"    votes[predict_tree_{i}(features)]++;\n"
    
    code += u"""
    // Return class with most votes
    int prediction = 0;
    int max_votes = votes[0];
    for (int i = 1; i < 3; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            prediction = i;
        }
    }
    
    return prediction;
}

#endif  // MODEL_H
"""
    
    return code

def main():
    """Main execution function"""
    print("=" * 80)
    print("RETRAIN RANDOM FOREST MODEL WITH RO = 1822")
    print("=" * 80)
    
    # Load data
    print(f"\n📂 Loading data from {DATASET_PATH}...")
    df = pd.read_csv(DATASET_PATH)
    print(f"✓ Loaded {len(df)} rows, {len(df.columns)} columns")
    
    # Recalibrate with new RO value
    df = recalibrate_data(df)
    
    # Train model
    model, scaler, X_scaled = train_model(df)
    
    if model is None:
        print("❌ Model training failed")
        return False
    
    # Save model and scaler
    save_model(model, scaler)
    
    # Get feature names
    feature_cols = [col for col in df.columns if col not in 
                   ['created_at', 'source_file', 'alarm_status', '_sensor_combo_key', 
                    '_sensor_combo_remark']]
    
    # Generate C++ model
    generate_cpp_model(model, feature_cols, scaler)
    
    print("\n" + "=" * 80)
    print("✅ RETRAINING COMPLETE WITH RO = 1822")
    print("=" * 80)
    print("\nFiles updated:")
    print(f"  ✓ {MODEL_SAVE_PATH}")
    print(f"  ✓ {SCALER_SAVE_PATH}")
    print(f"  ✓ {MODEL_H_PATH}")
    print(f"  ✓ {PROJECT_DIR / 'models' / 'confusion_matrix_ro1822.png'}")
    print("\nNote: Upload firmware/model.h to ESP32 device to deploy updated model")
    
    return True

if __name__ == '__main__':
    success = main()
    sys.exit(0 if success else 1)
