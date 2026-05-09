/*
  MQ2_ESP32_SandboxAdapted.ino
  Implements MQ-2 calibration and PPM math adapted for ESP32 (12-bit ADC, 3.3V ADC, GPIO34)
  Based on SandboxElectronics article and adapted to user hardware choices.

  Wiring notes:
  - MQ-2 module heater/sensor Vcc: typically 5V (SENSOR_VCC)
  - MQ2 analog output goes to ADC pin through a voltage divider to protect 3.3V ADC.
  - Set VOLTAGE_DIVIDER_SCALAR so sensorVoltage = measuredVadc * VOLTAGE_DIVIDER_SCALAR
    (For divider with Rtop and Rbottom where Vadc = Vsensor * Rbottom/(Rtop+Rbottom),
     scalar = (Rtop+Rbottom)/Rbottom).
  - Analog pin used: GPIO 34 (input only).
*/

#include <Arduino.h>
#include <Preferences.h>

// Pin & ADC config
const int MQ2_PIN = 34;                 // GPIO34 ADC input
const int ADC_RESOLUTION = 12;          // bits (ESP32)
const float ADC_MAX = 4095.0f;          // 2^12 - 1
const float ADC_VREF = 3.3f;            // ADC reference voltage on ESP32 (V)

// Sensor / circuit constants (adjust to your hardware)
const float SENSOR_VCC = 5.0f;          // MQ-2 supply voltage (heater) — usually 5V
const float RL_VALUE = 10000.0f;        // Load resistor value in ohms (10kΩ typical for your hardware)
const float VOLTAGE_DIVIDER_SCALAR = 1.0f; // Set >1.0 if you use a divider. default 1.0 (no divider).
                                         // Example: divider Rtop=10k, Rbottom=10k => scalar = (10k+10k)/10k = 2.0

// Clean-air factor from MQ-2 datasheet / common libraries
// RO_CLEAN_AIR_FACTOR = Rs/Ro in clean air. Typical MQ-2 ~ 9.83 (library common value).
const float RO_CLEAN_AIR_FACTOR = 9.83f;

// Calibration and sampling intervals
const unsigned long CALIBRATION_SAMPLE_INTERVAL = 200; // ms between calibration samples
const int CALIBRATION_SAMPLE_TIMES = 50;              // number of calibration samples
const unsigned long SAMPLE_INTERVAL = 5000;           // normal periodic sample interval (ms)

// Curve parameters (Power-law form PPM = A * (Ro/Rs)^B)
// Use the MQ-2-specific curves you obtain from datasheet or curve-fitting.
// Default below sets Smoke parameters from your earlier data (A=3616.1, B=2.675).
struct GasCurve { float A; float B; const char *name; };
GasCurve LPG_Curve   = { 1.0f, 1.0f, "LPG (placeholder)" };  // REPLACE with real constants
GasCurve Smoke_Curve = { 3616.1f, 2.675f, "Smoke" };         // provided earlier
GasCurve CO_Curve    = { 1.0f, 1.0f, "CO (placeholder)" };   // REPLACE with real constants

// Runtime variables
float Ro = -1.0f; // sensor baseline resistance in clean air (ohms)
unsigned long lastSampleMillis = 0;
Preferences prefs;
int adcCaution = -1;
int adcHazard = -1;

// Forward declarations
float MQResistanceCalculation(int raw_adc);
float MQCalibration(int pin);
float getGasPPM(float Rs, GasCurve curve);
void printReading(int adc, float Vs_measured, float Rs, float ppm, const char *gasName);
int ppmToAdc(float ppm, GasCurve curve, float Ro_val);

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }

  // Configure ADC resolution for ESP32
  analogReadResolution(ADC_RESOLUTION);

  // Optionally you can set attenuation to read larger voltages; we assume voltage divider ensures ADC <= 3.3V.
  // analogSetPinAttenuation(MQ2_PIN, ADC_11db);  // uncomment only if you want different attenuation

  Serial.println("MQ-2 ESP32 adapted sketch starting...");
  Serial.println("Ensure the sensor is in clean air for calibration.");
  // Initialize Preferences and attempt to load saved Ro
  prefs.begin("mq2", false);
  float storedRo = prefs.getFloat("Ro", -1.0f);
  if (storedRo > 0.0f) {
    Ro = storedRo;
    Serial.print("Loaded saved Ro="); Serial.print(Ro); Serial.println(" ohms");
  } else {
    // Calibrate Ro (blocking boot calibration)
    Ro = MQCalibration(MQ2_PIN);
    Serial.print("Calibration complete. Ro=");
    Serial.print(Ro);
    Serial.println(" ohms");
    prefs.putFloat("Ro", Ro);
    Serial.println("Ro saved to preferences.");
  }
  // compute ADC thresholds for caution/hazard using current Ro
  adcCaution = ppmToAdc(200.0f, Smoke_Curve, Ro);
  adcHazard  = ppmToAdc(500.0f, Smoke_Curve, Ro);
  Serial.print("ADC threshold - Caution: "); Serial.println(adcCaution);
  Serial.print("ADC threshold - Hazard : "); Serial.println(adcHazard);
  lastSampleMillis = millis();
}

