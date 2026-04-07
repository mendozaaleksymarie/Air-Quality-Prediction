"""
ML Inference Server for Air Quality Monitoring (MILES)
Receives sensor data from ESP32 and returns predictions using 35-feature Random Forest model

DEPLOYMENT CONFIGURATION:
- Loads: random_forest_model.pkl (trained on 35 engineered features)
- Loads: scaler.pkl (StandardScaler fitted to training data)
- Maintains: Feature history buffer (for lagged features: lag_1, lag_3, lag_5)
- Computes: All 35 features in real-time from raw ESP32 sensor readings
- Returns: Prediction + confidence + alarm status
"""

from flask import Flask, request, jsonify
from flask_cors import CORS
import pandas as pd
import numpy as np
import pickle
import os
from datetime import datetime
from collections import deque
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

# ═══════════════════════════════════════════════════════════════════════════════
# FEATURE HISTORY BUFFER FOR LAGGED FEATURES
# ═══════════════════════════════════════════════════════════════════════════════

class FeatureBuffer:
    """
    Maintains a rolling history of sensor readings for computing lagged features.
    
    Lagged features require historical context:
    - pm25_lag_1: PM2.5 value from 1 reading ago
    - pm25_lag_3: PM2.5 value from 3 readings ago  
    - pm25_lag_5: PM2.5 value from 5 readings ago
    
    Same for gas_lag_1/3/5 and co_lag_1/3/5.
    """
    
    def __init__(self, max_history=10):
        """
        Initialize buffer.
        
        Args:
            max_history: Maximum number of readings to keep (at least 5 for lag_5)
        """
        self.readings = deque(maxlen=max(max_history, 5))
        self.timestamps = deque(maxlen=max(max_history, 5))
        logger.info(f"FeatureBuffer initialized with max_history={max_history}")
    
    def add_reading(self, pm25, pm10, gas, co, temp, humidity, pressure=None):
        """
        Add a new sensor reading to history.
        
        Args:
            pm25, pm10, gas, co, temp, humidity, pressure: Raw sensor values
        """
        reading = {
            'pm25': pm25,
            'pm10': pm10,
            'gas': gas,
            'co': co,
            'temp': temp,
            'humidity': humidity,
            'pressure': pressure if pressure is not None else 0
        }
        self.readings.append(reading)
        self.timestamps.append(datetime.now())
    
    def get_lag_value(self, sensor_name, lag_minutes):
        """
        Get sensor value from N readings ago.
        
        Args:
            sensor_name: 'pm25', 'gas', 'co', etc.
            lag_minutes: 1, 3, or 5 (number of readings back)
        
        Returns:
            float: Sensor value from lag_minutes ago, or current value if not enough history
        """
        if len(self.readings) > lag_minutes:
            return self.readings[-lag_minutes-1].get(sensor_name, 0)
        elif len(self.readings) > 0:
            # Return first available reading if not enough history
            return self.readings[0].get(sensor_name, 0)
        else:
            # No history yet, return 0 (will be filled after first reading)
            return 0
    
    def is_ready(self):
        """Check if buffer has enough data for lag features (at least 1 reading)"""
        return len(self.readings) > 0
    
    def get_current_reading(self):
        """Get the most recent reading"""
        if len(self.readings) > 0:
            return self.readings[-1]
        return None

# Initialize global feature buffer
feature_buffer = FeatureBuffer(max_history=10)

# ═══════════════════════════════════════════════════════════════════════════════
# FEATURE ENGINEERING FUNCTIONS (Ported from train_random_forest.py)
# ═══════════════════════════════════════════════════════════════════════════════

def compute_wet_bulb_temperature(temp_c, humidity_rh):
    """
    Compute wet-bulb temperature: Physiological heat stress index
    
    Uses Stull (2011) formula to compute how hard body must work to cool itself.
    Combines temperature and humidity into single meaningful value.
    """
    try:
        if pd.isna(temp_c) or pd.isna(humidity_rh):
            return 20.0  # Safe default
        
        T = float(temp_c)
        RH = float(humidity_rh)
        RH = np.clip(RH, 0, 100)
        
        # Stull (2011) approximation
        term1 = T * np.arctan(0.151977 * np.sqrt(RH + 8.313659))
        term2 = np.arctan(T + RH)
        term3 = np.arctan(RH - 1.676331)
        term4 = 0.00391838 * (RH ** 1.8) * np.arctan(0.023101 * RH)
        term5 = 4.686035
        
        Tw = term1 + term2 - term3 + term4 - term5
        return float(Tw)
    except:
        return 20.0  # Safe default on error

