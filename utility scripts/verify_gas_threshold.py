import pandas as pd

df = pd.read_csv('dataset/combined_data.csv')

print('=' * 60)
print('GAS THRESHOLD VERIFICATION')
print('=' * 60)
print('\nDefined Thresholds:')
print('  Safe:    100-250 (no alarm)')
print('  Caution: 250-400 (no alarm)')
print('  Hazard:  >400    (ALARM TRIGGERED)')
print('\nCode Implementation: Alarm when gas > 400')

print('\n' + '=' * 60)
print('DATA ANALYSIS')
print('=' * 60)

# Categorize gas readings
safe = df[df['gas'] <= 250]
caution = df[(df['gas'] > 250) & (df['gas'] <= 400)]
hazard = df[df['gas'] > 400]

print(f'\n📊 Gas Level Distribution:')
print(f'  Safe (≤250):      {len(safe):3d} records ({len(safe)/len(df)*100:.1f}%)')
print(f'  Caution (250-400): {len(caution):3d} records ({len(caution)/len(df)*100:.1f}%)')
print(f'  Hazard (>400):     {len(hazard):3d} records ({len(hazard)/len(df)*100:.1f}%)')

print(f'\n⚠️  Alarms in Each Category:')
print(f'  Safe range:    {safe["alarm_status"].sum()}/{len(safe)} alarms (from other sensors)')
print(f'  Caution range: {caution["alarm_status"].sum()}/{len(caution)} alarms (from other sensors)')
print(f'  Hazard range:  {hazard["alarm_status"].sum()}/{len(hazard)} alarms')

print('\n' + '=' * 60)
print('HAZARD LEVEL GAS READINGS (>400)')
print('=' * 60)
if len(hazard) > 0:
    print(hazard[['created_at', 'gas', 'co', 'temp', 'pm2_5', 'alarm_status']])
else:
    print('✓ No hazard-level gas readings found')

print('\n' + '=' * 60)
print('CAUTION LEVEL GAS READINGS (250-400)')
print('=' * 60)
if len(caution) > 0:
    print(caution[['created_at', 'gas', 'co', 'temp', 'pm2_5', 'alarm_status']])
else:
    print('✓ No caution-level gas readings found')

print('\n' + '=' * 60)
print('VERIFICATION RESULTS')
print('=' * 60)

# Check if all hazard gas levels trigger alarm
hazard_with_alarm = df[(df['gas'] > 400) & (df['alarm_status'] == 1)]
hazard_no_alarm = df[(df['gas'] > 400) & (df['alarm_status'] == 0)]

print(f'\nGas >400 with alarm:    {len(hazard_with_alarm)}/{len(hazard)} records')
print(f'Gas >400 without alarm: {len(hazard_no_alarm)}/{len(hazard)} records')

# Check if caution/safe levels incorrectly trigger alarm due to gas alone
caution_alarm_only_gas = caution[
    (caution['alarm_status'] == 1) & 
    (caution['pm2_5'] <= 100) & 
    (caution['pm10'] <= 230) & 
    (caution['temp'] <= 35) & 
    (caution['humidity'] <= 70) & 
    (caution['co'] <= 30)
]

if len(caution_alarm_only_gas) > 0:
    print(f'\n❌ ISSUE: {len(caution_alarm_only_gas)} caution-level gas readings triggered alarm')
    print('   (when other sensors are normal)')
else:
    print('\n✓ Caution range (250-400) correctly does NOT trigger alarm by itself')

if len(hazard) == len(hazard_with_alarm):
    print('✓ All hazard-level gas readings (>400) correctly trigger alarms')
else:
    print(f'⚠️  {len(hazard_no_alarm)} hazard readings did not trigger alarm')
    print('   (possibly overridden by other logic)')

print(f'\n{"✓" if len(hazard_with_alarm) > 0 else "⚠️"} Threshold implementation: {"CORRECT" if len(hazard_with_alarm) > 0 else "NEEDS REVIEW"}')
print('=' * 60)