void loop() {
  unsigned long now = millis();

  if (now - lastSampleMillis >= SAMPLE_INTERVAL) {
    lastSampleMillis = now;

    int adc = analogRead(MQ2_PIN);
    float Vadc = (adc / ADC_MAX) * ADC_VREF;         // measured ADC voltage at ADC pin
    float Vs = Vadc * VOLTAGE_DIVIDER_SCALAR;       // estimate sensor Vout (accounting for divider)
    float Rs = MQResistanceCalculation(adc);        // sensor resistance (ohms), uses RL_VALUE and SENSOR_VCC

    // Calculate PPM for each gas (using Ro baseline)
    float smoke_ppm = getGasPPM(Rs, Smoke_Curve);
    float lpg_ppm = getGasPPM(Rs, LPG_Curve); // placeholder until tuned
    float co_ppm = getGasPPM(Rs, CO_Curve);   // placeholder until tuned

    // Print readings for debugging and calibration monitoring
    Serial.println("---- Measurement ----");
    printReading(adc, Vs, Rs, smoke_ppm, Smoke_Curve.name);
    Serial.print("LPG (est): "); Serial.println(lpg_ppm);
    Serial.print("CO  (est): "); Serial.println(co_ppm);
    Serial.println("---------------------");
  }

  // Check for serial command to recalibrate Ro (send 'c')
  if (Serial.available()) {
    char c = Serial.read();
    if (c == 'c' || c == 'C') {
      Serial.println("Manual recalibration requested...");
      Ro = MQCalibration(MQ2_PIN);
      prefs.putFloat("Ro", Ro);
      Serial.print("New Ro="); Serial.print(Ro); Serial.println(" ohms");
      adcCaution = ppmToAdc(200.0f, Smoke_Curve, Ro);
      adcHazard  = ppmToAdc(500.0f, Smoke_Curve, Ro);
      Serial.print("ADC threshold - Caution: "); Serial.println(adcCaution);
      Serial.print("ADC threshold - Hazard : "); Serial.println(adcHazard);
    }
  }

  // <-- Other non-blocking tasks can run here -->
}

/*
  MQResistanceCalculation:
  Given the raw ADC reading (0..ADC_MAX), computes RS (sensor resistance).
  Math:
    Vadc = (adc / ADC_MAX) * ADC_VREF                      // measured voltage at ADC pin
    Vsensor = Vadc * VOLTAGE_DIVIDER_SCALAR               // inverted divider to get actual sensor Vout
    RS = (Vcc - Vsensor) / Vsensor * RL_VALUE             // voltage divider between RS and RL
*/
float MQResistanceCalculation(int raw_adc) {
  if (raw_adc <= 0) raw_adc = 1;
  if (raw_adc >= (int)ADC_MAX) raw_adc = ADC_MAX - 1;

  float Vadc = (raw_adc / ADC_MAX) * ADC_VREF;
  float Vsensor = Vadc * VOLTAGE_DIVIDER_SCALAR;
  // protect division by zero
  if (Vsensor <= 0.000001f) Vsensor = 0.000001f;
  float Rs = ((SENSOR_VCC - Vsensor) / Vsensor) * RL_VALUE;
  return Rs;
}