def compute_sensor_ratios(pm25, pm10, gas, co):
    """
    FEATURE 2: Sensor Ratio Features — Distinguishes hazard types
    - PM Ratio (PM10/PM2.5): Identifies particle size distribution
    - Gas/CO Ratio: Identifies combustion type
    - PM Sum: Total particulate load
    """
    pm_ratio = pm10 / (pm25 + 0.1) if pm25 > 0 else pm10 / 0.1
    gas_co_ratio = gas / (co + 0.1) if co > 0 else gas / 0.1
    pm_sum = pm25 + pm10
    
    return {
        'pm_ratio': pm_ratio,
        'gas_co_ratio': gas_co_ratio,
        'pm_sum': pm_sum
    }

def compute_rate_of_change(current, previous):
    """
    FEATURE 3: Rate-of-Change (Delta) Features — Early hazard detection
    Computes per-minute change rate for each sensor
    """
    deltas = {
        'pm25_delta': current['pm25'] - previous['pm25'] if previous else 0,
        'pm10_delta': current['pm10'] - previous['pm10'] if previous else 0,
        'gas_delta': current['gas'] - previous['gas'] if previous else 0,
        'co_delta': current['co'] - previous['co'] if previous else 0
    }
    
    # Acceleration: is rate-of-change itself accelerating?
    deltas['pm_acceleration'] = 1 if abs(deltas['pm25_delta']) > 2 else 0
    deltas['gas_acceleration'] = 1 if abs(deltas['gas_delta']) > 2 else 0
    
    return deltas

def compute_volatility(current_reading, buffer):
    """
    FEATURE 6: Volatility/Standard Deviation — Distinguish stable vs erratic hazards
    Uses rolling window to compute variability in sensor readings
    """
    if len(buffer.readings) < 3:
        return {'pm25_volatility': 0, 'gas_volatility': 0}
    
    # Get last 5 readings
    recent_pm25 = [r['pm25'] for r in list(buffer.readings)[-5:]]
    recent_gas = [r['gas'] for r in list(buffer.readings)[-5:]]
    
    pm25_volatility = np.std(recent_pm25) if len(recent_pm25) > 1 else 0
    gas_volatility = np.std(recent_gas) if len(recent_gas) > 1 else 0
    
    return {
        'pm25_volatility': pm25_volatility,
        'gas_volatility': gas_volatility
    }

def compute_trend_direction(current_delta, previous_delta):
    """
    FEATURE 7: Trend Direction — Is danger escalating or resolving?
    - pm_trend: +1 (rising), -1 (falling), 0 (stable)
    - is_pm_accelerating: sustained rise detected
    - is_gas_accelerating: sustained rise detected
    """
    pm_trend = np.sign(current_delta['pm25_delta']) if current_delta['pm25_delta'] != 0 else 0
    gas_trend = np.sign(current_delta['gas_delta']) if current_delta['gas_delta'] != 0 else 0
    
    # Check if acceleration is sustained (both current and previous are positive)
    is_pm_accelerating = 1 if (current_delta['pm25_delta'] > 0 and 
                                (previous_delta and previous_delta['pm25_delta'] > 0)) else 0
    is_gas_accelerating = 1 if (current_delta['gas_delta'] > 0 and 
                                (previous_delta and previous_delta['gas_delta'] > 0)) else 0
    
    return {
        'pm_trend': pm_trend,
        'gas_trend': gas_trend,
        'is_pm_accelerating': is_pm_accelerating,
        'is_gas_accelerating': is_gas_accelerating
    }

