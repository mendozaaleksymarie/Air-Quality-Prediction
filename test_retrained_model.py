"""
Test script to verify the retrained model with RO = 1822
"""

import pickle
import numpy as np
import pandas as pd
from pathlib import Path

def test_model():
    print("=" * 80)
    print("TESTING RETRAINED MODEL WITH RO = 1822")
    print("=" * 80)
    
    # Load model and scaler
    print("\n1. Loading model files...")
    model_path = Path("models/random_forest_model.pkl")
    scaler_path = Path("models/scaler.pkl")
    
    with open(model_path, 'rb') as f:
        model = pickle.load(f)
    print(f"   ✓ Model loaded: {model_path}")
    
    with open(scaler_path, 'rb') as f:
        scaler = pickle.load(f)
    print(f"   ✓ Scaler loaded: {scaler_path}")
    
    # Verify model structure
    print(f"\n2. Model Structure:")
    print(f"   - Trees: {model.n_estimators}")
    print(f"   - Features: {model.n_features_in_}")
    print(f"   - Classes: {model.n_classes_}")
    print(f"   - Feature importance available: {hasattr(model, 'feature_importances_')}")
    
    # Verify scaler
    print(f"\n3. Scaler Parameters:")
    print(f"   - Mean values: {scaler.mean_.shape}")
    print(f"   - Scale values: {scaler.scale_.shape}")
    print(f"   - Mean (CO): {scaler.mean_[-1]:.4f}")
    print(f"   - Scale (CO): {scaler.scale_[-1]:.4f}")
    
    # Test with sample data
    print(f"\n4. Testing prediction with sample data...")
    
    # Create a sample feature vector (36 features)
    sample_features = np.random.randn(36) * 50 + 100  # Random normalized features
    sample_features_reshaped = sample_features.reshape(1, -1)
    
    # Scale features
    scaled_features = scaler.transform(sample_features_reshaped)
    
    # Make prediction
    prediction = model.predict(scaled_features)[0]
    probability = model.predict_proba(scaled_features)[0]
    
    print(f"   - Sample input shape: {sample_features_reshaped.shape}")
    print(f"   - Scaled features shape: {scaled_features.shape}")
    print(f"   - Prediction: {prediction} ({'Safe' if prediction == 0 else 'Caution' if prediction == 1 else 'Hazardous'})")
    print(f"   - Probabilities: Safe={probability[0]:.4f}, Caution={probability[1]:.4f}, Hazardous={probability[2]:.4f}")
    
    # Test feature importance
    print(f"\n5. Top 10 Most Important Features:")
    importances = model.feature_importances_
    top_indices = np.argsort(importances)[-10:][::-1]
    
    for rank, idx in enumerate(top_indices, 1):
        print(f"   {rank:2d}. Feature {idx:2d}: {importances[idx]:.4f}")
    
    # Load and check training data
    print(f"\n6. Training Data Verification:")
    dataset_path = Path("dataset/combined_data.csv")
    
    if dataset_path.exists():
        df = pd.read_csv(dataset_path, nrows=10)
        print(f"   - Dataset shape: {pd.read_csv(dataset_path).shape}")
        print(f"   - CO column (first 5 values): {df['co'].head().tolist()}")
        print(f"   - CO column dtype: {df['co'].dtype}")
        print(f"   - CO min/max: {df['co'].min():.4f} / {df['co'].max():.4f}")
    else:
        print(f"   ⚠️  Dataset not found at {dataset_path}")
    
    # Verify model.h exists
    print(f"\n7. Firmware File Verification:")
    model_h_path = Path("firmware/model.h")
    if model_h_path.exists():
        size = model_h_path.stat().st_size
        print(f"   ✓ model.h exists ({size / 1024 / 1024:.2f} MB)")
        
        # Check for RO parameter
        with open(model_h_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
            if '1822' in content or '1.822' in content:
                print(f"   ✓ Contains RO = 1822 calibration reference")
            if 'predict_tree_0' in content:
                print(f"   ✓ Contains embedded decision trees")
    else:
        print(f"   ❌ model.h not found at {model_h_path}")
    
    print("\n" + "=" * 80)
    print("✅ MODEL VERIFICATION COMPLETE")
    print("=" * 80)
    print("\nNext steps:")
    print("1. Upload firmware/model.h to ESP32 using Arduino IDE")
    print("2. Restart the ML inference server")
    print("3. Monitor CO sensor readings to verify they're in PPM (not ADC)")

if __name__ == "__main__":
    test_model()
