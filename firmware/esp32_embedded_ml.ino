/*
 * MILES DATA STATION - ATTEMPT 11.5 (STRICT TIME SYNC + 10M WARMUP)
 */

#define BLYNK_TEMPLATE_ID "TMPL66fm4nCL-"
#define BLYNK_TEMPLATE_NAME "MILES Air Quality Prediction System"
#define BLYNK_AUTH_TOKEN "vKF0tDJwkknKj38WjeibW4rqdjr5pNUy"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "model.h"
#include <SPI.h>
#include <SD.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "time.h"

// --- HOTSPOT CREDENTIALS ---
char ssid[] = "MILES_Blynk";
char pass[] = "12345678";

// --- PIN DEFINITIONS ---
#define SD_CS 5
#define MQ2_PIN 34
#define MQ7_PIN 35
#define DHTPIN 4
#define BUZZER_PIN 25
#define RXD2 16
#define TXD2 17
#define DHTTYPE DHT22
#define RED_LED 32
#define YELLOW_LED 27
#define GREEN_LED 26

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
String fileName = "";

// NTP Server Settings
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 28800; // GMT+8 (Philippines)
const int daylightOffset_sec = 0;

struct SensorData {
    float pm2_5, pm10, temp, hum, gas, co;
} data;

String lcdRemark = "";
String blynkFullRemark = "";
int lastClass = 0;
unsigned long lastRead = 0;
bool hasValidPM = false;
bool blynkConfigured = false;
bool rtcReady = false;
unsigned long warmupStartMs = 0;
unsigned long lastWifiAttempt = 0;
unsigned long lastBlynkAttempt = 0;
bool wasWifiConnected = false;  // Track WiFi state for auto-reconnect
const unsigned long WIFI_RETRY_MS = 5000;  // Reduced from 15s for faster reconnection
const unsigned long BLYNK_RETRY_MS = 5000;
const unsigned long WARMUP_MS = 120000;

// --- CALIBRATION CONSTANTS (Updated 2026-05-25) ---
#define CALIBRATION_VERSION 3.0
#define CALIBRATION_DATE "2026-05-25"
#define MQ2_OFFSET_CALIBRATED 510.0   // Baseline ADC avg: 2210 | Target: 30 ppm (Safe)
#define CALIB_BASELINE_TEMP 34.3      // Reference temperature during calibration (°C)
#define CALIB_BASELINE_HUM 51.9       // Reference humidity during calibration (%)

// MQ7 (CO) Sensor - Exponential Calibration Formula (v3.0)
#define MQ7_VIN 3.3                   // Reference voltage
#define MQ7_ADC_MAX 4095.0            // 12-bit ADC resolution
#define MQ7_RL 10000.0                // Load resistance (ohms)
#define MQ7_RO 1822.0                 // Clean air resistance (ohms)
#define MQ7_COEFF 99.042              // Calibration coefficient
#define MQ7_EXPONENT -1.518           // Calibration exponent

#define RL_VALUE 10.0
#define RO_CLEAN_AIR_FACTOR 9.83
#define ADC_MAX 4095.0
float SmokeCurve[3] = { 2.3, 0.53, -0.44 };
float Ro = 0.0;

struct PendingReading {
    String timestamp;
    float pm2_5;
    float pm10;
    float temp;
    float hum;
    float gas;
    float co;
    int cls;
    String remark;
};

const int MAX_PENDING_READINGS = 24;
PendingReading pendingReadings[MAX_PENDING_READINGS];
int pendingHead = 0;
int pendingCount = 0;

// ════════════════════════════════════════════════════════════════════════
// SENSOR HISTORY FOR ENGINEERED FEATURES (200-tree model)
// ════════════════════════════════════════════════════════════════════════
struct SensorReading {
    float pm2_5, pm10, temp, hum, gas, co, wet_bulb;
    unsigned long timestamp;
};

const int HISTORY_SIZE = 10;  // Keep last 10 readings (50 seconds at 5s interval)
SensorReading sensorHistory[HISTORY_SIZE];
int historyIndex = 0;
bool historyFull = false;

// ===== ENHANCED SD LOGGING CONFIGURATION =====
#define MAX_FILE_SIZE_BYTES 52428800  // 50 MB per file
#define FILE_SIZE_CHECK_INTERVAL 600000  // Check size every 10 minutes
unsigned long lastFileSizeCheck = 0;

struct SDStats {
    unsigned long totalBytesWritten;
    int rotationCount;
    unsigned long lastWriteTime;
};
SDStats sdStats = {0, 0, 0};

