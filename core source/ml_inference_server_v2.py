#!/usr/bin/env python3
"""
════════════════════════════════════════════════════════════════════════
ML INFERENCE SERVER FOR ESP32 AIR QUALITY PREDICTION
════════════════════════════════════════════════════════════════════════

This Flask-based server runs on a local machine (laptop/PC) and provides
real-time ML inference for the ESP32 device.

ARCHITECTURE:
  ESP32 (Device) → WiFi → Local Network → ML Server (This file)
                                              ↓
                                         Model Load
                                         Preprocessing
                                         Inference
                                              ↓
                                         JSON Response → ESP32

ADVANTAGES:
✓ Offload heavy ML computation to server (ESP32 can't handle complex models)
✓ Centralized model updates (change model without reflashing ESP32)
✓ Real-time predictions with 100-200ms latency
✓ Automatic fallback to threshold mode if server unavailable

REQUIREMENTS:
  pip install flask numpy scikit-learn pandas flask-cors

USAGE:
  python ml_inference_server_v2.py
  
Server will start on: http://localhost:5000
"""

import os
import sys
import json
import pickle
import numpy as np
from datetime import datetime
from flask import Flask, request, jsonify
from flask_cors import CORS

# ════════════════════════════════════════════════════════════════════
# CONFIGURATION
# ════════════════════════════════════════════════════════════════════

CONFIG = {
    'HOST': '0.0.0.0',  # Listen on all interfaces
    'PORT': 5000,
    'DEBUG': True,
    'MODEL_PATH': '../models/random_forest_model.pkl',
    'SCALER_PATH': '../models/scaler.pkl',
    'FEATURE_COLUMNS': ['pm2_5', 'pm10', 'temp', 'humidity', 'gas', 'co', 'time_of_day'],
    'CLASS_NAMES': ['SAFE', 'CAUTION', 'HAZARDOUS'],
    'CONFIDENCE_THRESHOLD': 0.90,
}

# ════════════════════════════════════════════════════════════════════
# INITIALIZE FLASK APP
# ════════════════════════════════════════════════════════════════════

app = Flask(__name__)
CORS(app)

# Global model objects
MODEL = None
SCALER = None
MODEL_LOADED = False

# ════════════════════════════════════════════════════════════════════
# MODEL LOADING
# ════════════════════════════════════════════════════════════════════

def load_model():
    """Load trained Random Forest model and scaler"""
    global MODEL, SCALER, MODEL_LOADED
    
    try:
        # Get the directory of this script
        current_dir = os.path.dirname(os.path.abspath(__file__))
        model_path = os.path.join(current_dir, CONFIG['MODEL_PATH'])
        scaler_path = os.path.join(current_dir, CONFIG['SCALER_PATH'])
        
        print(f"\n{'='*70}")
        print("LOADING ML MODEL AND SCALER")
        print(f"{'='*70}")
        print(f"Script directory: {current_dir}")
        print(f"Model path: {model_path}")
        print(f"Scaler path: {scaler_path}")
        
        # Check if files exist
        if not os.path.exists(model_path):
            print(f"✗ Model file not found: {model_path}")
            print(f"  Please ensure: random_forest_model.pkl exists in models/ directory")
            raise FileNotFoundError(f"Model file not found: {model_path}")
        
        if not os.path.exists(scaler_path):
            print(f"✗ Scaler file not found: {scaler_path}")
            raise FileNotFoundError(f"Scaler file not found: {scaler_path}")
        
        # Load model
        with open(model_path, 'rb') as f:
            MODEL = pickle.load(f)
        print(f"✓ Model loaded: {type(MODEL).__name__}")
        print(f"  - Trees: {MODEL.n_estimators}")
        print(f"  - Features: {MODEL.n_features_in_}")
        print(f"  - Classes: {MODEL.classes_}")
        
        # Load scaler
        with open(scaler_path, 'rb') as f:
            SCALER = pickle.load(f)
        print(f"✓ Scaler loaded successfully")
        
        MODEL_LOADED = True
        print(f"\n✓ MODEL READY FOR INFERENCE\n")
        
    except Exception as e:
        print(f"\n✗ ERROR LOADING MODEL: {str(e)}")
        MODEL_LOADED = False
        raise