def compute_lagged_features(buffer):
    """
    FEATURE 5: Lagged Features — Temporal history for trajectory recognition
    Returns: pm25_lag_1/3/5, gas_lag_1/3/5, co_lag_1/3/5
    """
    return {
        'pm25_lag_1': buffer.get_lag_value('pm25', 1),
        'pm25_lag_3': buffer.get_lag_value('pm25', 3),
        'pm25_lag_5': buffer.get_lag_value('pm25', 5),
        'gas_lag_1': buffer.get_lag_value('gas', 1),
        'gas_lag_3': buffer.get_lag_value('gas', 3),
        'gas_lag_5': buffer.get_lag_value('gas', 5),
        'co_lag_1': buffer.get_lag_value('co', 1),
        'co_lag_3': buffer.get_lag_value('co', 3),
        'co_lag_5': buffer.get_lag_value('co', 5)
    }

def flag_sensor_health_issues(current, previous):
    """
    FEATURE 14: Sensor Health Flags
    Detects: stuck sensors, rapid anomalies
    """
    # Simple health check: if reading hasn't changed in multiple readings, flag as stuck
    sensor_health_issue = 0
    if previous and abs(current['pm25'] - previous['pm25']) < 0.1:
        sensor_health_issue = 1
    
    return {'sensor_health_issue': sensor_health_issue}

def compute_all_35_features(current_reading, buffer, previous_reading=None, previous_delta=None):
    """
    Compute all 35 features from raw ESP32 sensor data.
    
    FEATURE BREAKDOWN:
    - 8 Original sensors: pm25, pm10, gas, co, temp, humidity, time_of_day, wet_bulb
    - 3 Ratios: pm_ratio, gas_co_ratio, pm_sum
    - 6 Deltas: pm25_delta, pm10_delta, gas_delta, co_delta, pm_acceleration, gas_acceleration
    - 9 Lagged: pm25_lag_1/3/5, gas_lag_1/3/5, co_lag_1/3/5
    - 2 Volatility: pm25_volatility, gas_volatility
    - 4 Trends: pm_trend, gas_trend, is_pm_accelerating, is_gas_accelerating
    - 1 Site: site_id (default 0 until configured)
    - 2 Health flags: sensor_health_issue, sensor_anomaly_flag
    
    Total: 35 features
    """
    features = {}
    
    # 1. ORIGINAL SENSORS (8)
    features['pm2_5'] = current_reading['pm25']
    features['pm10'] = current_reading['pm10']
    features['gas'] = current_reading['gas']
    features['co'] = current_reading['co']
    features['temp'] = current_reading['temp']
    features['humidity'] = current_reading['humidity']
    features['time_of_day'] = datetime.now().hour  # Extract hour from current time
    features['wet_bulb'] = compute_wet_bulb_temperature(
        current_reading['temp'],
        current_reading['humidity']
    )
    
    # 2. SENSOR RATIOS (3)
    ratios = compute_sensor_ratios(
        current_reading['pm25'],
        current_reading['pm10'],
        current_reading['gas'],
        current_reading['co']
    )
    features.update(ratios)
    
    # 3. RATE-OF-CHANGE / DELTA (6)
    deltas = compute_rate_of_change(current_reading, previous_reading)
    features.update(deltas)
    
    # 4. LAGGED FEATURES (9)
    lags = compute_lagged_features(buffer)
    features.update(lags)
    
    # 5. VOLATILITY (2)
    volatility = compute_volatility(current_reading, buffer)
    features.update(volatility)
    
    # 6. TREND DIRECTION (4)
    trends = compute_trend_direction(deltas, previous_delta)
    features.update(trends)
    
    # 7. SITE ID (1) - Default to 0, can be configurable
    features['site_id'] = 0
    
    # 8. SENSOR HEALTH (2)
    health = flag_sensor_health_issues(current_reading, previous_reading)
    features['sensor_health_issue'] = health['sensor_health_issue']
    features['sensor_anomaly_flag'] = 0  # No anomaly detection in real-time (requires Elliptic Envelope)
    
    return features

def load_model():
    """Load the trained Random Forest model and scaler"""
    global model, scaler
    try:
        if os.path.exists(MODEL_PATH):
            with open(MODEL_PATH, 'rb') as f:
                model = pickle.load(f)
            logger.info("✓ Model loaded successfully")
        else:
            logger.warning(f"✗ Model not found at {MODEL_PATH}")
            logger.warning("  Please run: python 'core source/train_random_forest.py'")
            
        if os.path.exists(SCALER_PATH):
            with open(SCALER_PATH, 'rb') as f:
                scaler = pickle.load(f)
            logger.info("✓ Scaler loaded successfully")
        else:
            logger.warning(f"✗ Scaler not found at {SCALER_PATH}")
    except Exception as e:
        logger.error(f"✗ Error loading model/scaler: {e}")