void addToHistory(float pm25, float pm10, float t, float h, float g, float c, float wb) {
    sensorHistory[historyIndex].pm2_5 = pm25;
    sensorHistory[historyIndex].pm10 = pm10;
    sensorHistory[historyIndex].temp = t;
    sensorHistory[historyIndex].hum = h;
    sensorHistory[historyIndex].gas = g;
    sensorHistory[historyIndex].co = c;
    sensorHistory[historyIndex].wet_bulb = wb;
    sensorHistory[historyIndex].timestamp = millis();
    
    historyIndex = (historyIndex + 1) % HISTORY_SIZE;
    if (historyIndex == 0) historyFull = true;
}

float computeVolatility(int sensorIndex) {
    if (!historyFull && historyIndex < 2) return 0.0f;  // Not enough data
    
    int validCount = historyFull ? HISTORY_SIZE : historyIndex;
    if (validCount < 2) return 0.0f;
    
    float mean = 0.0f, variance = 0.0f;
    for (int i = 0; i < validCount; i++) {
        float val = (sensorIndex == 0) ? sensorHistory[i].pm2_5 :
                    (sensorIndex == 1) ? sensorHistory[i].pm10 :
                    (sensorIndex == 2) ? sensorHistory[i].gas :
                    sensorHistory[i].co;
        mean += val;
    }
    mean /= validCount;
    
    for (int i = 0; i < validCount; i++) {
        float val = (sensorIndex == 0) ? sensorHistory[i].pm2_5 :
                    (sensorIndex == 1) ? sensorHistory[i].pm10 :
                    (sensorIndex == 2) ? sensorHistory[i].gas :
                    sensorHistory[i].co;
        variance += (val - mean) * (val - mean);
    }
    variance /= validCount;
    return sqrt(variance);
}

float computeTrend(int sensorIndex) {
    if (!historyFull && historyIndex < 3) return 0.0f;  // Not enough data
    
    int current = (historyIndex - 1 + HISTORY_SIZE) % HISTORY_SIZE;
    int prev1 = (historyIndex - 2 + HISTORY_SIZE) % HISTORY_SIZE;
    int prev2 = (historyIndex - 3 + HISTORY_SIZE) % HISTORY_SIZE;
    
    float curr_val = (sensorIndex == 0) ? sensorHistory[current].pm2_5 :
                     (sensorIndex == 1) ? sensorHistory[current].pm10 :
                     (sensorIndex == 2) ? sensorHistory[current].gas :
                     sensorHistory[current].co;
    float prev1_val = (sensorIndex == 0) ? sensorHistory[prev1].pm2_5 :
                      (sensorIndex == 1) ? sensorHistory[prev1].pm10 :
                      (sensorIndex == 2) ? sensorHistory[prev1].gas :
                      sensorHistory[prev1].co;
    float prev2_val = (sensorIndex == 0) ? sensorHistory[prev2].pm2_5 :
                      (sensorIndex == 1) ? sensorHistory[prev2].pm10 :
                      (sensorIndex == 2) ? sensorHistory[prev2].gas :
                      sensorHistory[prev2].co;
    
    // Linear trend: (current - prev2) / 2
    return (curr_val - prev2_val) / 2.0f;
}

