#!/usr/bin/env python3
"""Quick retrain script: single-threaded RandomForest saving model+scaler

Uses SourceFileLoader to import functions from the existing training script
without executing its `main()` (loads as module). Trains a smaller RF
without GridSearch to avoid long runs and parallel crashes.
"""
import os
import pickle
from importlib.machinery import SourceFileLoader

# Load training module from 'core source/train_random_forest.py'
TRAIN_MODULE_PATH = os.path.join(os.path.dirname(__file__), 'core source', 'train_random_forest.py')
train_mod = SourceFileLoader('train_mod', TRAIN_MODULE_PATH).load_module()

def main():
    print("Quick retrain: loading and preprocessing data...")
    df = train_mod.load_data()
    df_processed, X, y, feature_names, outliers = train_mod.preprocess_data(df)

    # Train a single RandomForestClassifier (faster, single-threaded)
    from sklearn.ensemble import RandomForestClassifier
    from sklearn.preprocessing import StandardScaler
    from sklearn.model_selection import train_test_split

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=42, stratify=y)

    scaler = StandardScaler()
    X_train_scaled = scaler.fit_transform(X_train)

    print("Training RandomForest (n_estimators=100, n_jobs=1, class_weight='balanced')...")
    rf = RandomForestClassifier(n_estimators=100, random_state=42, n_jobs=1, class_weight='balanced')
    rf.fit(X_train_scaled, y_train)

    # Save scaler and model
    models_dir = os.path.join(os.path.dirname(__file__), 'models')
    os.makedirs(models_dir, exist_ok=True)
    model_path = os.path.join(models_dir, 'random_forest_model.pkl')
    scaler_path = os.path.join(models_dir, 'scaler.pkl')

    with open(model_path, 'wb') as f:
        pickle.dump(rf, f)
    with open(scaler_path, 'wb') as f:
        pickle.dump(scaler, f)

    print(f"Saved model to: {model_path}")
    print(f"Saved scaler to: {scaler_path}")

if __name__ == '__main__':
    main()