# ════════════════════════════════════════════════════════════════════
# UTILITY FUNCTIONS
# ════════════════════════════════════════════════════════════════════

def validate_input_data(data):
    """Validate and check input sensor data"""
    errors = []
    
    for feature in CONFIG['FEATURE_COLUMNS']:
        if feature not in data:
            errors.append(f"Missing feature: {feature}")
        else:
            try:
                float(data[feature])
            except (ValueError, TypeError):
                errors.append(f"Invalid value for {feature}: {data[feature]}")
    
    return errors

def preprocess_features(data):
    """Convert raw sensor data to scaled features"""
    try:
        # Extract features in correct order
        features = np.array([
            data['pm2_5'],
            data['pm10'],
            data['temp'],
            data['humidity'],
            data['gas'],
            data['co'],
            data['time_of_day']
        ]).reshape(1, -1)
        
        # Scale features
        features_scaled = SCALER.transform(features)
        
        return features_scaled
    
    except Exception as e:
        raise ValueError(f"Error in preprocessing: {str(e)}")

def make_prediction(features):
    """Run inference with the trained model"""
    try:
        # Get class prediction
        prediction = MODEL.predict(features)[0]
        
        # Get prediction probabilities
        probabilities = MODEL.predict_proba(features)[0]
        confidence = max(probabilities)
        
        return {
            'prediction': int(prediction),
            'confidence': float(confidence),
            'probabilities': {
                'safe': float(probabilities[0]),
                'caution': float(probabilities[1]),
                'hazardous': float(probabilities[2])
            }
        }
    
    except Exception as e:
        raise RuntimeError(f"Error during prediction: {str(e)}")

# ════════════════════════════════════════════════════════════════════
# FLASK ROUTES
# ════════════════════════════════════════════════════════════════════

@app.route('/health', methods=['GET'])
def health_check():
    """Health check endpoint - verify server is running"""
    return jsonify({
        'status': 'SERVER_RUNNING',
        'model_loaded': MODEL_LOADED,
        'timestamp': datetime.now().isoformat()
    }), 200

@app.route('/model-info', methods=['GET'])
def get_model_info():
    """Get information about the loaded model"""
    if not MODEL_LOADED:
        return jsonify({'error': 'Model not loaded'}), 503
    
    return jsonify({
        'model_type': type(MODEL).__name__,
        'n_trees': MODEL.n_estimators,
        'n_features': MODEL.n_features_in_,
        'n_classes': len(MODEL.classes_),
        'classes': [str(c) for c in MODEL.classes_],
        'feature_names': CONFIG['FEATURE_COLUMNS'],
        'class_names': CONFIG['CLASS_NAMES']
    }), 200

@app.route('/predict', methods=['POST'])
def predict():
    """
    Main prediction endpoint
    
    Receives sensor data from ESP32, performs inference, returns classification
    
    INPUT (JSON):
    {
        "pm2_5": 35.2,
        "pm10": 55.1,
        "temp": 28.5,
        "humidity": 65.0,
        "gas": 250.5,
        "co": 12.3,
        "time_of_day": 14
    }
    
    OUTPUT (JSON):
    {
        "prediction": 0,
        "confidence": 0.99,
        "class_name": "SAFE",
        "probabilities": {
            "safe": 0.99,
            "caution": 0.01,
            "hazardous": 0.00
        },
        "timestamp": "2026-04-07T14:30:45.123456"
    }
    """
    
    try:
        # Check if model is loaded
        if not MODEL_LOADED:
            return jsonify({
                'error': 'Model not loaded. Server may still be initializing.',
                'status': 'ERROR'
            }), 503
        
        # Get JSON data
        data = request.get_json()
        
        if not data:
            return jsonify({
                'error': 'No JSON data provided',
                'status': 'ERROR'
            }), 400
        
        # Validate input
        validation_errors = validate_input_data(data)
        if validation_errors:
            return jsonify({
                'error': 'Invalid input data',
                'details': validation_errors,
                'status': 'ERROR'
            }), 400
        
        # Preprocess features
        features_scaled = preprocess_features(data)
        
        # Make prediction
        result = make_prediction(features_scaled)
        
        # Add class name and metadata
        result['class_name'] = CONFIG['CLASS_NAMES'][result['prediction']]
        result['timestamp'] = datetime.now().isoformat()
        result['status'] = 'SUCCESS'
        
        # Add warning if confidence is low
        if result['confidence'] < CONFIG['CONFIDENCE_THRESHOLD']:
            result['warning'] = f"Low confidence ({result['confidence']:.2%}). Use with caution."
        
        return jsonify(result), 200
    
    except Exception as e:
        print(f"✗ Error during prediction: {str(e)}")
        return jsonify({
            'error': str(e),
            'status': 'ERROR',
            'timestamp': datetime.now().isoformat()
        }), 500