void buildFullFeatureArray(float input[35], float pm25, float pm10, float t, float h, float g, float c, float wb) {
    // Core 8 features (features 0-7)
    input[0] = pm25;
    input[1] = pm10;
    input[2] = t;
    input[3] = h;
    input[4] = g;
    input[5] = c;
    input[6] = getCurrentHour();  // time_of_day (0-23 from RTC)
    input[7] = wb;  // wet_bulb
    
    // Feature ratios (features 8-11)
    input[8] = (pm10 > 0.1f) ? (pm25 / pm10) : 0.0f;  // PM2.5/PM10 ratio
    input[9] = (c > 0.1f) ? (g / c) : 0.0f;  // Gas/CO ratio
    input[10] = (h > 0.1f) ? (g / h) : 0.0f;  // Gas/Humidity ratio
    input[11] = (h > 0.1f) ? (pm25 / h) : 0.0f;  // PM2.5/Humidity ratio
    
    // Deltas - rate of change (features 12-14)
    if (historyFull || historyIndex > 0) {
        int prev_idx = (historyIndex - 1 + HISTORY_SIZE) % HISTORY_SIZE;
        input[12] = pm25 - sensorHistory[prev_idx].pm2_5;  // ΔPM2.5
        input[13] = g - sensorHistory[prev_idx].gas;  // ΔGas
        input[14] = c - sensorHistory[prev_idx].co;  // ΔCO
    } else {
        input[12] = 0.0f;
        input[13] = 0.0f;
        input[14] = 0.0f;
    }
    
    // Lag-1 features (features 15-17) - previous reading
    if (historyFull || historyIndex > 0) {
        int prev_idx = (historyIndex - 1 + HISTORY_SIZE) % HISTORY_SIZE;
        input[15] = sensorHistory[prev_idx].pm2_5;  // PM2.5(t-1)
        input[16] = sensorHistory[prev_idx].gas;  // Gas(t-1)
        input[17] = sensorHistory[prev_idx].co;  // CO(t-1)
    } else {
        input[15] = 0.0f;
        input[16] = 0.0f;
        input[17] = 0.0f;
    }
    
    // Lag-2 features (features 18-20) - two readings back
    if (historyFull || historyIndex > 1) {
        int prev2_idx = (historyIndex - 2 + HISTORY_SIZE) % HISTORY_SIZE;
        input[18] = sensorHistory[prev2_idx].pm2_5;  // PM2.5(t-2)
        input[19] = sensorHistory[prev2_idx].gas;  // Gas(t-2)
        input[20] = sensorHistory[prev2_idx].co;  // CO(t-2)
    } else {
        input[18] = 0.0f;
        input[19] = 0.0f;
        input[20] = 0.0f;
    }
    
    // Volatility features (features 21-23) - variability over time
    input[21] = computeVolatility(0);  // PM2.5 volatility
    input[22] = computeVolatility(2);  // Gas volatility
    input[23] = computeVolatility(3);  // CO volatility
    
    // Trend features (features 24-26) - direction & momentum
    input[24] = computeTrend(0);  // PM2.5 trend
    input[25] = computeTrend(2);  // Gas trend
    input[26] = computeTrend(3);  // CO trend
    
    // Anomaly flags (features 27-30) - extreme value detection
    input[27] = (pm25 > 100.0f) ? 1.0f : 0.0f;  // High PM2.5 flag
    input[28] = (c > 30.0f) ? 1.0f : 0.0f;  // High CO flag
    input[29] = (g > 63.0f) ? 1.0f : 0.0f;  // High Gas flag
    input[30] = (t > 35.0f) ? 1.0f : 0.0f;  // High temp flag
    
    // Multi-sensor correlation flags (features 31-34)
    input[31] = ((pm25 > 50.0f) && (c > 9.0f)) ? 1.0f : 0.0f;  // PM+CO both high
    input[32] = ((g > 40.0f) && (c > 9.0f)) ? 1.0f : 0.0f;  // Gas+CO both high
    input[33] = (pm25 > 50.0f) && (g > 40.0f) ? 1.0f : 0.0f;  // PM+Gas both high
    input[34] = (wb > 30.0f) && (c > 9.0f) ? 1.0f : 0.0f;  // Heat+CO both high
}

void queuePendingReading(const PendingReading &reading) {
    pendingReadings[pendingHead] = reading;
    pendingHead = (pendingHead + 1) % MAX_PENDING_READINGS;
    if (pendingCount < MAX_PENDING_READINGS) {
        pendingCount++;
    }
}

bool popPendingReading(PendingReading &reading) {
    if (pendingCount <= 0) {
        return false;
    }

    int tailIndex = (pendingHead - pendingCount + MAX_PENDING_READINGS) % MAX_PENDING_READINGS;
    reading = pendingReadings[tailIndex];
    pendingCount--;
    return true;
}

void sendReadingToBlynk(const PendingReading &reading) {
    if (!Blynk.connected()) {
        return;
    }

    Blynk.virtualWrite(V0, reading.pm2_5);
    Blynk.virtualWrite(V1, reading.pm10);
    Blynk.virtualWrite(V2, reading.temp);
    Blynk.virtualWrite(V3, reading.hum);
    Blynk.virtualWrite(V4, reading.gas);
    Blynk.virtualWrite(V5, reading.co);
    Blynk.virtualWrite(V7, "REMARKS: " + reading.remark + "\n\nTime: " + reading.timestamp);
}

void flushPendingReadings(uint8_t maxItems = 4) {
    if (!Blynk.connected()) {
        return;
    }

    PendingReading reading;
    uint8_t sent = 0;
    while (sent < maxItems && popPendingReading(reading)) {
        sendReadingToBlynk(reading);
        sent++;
    }
}