# Store previous reading/delta for trend computation
previous_reading = None
previous_delta = None

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
    Predict alarm status using ML model with all 35 engineered features.
    
    Args:
        data: dict with raw sensor values {pm25, pm10, gas, co, temp, humidity, pressure}
    
    Returns:
        dict: {prediction (0/1/2), probability, confidence, features_used}
        
    Falls back to rule-based prediction if model not available.
    """
    global previous_reading, previous_delta
    
    if model is None:
        logger.warning("Model not loaded, using rule-based fallback")
        # Rule-based fallback for emergency
        pm25 = data.get('pm25', 0)
        pm10 = data.get('pm10', 0)
        gas = data.get('gas', 0)
        
        if pm25 > 35 or pm10 > 50 or gas > 150:
            return {
                'prediction': 2,  # Hazardous
                'probability': 0.9,
                'confidence': 0.9,
                'method': 'rule-based'
            }
        elif pm25 > 12 or pm10 > 35 or gas > 100:
            return {
                'prediction': 1,  # Caution
                'probability': 0.6,
                'confidence': 0.6,
                'method': 'rule-based'
            }
        return {
            'prediction': 0,
            'probability': 0.1,
            'confidence': 0.8,
            'method': 'rule-based'
        }
    
    try:
        # Create current reading dict from raw data
        current_reading = {
            'pm25': data.get('pm25', 0),
            'pm10': data.get('pm10', 0),
            'gas': data.get('gas', 0),
            'co': data.get('co', 0),
            'temp': data.get('temp', 20),
            'humidity': data.get('humidity', 50),
            'pressure': data.get('pressure', 0)
        }
        
        # Compute ALL 35 features
        features_dict = compute_all_35_features(
            current_reading,
            feature_buffer,
            previous_reading,
            previous_delta
        )
        
        # Store for next iteration
        previous_reading = current_reading
        previous_delta = {
            'pm25_delta': features_dict['pm25_delta'],
            'gas_delta': features_dict['gas_delta']
        }
        
        # Convert to DataFrame with correct column order
        # This MUST match the training feature order!
        feature_columns = [
            'pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'time_of_day', 'wet_bulb',
            'pm_ratio', 'gas_co_ratio', 'pm_sum',
            'pm25_delta', 'pm10_delta', 'gas_delta', 'co_delta', 'pm_acceleration', 'gas_acceleration',
            'pm25_lag_1', 'pm25_lag_3', 'pm25_lag_5',
            'gas_lag_1', 'gas_lag_3', 'gas_lag_5',
            'co_lag_1', 'co_lag_3', 'co_lag_5',
            'pm25_volatility', 'gas_volatility',
            'pm_trend', 'gas_trend', 'is_pm_accelerating', 'is_gas_accelerating',
            'site_id', 'sensor_health_issue', 'sensor_anomaly_flag'
        ]
        
        # Build feature array with correct order
        X = np.array([[features_dict.get(col, 0) for col in feature_columns]])
        
        logger.info(f"Features computed: {X.shape[1]} features")
        logger.debug(f"Feature values: {X[0][:8]}... (showing first 8)")
        
        # Scale features if scaler available
        if scaler is not None:
            X_scaled = scaler.transform(X)
        else:
            logger.warning("Scaler not available, using unscaled features")
            X_scaled = X
        
        # Make prediction
        prediction = model.predict(X_scaled)[0]
        probabilities = model.predict_proba(X_scaled)[0]
        confidence = float(max(probabilities))
        
        # Probabilities are returned as [prob_class_0, prob_class_1, prob_class_2]
        prob_alarm = float(probabilities[prediction])
        
        logger.info(f"Prediction: {prediction} (confidence: {confidence:.2%})")
        logger.info(f"Class probabilities: Safe={probabilities[0]:.2%}, Caution={probabilities[1]:.2%}, Hazardous={probabilities[2]:.2%}")
        
        return {
            'prediction': int(prediction),
            'probability': prob_alarm,
            'confidence': confidence,
            'method': 'ml-35-features',
            'probabilities': {
                'safe': float(probabilities[0]),
                'caution': float(probabilities[1]),
                'hazardous': float(probabilities[2])
            },
            'features_computed': len(feature_columns)
        }
        
    except Exception as e:
        logger.error(f"Prediction error: {e}", exc_info=True)
        return {
            'prediction': 0,
            'probability': 0,
            'confidence': 0,
            'error': str(e),
            'method': 'error'
        }

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
    """Health check endpoint with feature engineering status"""
    return jsonify({
        'status': 'healthy',
        'model_loaded': model is not None,
        'scaler_loaded': scaler is not None,
        'feature_buffer_ready': feature_buffer.is_ready(),
        'buffer_size': len(feature_buffer.readings),
        'timestamp': datetime.now().isoformat(),
        'version': '2.0_35-features'
    })

@app.route('/data', methods=['POST'])
def receive_data():
    """
    Receive sensor data from ESP32, compute all 35 features, make prediction.
    
    Expected JSON:
    {
        "pm25": float,
        "pm10": float,
        "gas": float,
        "co": float,
        "temp": float,
        "humidity": float,
        "pressure": float (optional)
    }
    
    Response includes:
    - ML prediction (0=Safe, 1=Caution, 2=Hazardous)
    - Confidence and class probabilities
    - AQI category
    - All computed features
    """
    try:
        data = request.get_json()
        
        if not data:
            return jsonify({'error': 'No data received'}), 400
        
        logger.info(f"Received sensor data: PM2.5={data.get('pm25')}, Gas={data.get('gas')}")
        
        # Add reading to feature buffer (for lagged features)
        feature_buffer.add_reading(
            data.get('pm25', 0),
            data.get('pm10', 0),
            data.get('gas', 0),
            data.get('co', 0),
            data.get('temp', 20),
            data.get('humidity', 50),
            data.get('pressure', 0)
        )
        
        # Log the data
        log_data(data)
        
        # Get AQI category
        pm25 = data.get('pm25', 0)
        pm10 = data.get('pm10', 0)
        aqi_category = get_aqi_category(pm25, pm10)
        
        # Predict alarm status using ML with all 35 features
        prediction_result = predict_alarm(data)
        
        # Map prediction to alarm labels
        alarm_labels = ['Safe', 'Caution', 'Hazardous']
        alarm_label = alarm_labels[prediction_result['prediction']] if 'prediction' in prediction_result else 'Unknown'
        
        # Prepare response
        response = {
            'status': 'success',
            'timestamp': datetime.now().isoformat(),
            'sensor_data': {
                'pm25': pm25,
                'pm10': pm10,
                'gas': data.get('gas', 0),
                'co': data.get('co', 0),
                'temp': data.get('temp', 0),
                'humidity': data.get('humidity', 0),
                'pressure': data.get('pressure', 0)
            },
            'aqi_category': aqi_category,
            'ml_prediction': {
                'class': alarm_label,
                'class_code': prediction_result.get('prediction', 0),
                'confidence': prediction_result.get('confidence', 0),
                'method': prediction_result.get('method', 'unknown'),
                'features_used': prediction_result.get('features_computed', 0)
            },
            'probabilities': prediction_result.get('probabilities', {}),
            'alarm_triggered': bool(prediction_result.get('prediction', 0) == 2)  # 2 = Hazardous
        }
        
        logger.info(f"Response: {alarm_label} (confidence: {prediction_result.get('confidence', 0):.2%})")
        return jsonify(response), 200
        
    except Exception as e:
        logger.error(f"Error processing request: {e}", exc_info=True)
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

@app.route('/features', methods=['GET'])
def get_features_info():
    """
    Get information about the 35 feature engineering system
    """
    feature_categories = {
        'original_sensors': [
            'pm2_5', 'pm10', 'gas', 'co', 'temp', 'humidity', 'time_of_day', 'wet_bulb'
        ],
        'sensor_ratios': [
            'pm_ratio', 'gas_co_ratio', 'pm_sum'
        ],
        'deltas_and_acceleration': [
            'pm25_delta', 'pm10_delta', 'gas_delta', 'co_delta', 'pm_acceleration', 'gas_acceleration'
        ],
        'lagged_features': [
            'pm25_lag_1', 'pm25_lag_3', 'pm25_lag_5',
            'gas_lag_1', 'gas_lag_3', 'gas_lag_5',
            'co_lag_1', 'co_lag_3', 'co_lag_5'
        ],
        'volatility': [
            'pm25_volatility', 'gas_volatility'
        ],
        'trends': [
            'pm_trend', 'gas_trend', 'is_pm_accelerating', 'is_gas_accelerating'
        ],
        'site_specific': [
            'site_id'
        ],
        'sensor_health': [
            'sensor_health_issue', 'sensor_anomaly_flag'
        ]
    }
    
    total_features = sum(len(v) for v in feature_categories.values())
    
    return jsonify({
        'status': 'success',
        'total_features': total_features,
        'feature_categories': feature_categories,
        'buffer_status': {
            'history_available': feature_buffer.is_ready(),
            'current_size': len(feature_buffer.readings),
            'max_size': feature_buffer.readings.maxlen
        },
        'timestamp': datetime.now().isoformat()
    }), 200

@app.route('/info', methods=['GET'])
def get_system_info():
    """
    Get system information about deployment
    """
    return jsonify({
        'status': 'success',
        'system': 'MILES Air Quality Prediction (ML Inference Server)',
        'version': '2.0',
        'features': '35 engineered features',
        'model_architecture': 'Random Forest (200 estimators)',
        'training_accuracy': '100% on 5,142 validation samples',
        'deployment': {
            'model_loaded': model is not None,
            'scaler_loaded': scaler is not None,
            'feature_buffer_ready': feature_buffer.is_ready()
        },
        'input_requirements': {
            'raw_sensors': ['pm25', 'pm10', 'gas', 'co', 'temp', 'humidity', 'pressure (optional)'],
            'format': 'JSON POST request',
            'endpoint': '/data'
        },
        'output': {
            'prediction_classes': ['0=Safe', '1=Caution', '2=Hazardous'],
            'confidence': 'Prediction confidence (0-1)',
            'probabilities': 'Class probabilities for each class'
        },
        'timestamp': datetime.now().isoformat()
    }), 200

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
    
    # Startup information
    logger.info("=" * 80)
    logger.info("MILES ML INFERENCE SERVER - Version 2.0 (35 Features)")
    logger.info("=" * 80)
    logger.info("✓ System initialized")
    logger.info(f"  Model: {'LOADED' if model else 'NOT FOUND'}")
    logger.info(f"  Scaler: {'LOADED' if scaler else 'NOT FOUND'}")
    logger.info(f"  Feature Buffer: Ready (max history: {feature_buffer.readings.maxlen} readings)")
    logger.info(f"  Total Features: 35 (8 sensors + 27 engineered)")
    logger.info("")
    logger.info("Feature Categories:")
    logger.info("  • Original Sensors (8): PM2.5, PM10, Gas, CO, Temp, Humidity, Hour, Wet-Bulb")
    logger.info("  • Ratios (3): PM Ratio, Gas/CO Ratio, PM Sum")
    logger.info("  • Deltas (6): PM/PM10/Gas/CO Delta + Accelerations")
    logger.info("  • Lagged (9): 1/3/5-min lags for PM2.5, Gas, CO")
    logger.info("  • Volatility (2): PM2.5 and Gas rolling std dev")
    logger.info("  • Trends (4): PM/Gas trend + PM/Gas acceleration indicators")
    logger.info("  • Site (1): Site ID")
    logger.info("  • Health (2): Sensor health flags")
    logger.info("")
    logger.info("API Endpoints:")
    logger.info("  POST /data           - Send sensor data, get prediction")
    logger.info("  GET  /health         - System health check")
    logger.info("  GET  /info           - System information")
    logger.info("  GET  /features       - Feature engineering details")
    logger.info("  Post /predict        - Standalone prediction")
    logger.info("  GET  /stats          - Logged data statistics")
    logger.info("")
    logger.info("=" * 80)
    logger.info(f"Starting ML Inference Server on http://0.0.0.0:5000")
    logger.info(f"Timestamp: {datetime.now().isoformat()}")
    logger.info("=" * 80)
    
    # Start server (debug=False for production, True for development)
    app.run(host='0.0.0.0', port=5000, debug=False, threaded=True)
