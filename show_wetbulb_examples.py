import pandas as pd
import numpy as np
import sys
sys.path.insert(0, './core source')
from train_random_forest import compute_wet_bulb_temperature

# Load dataset
df = pd.read_csv('dataset/combined_data.csv')

# Calculate wet-bulb for all rows
df['wet_bulb'] = df.apply(lambda row: compute_wet_bulb_temperature(row['temp'], row['humidity']), axis=1)

print("="*120)
print("SAFE CLASS (0) - Examples with Wet-Bulb Temperature")
print("="*120)
safe_examples = df[df['alarm_status'] == 0].head(3)
for idx, (i, row) in enumerate(safe_examples.iterrows(), 1):
    print(f"\nExample {idx}: {row['source_file']}")
    print(f"  PM2.5: {row['pm2_5']:7.1f} μg/m³ | PM10: {row['pm10']:7.1f} μg/m³ | Gas: {row['gas']:6.1f} ppm | CO: {row['co']:5.1f} ppm")
    print(f"  Temp: {row['temp']:5.1f}°C | Humidity: {row['humidity']:5.1f}% | Wet-Bulb: {row['wet_bulb']:5.2f}°C")
    print(f"  Status: SAFE ✅")

print("\n" + "="*120)
print("CAUTION CLASS (1) - Examples with Wet-Bulb Temperature")
print("="*120)
caution_examples = df[df['alarm_status'] == 1].head(3)
for idx, (i, row) in enumerate(caution_examples.iterrows(), 1):
    print(f"\nExample {idx}: {row['source_file']}")
    print(f"  PM2.5: {row['pm2_5']:7.1f} μg/m³ | PM10: {row['pm10']:7.1f} μg/m³ | Gas: {row['gas']:6.1f} ppm | CO: {row['co']:5.1f} ppm")
    print(f"  Temp: {row['temp']:5.1f}°C | Humidity: {row['humidity']:5.1f}% | Wet-Bulb: {row['wet_bulb']:5.2f}°C")
    print(f"  Status: CAUTION ⚠️")

print("\n" + "="*120)
print("HAZARDOUS CLASS (2) - Examples with Wet-Bulb Temperature")
print("="*120)
hazard_examples = df[df['alarm_status'] == 2].head(3)
for idx, (i, row) in enumerate(hazard_examples.iterrows(), 1):
    print(f"\nExample {idx}: {row['source_file']}")
    print(f"  PM2.5: {row['pm2_5']:7.1f} μg/m³ | PM10: {row['pm10']:7.1f} μg/m³ | Gas: {row['gas']:6.1f} ppm | CO: {row['co']:5.1f} ppm")
    print(f"  Temp: {row['temp']:5.1f}°C | Humidity: {row['humidity']:5.1f}% | Wet-Bulb: {row['wet_bulb']:5.2f}°C")
    print(f"  Status: HAZARDOUS ❌")

print("\n" + "="*120)
print("WET-BULB STATISTICS BY CLASS")
print("="*120)
for cls in [0, 1, 2]:
    class_name = ['SAFE', 'CAUTION', 'HAZARDOUS'][cls]
    class_data = df[df['alarm_status'] == cls]['wet_bulb']
    print(f"\n{class_name} (Class {cls}):")
    print(f"  Mean: {class_data.mean():.2f}°C | Min: {class_data.min():.2f}°C | Max: {class_data.max():.2f}°C | Std: {class_data.std():.2f}°C")
    red_count = (class_data > 30).sum()
    yellow_count = ((class_data >= 27) & (class_data <= 30)).sum()
    green_count = (class_data <= 26).sum()
    print(f"  🔴 Tw > 30°C (RED): {red_count} ({100*red_count/len(class_data):.1f}%)")
    print(f"  🟡 Tw 27-30°C (YELLOW): {yellow_count} ({100*yellow_count/len(class_data):.1f}%)")
    print(f"  🟢 Tw ≤ 26°C (GREEN): {green_count} ({100*green_count/len(class_data):.1f}%)")
