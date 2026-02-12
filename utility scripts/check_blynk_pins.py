"""
Quick test to show exact values being sent to each Blynk virtual pin
"""

def adc_to_ppm(adc_value):
    """Convert gas sensor ADC value to ppm"""
    adc_value = max(0, min(1023, adc_value))
    ppm = (adc_value / 1023.0) * 10000
    return round(ppm, 1)

print("="*60)
print("BLYNK VIRTUAL PIN MAPPING")
print("="*60)

print("\nWhat each Virtual Pin receives:")
print(f"  V0 = PM2.5:       25.5 μg/m³")
print(f"  V1 = PM10:        40.2 μg/m³")
print(f"  V2 = Temperature: 24.8 °C")
print(f"  V3 = Humidity:    55.3 %")
print(f"  V4 = Gas:         {adc_to_ppm(220)} ppm  ← GAS IS HERE")
print(f"  V5 = Alarm:       0 (OFF)")

print("\n" + "="*60)
print("CHECK YOUR BLYNK APP CONFIGURATION")
print("="*60)
print("\nMake sure in your Blynk app:")
print("  • Gas widget is assigned to V4 (NOT V3)")
print("  • Humidity widget is assigned to V3")
print("\nIf you see 55.3 in gas:")
print("  → Your gas widget is using V3 instead of V4")
print("  → Change gas widget to Virtual Pin V4")
print("="*60)
