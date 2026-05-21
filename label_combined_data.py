import pandas as pd

# Load the data
df = pd.read_csv('dataset/combined_data.csv')

# Define thresholds based on the table provided
pm25_hazard = 100
pm25_caution = 51
pm10_hazard = 230
pm10_caution = 151
mqgas_hazard = 176
mqgas_caution = 131
mqco_hazard = 30
mqco_caution = 10

# Function to assign alarm status based on thresholds ONLY (no temp/humidity)
def assign_alarm_status(row):
    # Check for Hazardous
    if (row['pm2_5'] > pm25_hazard or 
        row['pm10'] > pm10_hazard or 
        row['gas'] >= mqgas_hazard or 
        row['co'] > mqco_hazard):
        return 2
    
    # Check for Caution
    elif (row['pm2_5'] >= pm25_caution or 
          row['pm10'] >= pm10_caution or 
          (row['gas'] >= mqgas_caution and row['gas'] < mqgas_hazard) or 
          (row['co'] >= mqco_caution and row['co'] <= mqco_hazard)):
        return 1
    
    # Otherwise Safe
    else:
        return 0

# Apply the labeling function
df['alarm_status'] = df.apply(assign_alarm_status, axis=1)

# Save back to CSV
df.to_csv('dataset/combined_data.csv', index=False)

print("✓ combined_data.csv has been relabeled based on thresholds")
print("\nLabel distribution:")
print(df['alarm_status'].value_counts().sort_index())
print(f"\nTotal records: {len(df)}")

# Show some examples
print("\nSample rows with different labels:")
for label in [0, 1, 2]:
    sample = df[df['alarm_status'] == label].iloc[0]
    label_name = {0: 'Safe', 1: 'Caution', 2: 'Hazardous'}[label]
    print(f"\n{label_name} example:")
    print(f"  PM2.5: {sample['pm2_5']:.2f}, PM10: {sample['pm10']:.2f}, Gas: {sample['gas']:.2f}, CO: {sample['co']:.2f}")
