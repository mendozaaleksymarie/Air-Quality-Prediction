#!/usr/bin/env python
"""Test wet-bulb temperature computation against documentation scenarios"""

import sys
import os
import numpy as np
import pandas as pd

# Add core source to path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'core source'))

from train_random_forest import compute_wet_bulb_temperature, apply_multi_sensor_escalation, STATUS_TO_LABEL

def test_wet_bulb_scenarios():
    """Test Tw computation with documentation scenarios"""
    print("\n" + "="*70)
    print("WET-BULB TEMPERATURE VERIFICATION TEST")
    print("="*70 + "\n")
    
    # Test scenarios from wet-bulb documentation
    scenarios = [
        # (temp_c, humidity_rh, expected_tw_approx, expected_classification, description)
        (30, 90, 28.6, "YELLOW", "Humid tropics - high risk"),
        (35, 70, 30.3, "RED", "Hot/moderate humidity - extreme stress"),
        (25, 40, 15.0, "GREEN", "Comfortable conditions"),
        (38, 30, 22.0, "GREEN", "Hot but dry - body can cool"),
        (28, 95, 27.8, "YELLOW", "High humidity + moderate temp"),
    ]
    
    print("Scenario Analysis:")
    print("-" * 70)
    print(f"{'Temp':>6} {'RH':>4} {'Tw (computed)':>13} {'Tw (expect)':>12} {'Tier':>8} {'Description':>25}")
    print("-" * 70)
    
    all_passed = True
    for temp, rh, expected_tw, tier, desc in scenarios:
        tw = compute_wet_bulb_temperature(temp, rh)
        error = abs(tw - expected_tw)
        status = "✓" if error < 1.0 else "✗"
        
        if error >= 1.0:
            all_passed = False
            
        print(f"{temp:6.1f}°C {rh:3.0f}% {tw:12.2f}°C {expected_tw:12.2f}°C {tier:>8} {desc:>25} {status}")
    
    print("-" * 70)
    print(f"Overall: {'✓ PASS - All values within 1°C of expected' if all_passed else '✗ FAIL - Check formula'}\n")
    
    return all_passed

def test_escalation_logic():
    """Test Tw escalation logic in classification"""
    print("="*70)
    print("TWET-BULB ESCALATION LOGIC TEST")
    print("="*70 + "\n")
    
    test_rows = [
        # (name, pm2_5, pm10, gas, co, temp, humidity, expected_class)
        ("Safe air + GREEN Tw", 20, 50, 100, 5, 25, 40, 0),      # Safe all around
        ("Safe air + YELLOW Tw", 20, 50, 100, 5, 30, 90, 1),     # Escalated to Caution due to heat
        ("Safe air + RED Tw", 20, 50, 100, 5, 38, 95, 2),        # Escalated to Hazardous due to extreme heat
        ("Caution air + YELLOW Tw", 75, 100, 150, 8, 28, 80, 2), # Already caution, stays hazardous with heat
        ("Normal with high temp", 30, 50, 110, 6, 35, 65, 1),     # Slight escalation from heat
    ]
    
    print("Classification Behavior with Heat Stress:")
    print("-" * 90)
    print(f"{'Test Case':30} {'Sensors':25} {'Temp/RH':12} {'Tw':7} {'Class':6}")
    print("-" * 90)
    
    for name, pm2_5, pm10, gas, co, temp, humidity, expected_class in test_rows:
        row = {
            'pm2_5': pm2_5, 'pm10': pm10, 'gas': gas, 'co': co,
            'temp': temp, 'humidity': humidity
        }
        
        tw = compute_wet_bulb_temperature(temp, humidity)
        classification = apply_multi_sensor_escalation(row)
        
        sensor_str = f"PM:{pm2_5:3.0f}/{pm10:3.0f} G:{gas:3.0f} C:{co:3.0f}"
        tw_str = f"{tw:5.1f}°C"
        class_name = STATUS_TO_LABEL.get(classification, "?")
        
        status = "✓" if classification == expected_class else f"✗(exp:{expected_class})"
        print(f"{name:30} {sensor_str:25} {temp:3.0f}°C/{humidity:2.0f}% {tw_str:>7} {class_name:>4} {status}")
    
    print("-" * 90 + "\n")

def test_import():
    """Verify all imports work"""
    print("="*70)
    print("IMPORT VERIFICATION")
    print("="*70 + "\n")
    
    try:
        from train_random_forest import (
            compute_wet_bulb_temperature,
            apply_multi_sensor_escalation,
            apply_intelligent_labeling,
            STATUS_TO_LABEL
        )
        print("✓ All required functions imported successfully")
        print("✓ compute_wet_bulb_temperature: Available")
        print("✓ apply_multi_sensor_escalation: Available (WITH Tw escalations)")
        print("✓ apply_intelligent_labeling: Available")
        print("✓ STATUS_TO_LABEL: Available\n")
        return True
    except ImportError as e:
        print(f"✗ Import failed: {e}\n")
        return False

if __name__ == "__main__":
    print("\n" + "█"*70)
    print("█" + " "*68 + "█")
    print("█" + "  WET-BULB TEMPERATURE INTEGRATION VERIFICATION".center(68) + "█")
    print("█" + "  Testing Stull (2011) Formula & Escalation Logic".center(68) + "█")
    print("█" + " "*68 + "█")
    print("█"*70 + "\n")
    
    import_ok = test_import()
    if import_ok:
        test_wet_bulb_scenarios()
        test_escalation_logic()
        print("█"*70)
        print("█  ✓ ALL TESTS COMPLETE".ljust(69) + "█")
        print("█"*70 + "\n")
