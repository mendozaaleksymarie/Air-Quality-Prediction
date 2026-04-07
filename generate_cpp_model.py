#!/usr/bin/env python3
"""
Convert sklearn Random Forest model to C++ header file for ESP32 embedding
"""

import pickle
import numpy as np
import os

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
    print("Loading model...")
    
    # Load model and scaler
    with open('models/random_forest_model.pkl', 'rb') as f:
        model = pickle.load(f)
    
    with open('models/scaler.pkl', 'rb') as f:
        scaler = pickle.load(f)
    
    print(f"✓ Model loaded: {model.n_estimators} trees, {model.n_features_in_} features, {model.n_classes_} classes")
    print(f"✓ Scaler loaded: StandardScaler")
    
    # Feature names
    feature_names = list(model.feature_names_in_) if hasattr(model, 'feature_names_in_') else [f"feature_{i}" for i in range(model.n_features_in_)]
    print(f"✓ Features: {feature_names}")
    
    # Get scaler parameters
    scaler_mean = scaler.mean_
    scaler_scale = scaler.scale_
    
    print("\nGenerating C++ code...")
    
    # Start generating C++ header
    cpp_code = '''/*
 * ════════════════════════════════════════════════════════════════════════
 * RANDOM FOREST MODEL - C++ EMBEDDED VERSION FOR ESP32
 * ════════════════════════════════════════════════════════════════════════
 * 
 * GENERATED: Automated conversion from Python sklearn model
 * Model Type: Random Forest Classifier
 * Features: 7 (PM2.5, PM10, Temperature, Humidity, Gas, CO, TimeOfDay)
 * Classes: 3 (0=Safe, 1=Caution, 2=Hazardous)
 * 
 * USAGE:
 *   float features[7] = {pm2_5, pm10, temp, humidity, gas, co, time_of_day};
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
'''
    
    # Add scaler means
    for i, mean in enumerate(scaler_mean):
        cpp_code += f"    {mean}f,  // {feature_names[i]}\n"
    cpp_code += "};\n\n"
    
    cpp_code += "const float SCALER_SCALE[] = {\n"
    
    # Add scaler scales
    for i, scale in enumerate(scaler_scale):
        cpp_code += f"    {scale}f,  // {feature_names[i]}\n"
    cpp_code += "};\n\n"
    
    cpp_code += f"const int NUM_FEATURES = {model.n_features_in_};\n"
    cpp_code += f"const int NUM_CLASSES = {model.n_classes_};\n"
    cpp_code += f"const int NUM_TREES = {model.n_estimators};\n\n"
    
    # Add feature normalization function
    cpp_code += """// ════════════════════════════════════════════════════════════════════════
// FEATURE PREPROCESSING (StandardScaler normalization)
// ════════════════════════════════════════════════════════════════════════

void normalize_features(float* features) {
    for (int i = 0; i < NUM_FEATURES; i++) {
        features[i] = (features[i] - SCALER_MEAN[i]) / SCALER_SCALE[i];
    }
}

"""
    
    # Generate all trees
    print(f"Generating {model.n_estimators} decision trees...")
    for i, tree in enumerate(model.estimators_):
        if i % 10 == 0:
            print(f"  Tree {i}/{model.n_estimators}...", end='\r')
        cpp_code += generate_tree_cpp(tree, i, feature_names)
    print(f"  Tree {model.n_estimators}/{model.n_estimators}... ✓")
    
    # Add ensemble prediction function
    cpp_code += """
// ════════════════════════════════════════════════════════════════════════
// RANDOM FOREST ENSEMBLE PREDICTION
// ════════════════════════════════════════════════════════════════════════

int predict(float features[NUM_FEATURES]) {
    // Create copy for normalization
    float normalized_features[NUM_FEATURES];
    for (int i = 0; i < NUM_FEATURES; i++) {
        normalized_features[i] = features[i];
    }
    
    // Normalize features using scaler parameters
    normalize_features(normalized_features);
    
    // Vote from all trees
    int votes[NUM_CLASSES] = {0, 0, 0};
    
"""
    
    # Add voting logic for each tree
    for i in range(model.n_estimators):
        cpp_code += f"    int vote_{i} = predict_tree_{i}(normalized_features);\n"
        cpp_code += f"    votes[vote_{i}]++;\n"
    
    cpp_code += """
    // Return class with most votes
    int predicted_class = 0;
    int max_votes = votes[0];
    
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
            predicted_class = i;
        }
    }
    
    return predicted_class;
}

// ════════════════════════════════════════════════════════════════════════
// GET CONFIDENCE SCORE (based on vote distribution)
// ════════════════════════════════════════════════════════════════════════

float get_confidence(float features[NUM_FEATURES]) {
    // Create copy for normalization
    float normalized_features[NUM_FEATURES];
    for (int i = 0; i < NUM_FEATURES; i++) {
        normalized_features[i] = features[i];
    }
    
    // Normalize features
    normalize_features(normalized_features);
    
    // Collect votes
    int votes[NUM_CLASSES] = {0, 0, 0};
    
"""
    
    # Add voting logic for confidence
    for i in range(model.n_estimators):
        cpp_code += f"    int vote_{i}_conf = predict_tree_{i}(normalized_features);\n"
        cpp_code += f"    votes[vote_{i}_conf]++;\n"
    
    cpp_code += """
    // Calculate confidence as ratio of max votes to total trees
    int max_votes = 0;
    for (int i = 0; i < NUM_CLASSES; i++) {
        if (votes[i] > max_votes) {
            max_votes = votes[i];
        }
    }
    
    float confidence = (float)max_votes / (float)NUM_TREES;
    return confidence;
}

#endif  // MODEL_H

// ════════════════════════════════════════════════════════════════════════
// END OF MODEL
// ════════════════════════════════════════════════════════════════════════
"""
    
    # Write to file
    output_file = "firmware/model.h"
    os.makedirs("firmware", exist_ok=True)
    
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(cpp_code)
    
    file_size = len(cpp_code) / 1024  # in KB
    print(f"\n✓ C++ model generated successfully!")
    print(f"  File: {output_file}")
    print(f"  Size: {file_size:.1f} KB")
    print(f"  Trees: {model.n_estimators}")
    print(f"  Features: {model.n_features_in_}")
    print(f"  Classes: {model.n_classes_}")
    print(f"\nNEXT STEPS:")
    print(f"  1. Include in firmware: #include \"model.h\"")
    print(f"  2. Call predict: int class = predict(sensor_array);")
    print(f"  3. Get confidence: float conf = get_confidence(sensor_array);")

if __name__ == "__main__":
    main()
