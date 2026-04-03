import pandas as pd

df = pd.read_csv('dataset/combined_data.csv')

print('='*70)
print('DATA RANGE FOR ALL CATEGORIES IN DATASET')
print('='*70)

print(f'\n📊 Total Records: {len(df)} readings')
print(f'📅 Date Range: {df["created_at"].min()} to {df["created_at"].max()}')

print('\n' + '='*70)
print('PARAMETER RANGES WITH UNITS')
print('='*70)

print(f'\n1. PM2.5 (Particulate Matter 2.5)')
print(f'   Range: {df["pm2_5"].min():.1f} - {df["pm2_5"].max():.1f} μg/m³')
print(f'   Mean:  {df["pm2_5"].mean():.1f} μg/m³')
print(f'   Unit:  Micrograms per cubic meter (μg/m³)')

print(f'\n2. PM10 (Particulate Matter 10)')
print(f'   Range: {df["pm10"].min():.1f} - {df["pm10"].max():.1f} μg/m³')
print(f'   Mean:  {df["pm10"].mean():.1f} μg/m³')
print(f'   Unit:  Micrograms per cubic meter (μg/m³)')

print(f'\n3. Temperature')
print(f'   Range: {df["temp"].min():.1f} - {df["temp"].max():.1f} °C')
print(f'   Mean:  {df["temp"].mean():.1f} °C')
print(f'   Unit:  Degrees Celsius (°C)')

print(f'\n4. Humidity')
print(f'   Range: {df["humidity"].min():.1f} - {df["humidity"].max():.1f} %')
print(f'   Mean:  {df["humidity"].mean():.1f} %')
print(f'   Unit:  Percentage (%)')

print(f'\n5. Gas (MQ-2 Sensor)')
print(f'   Range: {df["gas"].min():.1f} - {df["gas"].max():.1f} ADC')
print(f'   Mean:  {df["gas"].mean():.1f} ADC')
print(f'   Unit:  Analog-to-Digital Converter value (0-1023)')
print(f'   Levels:')
print(f'     - Safe:    100-250 ADC')
print(f'     - Caution: 250-400 ADC')
print(f'     - Hazard:  >400 ADC')

print(f'\n6. Carbon Monoxide (CO - MQ-7 Sensor)')
print(f'   Range: {df["co"].min():.1f} - {df["co"].max():.1f} ADC')
print(f'   Mean:  {df["co"].mean():.1f} ADC')
print(f'   Unit:  Analog-to-Digital Converter value (0-1023)')

print(f'\n7. Alarm Status')
print(f'   Values: 0 (No Alarm) or 1 (Alarm Triggered)')
print(f'   No Alarm: {(df["alarm_status"]==0).sum()} records ({(df["alarm_status"]==0).sum()/len(df)*100:.1f}%)')
print(f'   Alarm ON: {(df["alarm_status"]==1).sum()} records ({(df["alarm_status"]==1).sum()/len(df)*100:.1f}%)')
print(f'   Unit:  Binary (0/1)')

print('\n' + '='*70)
print('THRESHOLD SUMMARY')
print('='*70)
print('\nAlarm Triggers (Hazardous Levels):')
print('  • PM2.5 > 100 μg/m³ (DENR Ambient Air Quality Guideline)')
print('  • PM10 > 230 μg/m³ (RA 8749 IRR)')
print('  • Temperature > 35 °C (DOLE OSHS Heat Stress)')
print('  • Humidity > 70 % (DOLE OSHS)')
print('  • Gas (MQ-2) ≥ 176 ppm (NIOSH/OSHA PEL - Smoke/Combustible Gases)')
print('  • CO (MQ-7) > 30 ppm (RA 8749 IRR)')
print('='*70)
