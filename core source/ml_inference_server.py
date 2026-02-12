"""
ML Inference Server for Air Quality Monitoring
Receives sensor data from ESP32 and returns predictions using Random Forest model
"""

from flask import Flask, request, jsonify
from flask_cors import CORS
import pandas as pd
import numpy as np
import pickle
import os
from datetime import datetime
import logging

app = Flask(__name__)
CORS(app)

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Model paths
import os
base_dir = os.path.dirname(os.path.dirname(__file__))
MODEL_PATH = os.path.join(base_dir, 'models', 'random_forest_model.pkl')
SCALER_PATH = os.path.join(base_dir, 'models', 'scaler.pkl')
DATA_LOG_PATH = os.path.join(base_dir, 'logs', 'sensor_data.csv')

# Load trained model and scaler
model = None
scaler = None

def load_model():
    """Load the trained Random Forest model"""
    global model, scaler
    try:
        if os.path.exists(MODEL_PATH):
            with open(MODEL_PATH, 'rb') as f:
                model = pickle.load(f)
            logger.info("Model loaded successfully")
        else:
            logger.warning(f"Model not found at {MODEL_PATH}")
            
        if os.path.exists(SCALER_PATH):
            with open(SCALER_PATH, 'rb') as f:
                scaler = pickle.load(f)
            logger.info("Scaler loaded successfully")
    except Exception as e:
        logger.error(f"Error loading model: {e}")

def get_aqi_category(pm25, pm10):
    """
    Determine Air Quality Index category based on PM values
    Based on EPA AQI standards
    """
    # PM2.5 breakpoints
    if pm25 <= 12.0:
        pm25_aqi = 'Good'
    elif pm25 <= 35.4:
        pm25_aqi = 'Moderate'
    elif pm25 <= 55.4:
        pm25_aqi = 'Unhealthy for Sensitive Groups'
    elif pm25 <= 150.4:
        pm25_aqi = 'Unhealthy'
    elif pm25 <= 250.4:
        pm25_aqi = 'Very Unhealthy'
    else:
        pm25_aqi = 'Hazardous'
    
    # PM10 breakpoints
    if pm10 <= 54:
        pm10_aqi = 'Good'
    elif pm10 <= 154:
        pm10_aqi = 'Moderate'
    elif pm10 <= 254:
        pm10_aqi = 'Unhealthy for Sensitive Groups'
    elif pm10 <= 354:
        pm10_aqi = 'Unhealthy'
    elif pm10 <= 424:
        pm10_aqi = 'Very Unhealthy'
    else:
        pm10_aqi = 'Hazardous'
    
    # Return the worse category
    categories = ['Good', 'Moderate', 'Unhealthy for Sensitive Groups', 
                 'Unhealthy', 'Very Unhealthy', 'Hazardous']
    
    pm25_idx = categories.index(pm25_aqi)
    pm10_idx = categories.index(pm10_aqi)
    
    return categories[max(pm25_idx, pm10_idx)]

def predict_alarm(data):
    """
    Predict if alarm should be triggered using ML model
    Falls back to rule-based if model not available
    """
    if model is None:
        # Rule-based fallback
        pm25 = data.get('pm25', 0)
        pm10 = data.get('pm10', 0)
        temp = data.get('temp', 20)
        
        if pm25 > 35 or pm10 > 50 or temp > 30 or temp < 18:
            return 1
        return 0
    
    try:
        # Prepare features for model
        features = pd.DataFrame([{
            'pm25': data.get('pm25', 0),
            'pm10': data.get('pm10', 0),
            'temp': data.get('temp', 0),
            'humidity': data.get('humidity', 0),
            'pressure': data.get('pressure', 0)
        }])
        
        # Scale features if scaler available
        if scaler is not None:
            features_scaled = scaler.transform(features)
        else:
            features_scaled = features.values
        
        # Predict
        prediction = model.predict(features_scaled)[0]
        probability = model.predict_proba(features_scaled)[0]
        
        return {
            'prediction': int(prediction),
            'probability': float(probability[1]),  # Probability of alarm
            'confidence': float(max(probability))
        }
    except Exception as e:
        logger.error(f"Prediction error: {e}")
        return {'prediction': 0, 'probability': 0, 'confidence': 0}