@app.route('/predict-batch', methods=['POST'])
def predict_batch():
    """
    Batch prediction endpoint - predict multiple samples at once
    Useful for testing or logging
    
    INPUT:
    {
        "samples": [
            {"pm2_5": 35.2, "pm10": 55.1, ...},
            {"pm2_5": 25.0, "pm10": 45.0, ...}
        ]
    }
    """
    
    try:
        if not MODEL_LOADED:
            return jsonify({'error': 'Model not loaded'}), 503
        
        data = request.get_json()
        samples = data.get('samples', [])
        
        if not samples:
            return jsonify({'error': 'No samples provided'}), 400
        
        predictions = []
        
        for sample in samples:
            validation_errors = validate_input_data(sample)
            if validation_errors:
                predictions.append({
                    'error': validation_errors,
                    'status': 'ERROR'
                })
                continue
            
            try:
                features_scaled = preprocess_features(sample)
                result = make_prediction(features_scaled)
                result['class_name'] = CONFIG['CLASS_NAMES'][result['prediction']]
                result['status'] = 'SUCCESS'
                predictions.append(result)
            except Exception as e:
                predictions.append({
                    'error': str(e),
                    'status': 'ERROR'
                })
        
        return jsonify({
            'predictions': predictions,
            'total': len(samples),
            'successful': sum(1 for p in predictions if p.get('status') == 'SUCCESS'),
            'timestamp': datetime.now().isoformat()
        }), 200
    
    except Exception as e:
        return jsonify({'error': str(e), 'status': 'ERROR'}), 500

# ════════════════════════════════════════════════════════════════════
# ERROR HANDLERS
# ════════════════════════════════════════════════════════════════════

@app.errorhandler(404)
def not_found(error):
    return jsonify({
        'error': 'Endpoint not found',
        'available_endpoints': [
            '/health',
            '/model-info',
            '/predict',
            '/predict-batch'
        ]
    }), 404

@app.errorhandler(500)
def internal_error(error):
    return jsonify({
        'error': 'Internal server error',
        'details': str(error)
    }), 500

# ════════════════════════════════════════════════════════════════════
# MAIN
# ════════════════════════════════════════════════════════════════════

if __name__ == '__main__':
    print("\n")
    print("╔════════════════════════════════════════════════════════════╗")
    print("║  ML INFERENCE SERVER FOR ESP32 AIR QUALITY PREDICTION     ║")
    print("║  Status: STARTING...                                      ║")
    print("╚════════════════════════════════════════════════════════════╝")
    
    # Load model on startup
    try:
        load_model()
    except Exception as e:
        print(f"\n✗ FATAL ERROR: Could not load model")
        print(f"  {str(e)}")
        print(f"\nServer will still start in limited mode.")
        print(f"Please place model files in the models/ directory.")
    
    # Start Flask server
    print(f"\n{'='*70}")
    print("STARTING FLASK SERVER")
    print(f"{'='*70}")
    print(f"Server Address: http://0.0.0.0:{CONFIG['PORT']}")
    print(f"Accessible from ESP32 at: http://<YOUR_LAPTOP_IP>:{CONFIG['PORT']}")
    print(f"\nExample ESP32 URL: http://192.168.1.100:{CONFIG['PORT']}/predict")
    print(f"\n✓ To find your laptop IP:")
    print(f"  Windows: ipconfig (look for IPv4 Address)")
    print(f"  Mac/Linux: ifconfig (look for inet)")
    print(f"\nServer running. Press CTRL+C to stop.\n")
    
    app.run(host=CONFIG['HOST'], port=CONFIG['PORT'], debug=CONFIG['DEBUG'])