// WiFi Event Handler - Called when WiFi connection status changes
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch(event) {
        case WIFI_EVENT_STA_CONNECTED:
            Serial.println("[WiFi] Connected to AP");
            wasWifiConnected = true;
            lastWifiAttempt = 0;  // Reset timer for immediate reconnection if needed
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            Serial.printf("[WiFi] Disconnected (reason: %d)\n", info.wifi_sta_disconnected.reason);
            wasWifiConnected = false;
            lastWifiAttempt = 0;  // Reset timer for immediate reconnection attempt
            break;
        case IP_EVENT_STA_GOT_IP:
            Serial.printf("[WiFi] Got IP: %s\n", WiFi.localIP().toString().c_str());
            break;
        default:
            break;
    }
}

void manageConnections() {
    unsigned long now = millis();
    wl_status_t currentWifiStatus = WiFi.status();
    
    // Handle WiFi Connection/Reconnection
    if (currentWifiStatus != WL_CONNECTED) {
        // WiFi disconnected - attempt reconnection
        if (now - lastWifiAttempt >= WIFI_RETRY_MS) {
            lastWifiAttempt = now;
            Serial.println("[WiFi] Attempting reconnection...");
            WiFi.mode(WIFI_STA);
            WiFi.setAutoReconnect(true);  // Enable auto-reconnect
            WiFi.begin(ssid, pass);
        }
        return;
    }
    
    // WiFi is connected - manage Blynk connection
    if (!blynkConfigured) {
        Blynk.config(BLYNK_AUTH_TOKEN);
        blynkConfigured = true;
    }

    if (!Blynk.connected() && now - lastBlynkAttempt >= BLYNK_RETRY_MS) {
        lastBlynkAttempt = now;
        Serial.println("[Blynk] Connecting to Blynk...");
        Blynk.connect(0);
    }

    if (Blynk.connected()) {
        flushPendingReadings();
    }
}

// Kukuha ng Real Time mula sa system clock
String getTimeString() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "TIME_NOT_SYNCED";
    }
    char timeStr[25];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &timeinfo);
    return String(timeStr);
}

// Get current hour (0-23) from RTC for time_of_day feature
float getCurrentHour() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return 12.0f;  // Default to noon if RTC not synced
    }
    return (float)timeinfo.tm_hour;  // Returns 0-23
}