/*
  MQCalibration:
  Samples RS multiple times in clean air and computes Ro.
  Ro = average_RS / RO_CLEAN_AIR_FACTOR
  (RO_CLEAN_AIR_FACTOR is the typical Rs/Ro ratio in clean air from datasheet ~9.83)
*/
float MQCalibration(int pin) {
  float rs_sum = 0.0f;
  Serial.println("Starting Ro calibration. Please ensure sensor is in clean air...");
  for (int i = 0; i < CALIBRATION_SAMPLE_TIMES; i++) {
    int adc = analogRead(pin);
    float rs = MQResistanceCalculation(adc);
    rs_sum += rs;
    Serial.print("Cal sample "); Serial.print(i+1);
    Serial.print(" / "); Serial.print(CALIBRATION_SAMPLE_TIMES);
    Serial.print(" : Rs=");
    Serial.println(rs);
    delay(CALIBRATION_SAMPLE_INTERVAL); // calibration can block briefly
  }
  float rs_avg = rs_sum / CALIBRATION_SAMPLE_TIMES;
  float ro_val = rs_avg / RO_CLEAN_AIR_FACTOR;
  return ro_val;
}

/*
  getGasPPM:
  Convert Rs (ohms) and baseline Ro into ppm for a given gas curve.

  The general power-law/log approach (consistent with many MQ references):

    ppm = A * (Ro / Rs)^B

  This form comes from the curve fit where ppm increases as Rs decreases (gas increases). The
  MQ datasheets often present Rs/Ro vs ppm log-log plots; you can convert slope/intercept
  from such plots into A/B or derive A/B from two known points.

  NOTE: Replace LPG_Curve and CO_Curve constants with values derived from the MQ-2 datasheet
  curve fits for accurate LPG and CO readings. Smoke_Curve is set to A=3616.1, B=2.675 by default.
*/
float getGasPPM(float Rs, GasCurve curve) {
  if (Ro <= 0.0f) return -1.0f; // not calibrated yet
  // protect against division by zero
  if (Rs <= 0.0f) Rs = 0.000001f;
  float ratio = Ro / Rs;
  // Handle placeholder curves that are not set
  if (curve.A <= 1.0f && curve.B <= 1.0f && curve.A != 1.0f) {
    // no-op placeholder check; fall through to compute something
  }
  float ppm = curve.A * pow(ratio, curve.B);
  return ppm;
}

// Convert a target ppm to the expected raw ADC value using current constants and Ro
int ppmToAdc(float ppm, GasCurve curve, float Ro_val) {
  if (ppm <= 0.0f || Ro_val <= 0.0f) return -1;
  float ratio = pow((ppm / curve.A), (1.0f / curve.B));
  float Rs = Ro_val / ratio;
  // compute Vout across RL: Vout = Vcc * (RL / (Rs + RL))
  float Vout = (RL_VALUE * SENSOR_VCC) / (Rs + RL_VALUE);
  float Vadc = Vout / VOLTAGE_DIVIDER_SCALAR;
  int adc = (int)round((Vadc / ADC_VREF) * ADC_MAX);
  if (adc < 0) adc = 0;
  if (adc > (int)ADC_MAX) adc = (int)ADC_MAX;
  return adc;
}

/*
  Helper: prints key values in a readable format
*/
void printReading(int adc, float Vsensor, float Rs, float ppm, const char *gasName) {
  Serial.print("ADC raw: "); Serial.print(adc);
  Serial.print("  Vadc: "); Serial.print((adc / ADC_MAX) * ADC_VREF, 3);
  Serial.print(" V  Vsensor: "); Serial.print(Vsensor, 3); Serial.print(" V");
  Serial.print("  Rs: "); Serial.print(Rs, 1); Serial.print(" ohm");
  Serial.print("  Ro: "); Serial.print(Ro, 1); Serial.print(" ohm");
  Serial.print("  ");
  Serial.print(gasName); Serial.print(": ");
  Serial.print(ppm, 2);
  Serial.println(" ppm");
}

/* 
  How to derive A and B (brief):
  - From MQ datasheet log-log plot for a gas you can take two points (ppm1, RsRo1) and (ppm2, RsRo2).
  - Using model ppm = A * (Ro/Rs)^B you can solve for A and B:
      log10(ppm) = log10(A) + B * log10(Ro/Rs)
    Rearranged to find B and A from two known pairs.
  - Many libraries provide fitted values; use those or perform your own regression.
*/