def log_data(data):
    """Save incoming sensor data to CSV file"""
    try:
        os.makedirs(os.path.dirname(DATA_LOG_PATH), exist_ok=True)
        
        df = pd.DataFrame([data])
        
        # Add timestamp if not present
        if 'datetime' not in df.columns:
            df['datetime'] = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        
        # Append to CSV
        if not os.path.exists(DATA_LOG_PATH):
            df.to_csv(DATA_LOG_PATH, index=False)
        else:
            df.to_csv(DATA_LOG_PATH, mode='a', header=False, index=False)
        
        logger.info(f"Data logged to {DATA_LOG_PATH}")
    except Exception as e:
        logger.error(f"Error logging data: {e}")

@app.route('/health', methods=['GET'])
def health_check():
    """Health check endpoint"""
    return jsonify({
        'status': 'healthy',
        'model_loaded': model is not None,
        'scaler_loaded': scaler is not None,
        'timestamp': datetime.now().isoformat()
    })

@app.route('/data', methods=['POST'])
def receive_data():
    """
    Receive sensor data from ESP32, make prediction, and return result
    """
    try:
        data = request.get_json()
        
        if not data:
            return jsonify({'error': 'No data received'}), 400
        
        logger.info(f"Received data: {data}")
        
        # Log the data
        log_data(data)
        
        # Get AQI category
        pm25 = data.get('pm25', 0)
        pm10 = data.get('pm10', 0)
        aqi_category = get_aqi_category(pm25, pm10)
        
        # Predict alarm status
        prediction_result = predict_alarm(data)
        
        # Prepare response
        if isinstance(prediction_result, dict):
            response = {
                'status': 'success',
                'timestamp': datetime.now().isoformat(),
                'aqi_category': aqi_category,
                'prediction': prediction_result['prediction'],
                'alarm': bool(prediction_result['prediction']),
                'confidence': prediction_result.get('confidence', 0),
                'probability': prediction_result.get('probability', 0),
                'input_data': data
            }
        else:
            response = {
                'status': 'success',
                'timestamp': datetime.now().isoformat(),
                'aqi_category': aqi_category,
                'prediction': prediction_result,
                'alarm': bool(prediction_result),
                'input_data': data
            }
        
        logger.info(f"Response: {response}")
        return jsonify(response), 200
        
    except Exception as e:
        logger.error(f"Error processing request: {e}")
        return jsonify({
            'status': 'error',
            'error': str(e),
            'timestamp': datetime.now().isoformat()
        }), 500

@app.route('/predict', methods=['POST'])
def predict():
    """
    Standalone prediction endpoint
    """
    try:
        data = request.get_json()
        
        if model is None:
            return jsonify({
                'error': 'Model not loaded',
                'status': 'error'
            }), 503
        
        prediction_result = predict_alarm(data)
        
        return jsonify({
            'status': 'success',
            'prediction': prediction_result,
            'timestamp': datetime.now().isoformat()
        }), 200
        
    except Exception as e:
        logger.error(f"Prediction error: {e}")
        return jsonify({
            'status': 'error',
            'error': str(e)
        }), 500

@app.route('/stats', methods=['GET'])
def get_stats():
    """
    Get statistics from logged data
    """
    try:
        if not os.path.exists(DATA_LOG_PATH):
            return jsonify({'error': 'No data logged yet'}), 404
        
        df = pd.read_csv(DATA_LOG_PATH)
        
        stats = {
            'total_records': len(df),
            'date_range': {
                'start': df['datetime'].min() if 'datetime' in df.columns else 'N/A',
                'end': df['datetime'].max() if 'datetime' in df.columns else 'N/A'
            },
            'averages': {
                'pm25': float(df['pm25'].mean()) if 'pm25' in df.columns else 0,
                'pm10': float(df['pm10'].mean()) if 'pm10' in df.columns else 0,
                'temp': float(df['temp'].mean()) if 'temp' in df.columns else 0,
                'humidity': float(df['humidity'].mean()) if 'humidity' in df.columns else 0,
                'pressure': float(df['pressure'].mean()) if 'pressure' in df.columns else 0
            },
            'alarm_count': int(df['alarm'].sum()) if 'alarm' in df.columns else 0
        }
        
        return jsonify(stats), 200
        
    except Exception as e:
        logger.error(f"Error getting stats: {e}")
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    # Load model on startup
    load_model()
    
    # Create necessary directories
    os.makedirs(os.path.dirname(MODEL_PATH), exist_ok=True)
    os.makedirs(os.path.dirname(DATA_LOG_PATH), exist_ok=True)
    
    # Start server
    logger.info("Starting ML Inference Server...")
    logger.info("Server running on http://0.0.0.0:5000")
    
    app.run(host='0.0.0.0', port=5000, debug=True)