// Robust PMS7003 reader
bool readPMS7003Frame(float &pm25, float &pm10, uint32_t timeoutMs = 1200) {
    unsigned long start = millis();
    while (millis() - start < timeoutMs) {
        while (Serial2.available() > 0) {
            if (Serial2.peek() != 0x42) {
                Serial2.read();
                continue;
            }
            if (Serial2.available() < 32) break;
            uint8_t frame[32];
            size_t n = Serial2.readBytes(frame, 32);
            if (n != 32) continue;
            if (frame[0] != 0x42 || frame[1] != 0x4D) continue;
            uint16_t frameLen = ((uint16_t)frame[2] << 8) | frame[3];
            if (frameLen != 28) continue;
            uint16_t sum = 0;
            for (int i = 0; i < 30; i++) sum += frame[i];
            uint16_t received = ((uint16_t)frame[30] << 8) | frame[31];
            if (sum != received) continue;
            pm25 = ((uint16_t)frame[12] << 8) | frame[13];
            pm10 = ((uint16_t)frame[14] << 8) | frame[15];
            return true;
        }
        delay(2);
        yield();
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════════════════
// MILES COMPLETE DECISION TABLE - Dynamic Remarks Generator
// Wet-Bulb Temperature + Sensor Escalation + Multi-Sensor Logic (May 28, 2026)
// ═══════════════════════════════════════════════════════════════════════════════
void processDecisions(int cls, float pm25, float pm10, float co, float gas, float hum, float temp) {
    // Step 1: Calculate Wet-Bulb Temperature (Heat Stress Indicator)
    float Tw = temp * atan(0.151977 * pow(hum + 8.313659, 0.5)) + atan(temp + hum) - atan(hum - 1.676331) + 0.00391838 * pow(hum, 1.5) * atan(0.023101 * hum) - 4.686035;

    // Step 2: Evaluate Sensor Thresholds (RA 8749 IRR Standards)
    bool isPm25Haz = (pm25 > 100.0);        // PM2.5 > 100 μg/m³
    bool isPm10Haz = (pm10 > 230.0);        // PM10 > 230 μg/m³
    bool isGasHaz = (gas >= 63.0);          // Gas ≥ 63 ppm
    bool isCoHaz = (co > 30.0);             // CO > 30 ppm

    bool isPm25Cau = (pm25 >= 51.0);        // PM2.5 51-100 μg/m³
    bool isPm10Cau = (pm10 >= 151.0);       // PM10 151-230 μg/m³
    bool isGasCau = (gas >= 40.0);          // Gas 40-62 ppm
    bool isCoCau = (co > 9.0 && co <= 30.0); // CO 10-30 ppm

    int cautionCount = isPm25Cau + isPm10Cau + isGasCau + isCoCau;
    int hazardCount = isPm25Haz + isPm10Haz + isGasHaz + isCoHaz;

    // Step 3: Apply Decision Rules from MILES COMPLETE DECISION TABLE
    if (hum >= 95.0 && gas <= 40.0 && Tw <= 35.0) {
        cls = 0;  // MISTING OVERRIDE
    }
    else if (Tw > 35.0) {
        cls = 2;  // EXTREME HEAT ESCALATION
    }
    else if (Tw > 30.0 && cls == 0) {
        cls = 1;  // HEAT STRESS ESCALATION
    }
    else if (hazardCount >= 1) {
        cls = 2;  // HAZARD ESCALATION
    }
    else if (cautionCount >= 1 && cls == 0) {
        cls = 1;  // CAUTION ESCALATION
    }
    else if (cautionCount >= 3 && Tw > 30.0) {
        cls = 2;  // THREE+ CAUTION WITH HEAT
    }

    // Step 4: Generate Dynamic Remarks based on Class and Sensor Patterns
    String status = "";

    if (Tw > 35.0) {
        status = "HAZARDOUS: EXTREME HEAT DETECTED, EVACUATE TO COOLING AREA NOW";
    }
    else if (cls == 2) {
        if (Tw > 30.0) {
            status = "HAZARDOUS: HIGH WET-BULB TEMP, STOP NON-ESSENTIAL PHYSICAL WORK";
        }
        else if (hazardCount >= 3) {
            status = "HAZARDOUS: MULTIPLE SENSORS CRITICAL, EXECUTE FULL EMERGENCY PROTOCOL";
        }
        else if (isGasHaz && isCoHaz) {
            status = "HAZARDOUS: TOXIC GAS AND CO CRITICAL, EVACUATE AFFECTED ZONE NOW";
        }
        else if (isPm25Haz && isCoHaz) {
            status = "HAZARDOUS: HIGH DUST AND CO DETECTED, TREAT AS FIRE RISK NOW";
        }
        else if (isPm25Haz && isGasHaz) {
            status = "HAZARDOUS: DUST AND COMBUSTIBLE GAS CRITICAL, PREPARE EVACUATION";
        }
        else if (isPm25Haz && isPm10Haz) {
            status = "HAZARDOUS: EXTREME PM LEVELS, ENFORCE RESPIRATORS IMMEDIATELY";
        }
        else if (isCoHaz) {
            status = "HAZARDOUS: CO LEVELS CRITICAL, MOVE UPWIND IMMEDIATELY";
        }
        else if (isGasHaz) {
            status = "HAZARDOUS: GAS LEAK DETECTED, STOP IGNITION ACTIVITIES NOW";
        }
        else if (isPm10Haz) {
            status = "HAZARDOUS: COARSE DUST CRITICAL, ACTIVATE DUST SUPPRESSION NOW";
        }
        else if (isPm25Haz) {
            status = "HAZARDOUS: FINE DUST CRITICAL, STOP DUST-PRODUCING WORK NOW";
        }
        else {
            status = "HAZARDOUS: ANOMALY DETECTED, PAUSE OPERATIONS UNTIL STABLE";
        }
    }
    else if (cls == 1) {
        if (Tw >= 27.0 && Tw <= 30.0 && cautionCount == 0) {
            status = "CAUTION: ELEVATED HEAT, SLOW WORK AND HYDRATE";
        }
        else if (cautionCount >= 3) {
            status = "CAUTION: MULTIPLE SENSORS RISING, ACTIVE PROTECTIVE PROTOCOL";
        }
        else if (isPm10Cau && isCoCau) {
            status = "CAUTION: DUST AND CO RISING, START FIRE-SOURCE CHECK";
        }
        else if (isPm10Cau && isGasCau) {
            status = "CAUTION: DUST AND GAS RISING, PREPARE RESPIRATORY PROTECTION";
        }
        else if (isCoCau) {
            status = "CAUTION: CO LEVELS RISING, MOVE TO CLEANER AIR ZONE";
        }
        else if (isGasCau) {
            status = "CAUTION: COMBUSTIBLE GAS DETECTED, CHECK SOURCES NOW";
        }
        else if (isPm10Cau) {
            status = "CAUTION: COARSE DUST RISING, IMPROVE VENTILATION NOW";
        }
        else if (isPm25Cau) {
            status = "CAUTION: FINE DUST RISING, REDUCE DUST EXPOSURE NOW";
        }
        else {
            status = "CAUTION: AIR QUALITY DEGRADING, APPLY PPE AND REASSESS";
        }
    }
    else {
        if (hum >= 95.0 && gas <= 40.0) {
            status = "SAFE: HIGH HUMIDITY MIST DETECTED, CONTINUE WORK";
        }
        else if (hum > 70.0) {
            status = "SAFE: ELEVATED HUMIDITY ONLY, CONTINUE TASKS WITH HYDRATION";
        }
        else {
            status = "SAFE: ALL SENSORS NORMAL, CONTINUE OPERATIONS";
        }
    }

    lcdRemark = status;
    blynkFullRemark = "REMARKS: " + status;
}

float MQResistanceCalculation(int raw_adc) {
    if (raw_adc <= 0) raw_adc = 1;
    if (raw_adc >= ADC_MAX) raw_adc = ADC_MAX - 1;
    return ((float)RL_VALUE * (ADC_MAX - raw_adc) / raw_adc);
}

float MQCalibration(int mq_pin) {
    float val = 0;
    for (int i = 0; i < 50; i++) {
        val += MQResistanceCalculation(analogRead(mq_pin));
        delay(500);
    }
    val /= 50;
    val /= RO_CLEAN_AIR_FACTOR;
    return val;
}

float MQRead(int mq_pin) {
    float rs = 0;
    for (int i = 0; i < 5; i++) {
        rs += MQResistanceCalculation(analogRead(mq_pin));
        delay(50);
    }
    rs /= 5;
    return rs;
}

float MQGetSmokePpm(float rs_ro_ratio) {
    return pow(10.0, ((log10(rs_ro_ratio) - SmokeCurve[1]) / SmokeCurve[2]) + SmokeCurve[0]);
}

void scrollRemark(String msg) {
    static int pos = 0;
    static unsigned long lastScroll = 0;
    String displayMsg = "REMARK: " + msg + " ";
    if (millis() - lastScroll > 350) {
        lastScroll = millis();
        lcd.setCursor(0, 3);
        String toPrint = displayMsg.substring(pos, pos + 20);
        while (toPrint.length() < 20) toPrint += " ";
        lcd.print(toPrint);
        pos++;
        if (pos > displayMsg.length() - 20) pos = 0;
    }
}

// Check and rotate SD log file if size limit reached
void checkAndRotateLogFile() {
    if (millis() - lastFileSizeCheck < FILE_SIZE_CHECK_INTERVAL) {
        return;  // Skip if checked recently
    }
    lastFileSizeCheck = millis();
    
    File currentFile = SD.open(fileName, FILE_READ);
    if (currentFile) {
        unsigned long fileSize = currentFile.size();
        currentFile.close();
        
        if (fileSize >= MAX_FILE_SIZE_BYTES) {
            // File size limit reached - rotate to new file
            int fileNum = 1;
            while (SD.exists("/MILES_LOG_" + String(fileNum) + ".csv")) fileNum++;
            
            String oldFileName = fileName;
            fileName = "/MILES_LOG_" + String(fileNum) + ".csv";
            sdStats.rotationCount++;
            sdStats.totalBytesWritten = 0;
            
            // Create new file with header
            File newFile = SD.open(fileName, FILE_WRITE);
            if (newFile) {
                newFile.println("Timestamp,PM2.5,PM10,Temp,Hum,Gas,CO,Class,Remark");
                newFile.close();
                
                // Log rotation event
                Serial.println("LOG ROTATED: " + oldFileName + " -> " + fileName);
                Serial.println("Previous file size: " + String(fileSize) + " bytes");
            }
        }
    }
}

// Enhanced SD write with error recovery
bool writeToSDCard(const String& timestamp, float pm2_5, float pm10, 
                   float temp, float hum, float gas, float co, 
                   int cls, const String& remark) {
    int retries = 3;
    while (retries > 0) {
        File file = SD.open(fileName, FILE_APPEND);
        if (file) {
            String line = "";
            line += timestamp + ",";
            line += String(pm2_5, 1) + ",";
            line += String(pm10, 1) + ",";
            line += String(temp, 1) + ",";
            line += String(hum, 1) + ",";
            line += String(gas, 1) + ",";
            line += String(co, 1) + ",";
            line += String(cls) + ",";
            line += remark + "\n";
            
            size_t bytesWritten = file.print(line);
            file.close();
            
            if (bytesWritten > 0) {
                sdStats.totalBytesWritten += bytesWritten;
                sdStats.lastWriteTime = millis();
                return true;
            }
        }
        retries--;
        if (retries > 0) delay(100);  // Brief delay before retry
    }
    return false;  // Failed after retries
}

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0); lcd.print("WELCOME TO MILES!");
    lcd.setCursor(0, 1); lcd.print("DATA STATION");
    delay(2000);

    lcd.clear(); lcd.setCursor(0, 0); lcd.print("INITIALIZING LOG...");
    
    // Initialize SD card
    if (!SD.begin(SD_CS)) {
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("SD INIT FAILED!");
        delay(2000);
        return;  // Exit setup if SD fails
    }
    
    // Enhanced file initialization with timestamp-based naming
    int fileNum = 1;
    while (SD.exists("/MILES_LOG_" + String(fileNum) + ".csv")) fileNum++;
    fileName = "/MILES_LOG_" + String(fileNum) + ".csv";
    
    File file = SD.open(fileName, FILE_WRITE);
    if (file) {
        String header = "Timestamp,PM2.5,PM10,Temp,Hum,Gas,CO,Class,Remark\n";
        file.print(header);
        file.close();
        sdStats.totalBytesWritten = header.length();
        sdStats.rotationCount = fileNum - 1;
        lcd.clear(); lcd.setCursor(0, 0); 
        lcd.print("LOG: MILES_LOG_" + String(fileNum));
        delay(1500);
    } else {
        lcd.clear(); lcd.setCursor(0, 0); 
        lcd.print("SD INIT FAILED!");
        delay(2000);
        return;  // Exit setup if file creation fails
    }

    lcd.clear(); lcd.setCursor(0, 0); lcd.print("CONNECTING WIFI...");
    
    // Register WiFi event handler for auto-reconnect
    WiFi.onEvent(onWiFiEvent);
    
    // Enable auto-reconnect before connecting
    WiFi.setAutoReconnect(true);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    lastWifiAttempt = millis();
    wasWifiConnected = false;
    unsigned long wifiStart = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - wifiStart < 20000) {
        delay(500);
        lcd.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        lcd.clear(); lcd.setCursor(0, 0); lcd.print("SYNCING TIME...");
        configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

        struct tm timeinfo;
        int retry = 0;
        while (!getLocalTime(&timeinfo) && retry < 10) {
            delay(1000);
            retry++;
        }

        lcd.setCursor(0, 1); lcd.print("TIME UPDATED!");
        delay(1000);
        rtcReady = true;
    } else {
        lcd.clear(); lcd.print("OFFLINE MODE");
        delay(1000);
    }

    Blynk.config(BLYNK_AUTH_TOKEN);
    blynkConfigured = true;
    warmupStartMs = millis();
    lcd.clear(); lcd.setCursor(0, 0); lcd.print("SAMPLING STARTED");

    dht.begin();
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("CALIBRATING MQ2...");
    Ro = MQCalibration(MQ2_PIN);
    Serial.print("MQ2 Ro calibrated: ");
    Serial.println(Ro);
    lcd.setCursor(0, 1); lcd.print("MQ2 Ro:"); lcd.print(Ro, 1);
    delay(1500);
    while (Serial2.available()) {
        Serial2.read();
    }

    lcd.clear();
}

