#!/usr/bin/env python3
"""
Convert 200-tree Random Forest model to C++ header file for ESP32 embedding
This script monitors for the trained model and generates model.h once it's ready
"""

import pickle
import numpy as np
import os
import time

def generate_tree_cpp(tree, tree_idx, feature_names):
    """Generate C++ code for a single decision tree"""
    code = f"\n// Tree {tree_idx}\n"
    code += f"int predict_tree_{tree_idx}(const float* features) {{\n"
    code += f"    // Max depth: {tree.get_depth()}\n"
    
    tree_struct = tree.tree_
    
    # Extract tree structure
    feature = tree_struct.feature
    threshold = tree_struct.threshold
    children_left = tree_struct.children_left
    children_right = tree_struct.children_right
    value = tree_struct.value
    
    # Generate recursive traversal
    def generate_node(node_id, depth=0):
        indent = "    " * (depth + 1)
        
        if children_left[node_id] == -1:  # Leaf node
            # Get class prediction
            class_votes = value[node_id][0]
            predicted_class = np.argmax(class_votes)
            return f"{indent}return {int(predicted_class)};"
        else:
            # Internal node
            feature_idx = feature[node_id]
            threshold_val = threshold[node_id]
            feat_name = feature_names[feature_idx] if feature_idx < len(feature_names) else f"features[{feature_idx}]"
            
            code = f"{indent}if (features[{feature_idx}] <= {threshold_val}f) {{\n"
            code += generate_node(children_left[node_id], depth + 1)
            code += f"{indent}}} else {{\n"
            code += generate_node(children_right[node_id], depth + 1)
            code += f"{indent}}}\n"
            return code
    
    code += generate_node(0, 0)
    code += "}\n"
    
    return code

def main():
    print("Waiting for model training to complete...")
    print("Monitoring: models/random_forest_model.pkl")
    
    # Wait for the model file
    while not os.path.exists('models/random_forest_model.pkl'):
        print(".", end="", flush=True)
        time.sleep(5)
    
    print("\n\nLoading model...")
    
    # Load model and scaler
    with open('models/random_forest_model.pkl', 'rb') as f:
        model = pickle.load(f)
    
    with open('models/scaler.pkl', 'rb') as f:
        scaler = pickle.load(f)
    
    print(f"[OK] Model loaded: {model.n_estimators} trees, {model.n_features_in_} features, {model.n_classes_} classes")
    print(f"[OK] Scaler loaded: StandardScaler")
    
    # Feature names
    feature_names = list(model.feature_names_in_) if hasattr(model, 'feature_names_in_') else [f"feature_{i}" for i in range(model.n_features_in_)]
    print(f"[OK] Features: {model.n_features_in_} total")
    
    # Get scaler parameters
    scaler_mean = scaler.mean_
    scaler_scale = scaler.scale_
    
    print("\nGenerating C++ code...")
    
    # Start generating C++ header
    cpp_code = f'''/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model (200 trees)
 * Model Type: Random Forest Classifier
 * Features: {model.n_features_in_} (Core: PM2.5, PM10, Temp, Humidity, Gas, CO, TimeOfDay, WetBulb + Engineered: ratios, deltas, lags, volatility, trends, anomalies)
 * Classes: {model.n_classes_} (0=Safe, 1=Caution, 2=Hazardous)
 * Trees: {model.n_estimators}
 * Training Data: 20,568 samples from 8 MILES Protocol scenarios
 * Training Target: Safety-critical minority class (Caution) detection
 * 
 * USAGE:
 *   float features[{model.n_features_in_}] = {{core_sensors[8], engineered_features[{model.n_features_in_-8}]}};
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

const float SCALER_MEAN[] = {{
'''
    
    for i, mean_val in enumerate(scaler_mean):
        cpp_code += f"    {mean_val}f,  // feature_{i}\n"
    
    cpp_code += f"""}};

const float SCALER_SCALE[] = {{
"""
    
    for i, scale_val in enumerate(scaler_scale):
        cpp_code += f"    {scale_val}f,  // feature_{i}\n"
    
    cpp_code += f"""}};

const int NUM_FEATURES = {model.n_features_in_};
const int NUM_CLASSES = {model.n_classes_};
const int NUM_TREES = {model.n_estimators};

// ════════════════════════════════════════════════════════════════════════
// FEATURE PREPROCESSING (StandardScaler normalization)
// ════════════════════════════════════════════════════════════════════════

void normalize_features(float* features) {{
    for (int i = 0; i < NUM_FEATURES; i++) {{
        features[i] = (features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];
    }}
}}

"""
    
    # Generate all tree functions
    print(f"Generating {model.n_estimators} decision trees...")
    for tree_idx, tree in enumerate(model.estimators_):
        if (tree_idx + 1) % 50 == 0:
            print(f"  Tree {tree_idx + 1}/{model.n_estimators}... [OK]")
        cpp_code += generate_tree_cpp(tree, tree_idx, feature_names)
    
    # Generate predict function
    cpp_code += f"""
// ════════════════════════════════════════════════════════════════════════
// ENSEMBLE PREDICTION (Vote across all {model.n_estimators} trees)
// ════════════════════════════════════════════════════════════════════════

int predict(float* features) {{
    normalize_features(features);
    
    int votes[NUM_CLASSES] = {{0}};
    
"""
    
    for tree_idx in range(model.n_estimators):
        cpp_code += f"    votes[predict_tree_{tree_idx}(features)]++;\n"
    
    cpp_code += """    
    int max_votes = votes[0];
    int predicted_class = 0;
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return predicted_class;
}

// Get confidence as fraction of votes for predicted class
float get_confidence(float* features) {
    normalize_features(features);
    
    int votes[NUM_CLASSES] = {0};
    
"""
    
    for tree_idx in range(model.n_estimators):
        cpp_code += f"    votes[predict_tree_{tree_idx}(features)]++;\n"
    
    cpp_code += """    
    int max_votes = votes[0];
    int predicted_class = 0;
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return (float)max_votes / NUM_TREES;
}

#endif  // MODEL_H
"""
    
    # Write to file
    print("\nWriting to firmware/model.h...")
    os.makedirs('firmware', exist_ok=True)
    with open('firmware/model.h', 'w', encoding='utf-8') as f:
        f.write(cpp_code)
    
    file_size = os.path.getsize('firmware/model.h')
    print(f"[OK] C++ model generated successfully!")
    print(f"  File: firmware/model.h")
    print(f"  Size: {file_size:,} bytes ({file_size/1024:.1f} KB)")
    print(f"  Trees: {model.n_estimators}")
    print(f"  Features: {model.n_features_in_}")
    print(f"  Classes: {model.n_classes_}")
    
    print("\nNEXT STEPS:")
    print("  1. Update ESP32 firmware with new model.h")
    print("  2. Upload to device")
    print(f"  3. Model now uses {model.n_estimators} trees for improved minority class detection")

if __name__ == "__main__":
    main()