void loop() {
    manageConnections();
    Blynk.run();

    unsigned long now = millis();
    if (now - lastRead >= 5000) {
        lastRead = now;
        data.temp = dht.readTemperature();
        data.hum = dht.readHumidity();
        float rs = MQRead(MQ2_PIN);
        float rs_ro_ratio = rs / Ro;
        data.gas = MQGetSmokePpm(rs_ro_ratio);
        
        // MQ7 (CO) Conversion - Exponential Calibration (v3.0)
        // Step 1: Vout = MQ7_ADC × (3.3 / 4095)
        // Step 2: Rs = 10,000 × (3.3 - Vout) / Vout
        // Step 3: ratio = Rs / 2120
        // Step 4: MQ7_PPM = 99.042 × ratio^(-1.518)
        float mq7_adc = analogRead(MQ7_PIN);
        float mq7_vout = mq7_adc * (MQ7_VIN / MQ7_ADC_MAX);
        float mq7_rs = MQ7_RL * (MQ7_VIN - mq7_vout) / mq7_vout;
        float mq7_ratio = mq7_rs / MQ7_RO;
        data.co = MQ7_COEFF * pow(mq7_ratio, MQ7_EXPONENT);
        if (data.co < 0.0) data.co = 0.0;

        float pm25Read = 0.0, pm10Read = 0.0;
        if (readPMS7003Frame(pm25Read, pm10Read, 1200)) {
            data.pm2_5 = pm25Read;
            data.pm10 = pm10Read;
            hasValidPM = true;
        } else if (!hasValidPM) {
            data.pm2_5 = 0.0;
            data.pm10 = 0.0;
        }

        // Add to history for engineered features
        float wet_bulb = data.temp * atan(0.151977 * pow(data.hum + 8.313659, 0.5)) + atan(data.temp + data.hum) - atan(data.hum - 1.676331) + 0.00391838 * pow(data.hum, 1.5) * atan(0.023101 * data.hum) - 4.686035;
        addToHistory(data.pm2_5, data.pm10, data.temp, data.hum, data.gas, data.co, wet_bulb);
        
        // Build full 35-feature array with engineered features
        float input[35];
        buildFullFeatureArray(input, data.pm2_5, data.pm10, data.temp, data.hum, data.gas, data.co, wet_bulb);
        
        // Predict using 200-tree model
        lastClass = predict(input, 35);
        processDecisions(lastClass, data.pm2_5, data.pm10, data.co, data.gas, data.hum, data.temp);

        PendingReading reading;
        reading.timestamp = getTimeString();
        reading.pm2_5 = data.pm2_5;
        reading.pm10 = data.pm10;
        reading.temp = data.temp;
        reading.hum = data.hum;
        reading.gas = data.gas;
        reading.co = data.co;
        reading.cls = lastClass;
        reading.remark = lcdRemark;

        // Check for log file rotation
        checkAndRotateLogFile();
        
        // Write to SD with enhanced error handling
        bool writeSuccess = writeToSDCard(
            reading.timestamp, reading.pm2_5, reading.pm10, 
            reading.temp, reading.hum, reading.gas, reading.co, 
            reading.cls, reading.remark
        );
        
        if (!writeSuccess) {
            // Log write failed - optional alert
            Serial.println("WARNING: SD write failed for timestamp " + reading.timestamp);
        }

        if (Blynk.connected()) {
            flushPendingReadings();
            sendReadingToBlynk(reading);
        } else {
            queuePendingReading(reading);
        }

        digitalWrite(GREEN_LED, (lcdRemark.startsWith("SAFE")));
        digitalWrite(YELLOW_LED, (lcdRemark.startsWith("CAUTION")));
        digitalWrite(RED_LED, (lcdRemark.startsWith("HAZARDOUS")));
        digitalWrite(BUZZER_PIN, (lcdRemark.startsWith("HAZARDOUS")) ? HIGH : LOW);

        lcd.setCursor(0, 0); lcd.print("P2.5:"); lcd.print((int)data.pm2_5); lcd.print("  ");
        lcd.setCursor(11, 0); lcd.print("P10:"); lcd.print((int)data.pm10); lcd.print("  ");
        lcd.setCursor(0, 1); lcd.print("SMK:"); lcd.print((int)data.gas); lcd.print("  ");
        lcd.setCursor(11, 1); lcd.print("CO :"); lcd.print((int)data.co); lcd.print("  ");
        lcd.setCursor(0, 2); lcd.print("T:"); lcd.print(data.temp, 1); lcd.print("C ");
        lcd.setCursor(11, 2); lcd.print("H:"); lcd.print(data.hum, 0); lcd.print("% ");
    }

    if (millis() - warmupStartMs < WARMUP_MS) {
        unsigned long remaining = (WARMUP_MS - (millis() - warmupStartMs)) / 1000;
        lcd.setCursor(0, 3);
        String warmupMsg = "WARMUP: " + String(remaining) + "s left   ";
        while (warmupMsg.length() < 20) warmupMsg += " ";
        lcd.print(warmupMsg.substring(0, 20));
    }

    scrollRemark(lcdRemark);
}
