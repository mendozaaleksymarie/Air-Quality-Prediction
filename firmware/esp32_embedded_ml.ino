/*
 * ══════════════════════════════════════════════════════════════════════
 * AIR QUALITY PREDICTION - EMBEDDED ML FIRMWARE (ESP32)
 * ══════════════════════════════════════════════════════════════════════
 * 
 * SYSTEM: Embedded Random Forest on ESP32 with WiFi Admin Panel
 * - Safe (0): Normal air quality
 * - Caution (1): Elevated pollution - manual inspection needed
 * - Hazardous (2): Immediate evacuation required
 * 
 * KEY FEATURES:
 * ✓ 99.98% accuracy on-device ML inference
 * ✓ WiFi Admin Panel for data management
 * ✓ ML model embedded as C++ header (model.h)
 * ✓ Real-time inference (~10ms per prediction)
 * ✓ Multi-sensor contextual analysis with confidence scoring
 * ✓ 20x4 LCD display with real-time data
 * ✓ LittleFS data logging (CSV format)
 * ✓ Time sync and data download via web interface
 * 
 * HARDWARE:
 * - ESP32 Development Board
 * - DHT22 (Temperature + Humidity) - Pin 4
 * - MQ2 (Gas/VOC Sensor) - Pin 34 (ADC)
 * - MQ7 (CO Sensor) - Pin 35 (ADC)
 * - PMS5003 (PM2.5/PM10) - UART (TX2/RX2)
 * - 20x4 LCD I2C Display (0x27)
 * - RGB LEDs: Green (18), Yellow (19), Red (32)
 * - Buzzer - Pin 25
 * 
 * MODEL: Random Forest Classifier (200 trees, 99.98% accuracy)
 * INPUT: [PM2.5, PM10, Temp, Humidity, Gas, CO, TimeOfDay]
 * OUTPUT: Class (0/1/2) + Confidence Score
 * 
 * ══════════════════════════════════════════════════════════════════════
 */

// Embedded ML model & wireless libraries
#include "model.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <time.h>

// ════════════════════════════════════════════════════════════════════
// ████ CONFIGURATION SECTION (USER EDITABLE)
// ════════════════════════════════════════════════════════════════════

// WiFi Configuration
const char* ap_ssid = "MILES_Data_Station";
const char* ap_password = "password123";

// System Configuration
const int SENSOR_READ_INTERVAL = 10000;  // Read sensors every 10 seconds
const int WARMUP_TIME = 120000;  // 120 seconds (2 mins) warm-up period
const float CONFIDENCE_THRESHOLD = 0.90;  // Only act if confidence > 90%

// LCD display refresh interval
const int LCD_REFRESH_INTERVAL = 10000;  // Refresh LCD every 10 seconds

// ════════════════════════════════════════════════════════════════════
// ████ PIN DEFINITIONS
// ════════════════════════════════════════════════════════════════════

#define DHTPIN 4
#define DHTTYPE DHT22
#define MQ2_PIN 34
#define MQ7_PIN 35
#define BUZZER_PIN 25
#define RED_LED 32
#define YELLOW_LED 19
#define GREEN_LED 18

// UART for PMS5003
#define RXD2 16
#define TXD2 17

// ════════════════════════════════════════════════════════════════════
// ████ GLOBAL VARIABLES
// ════════════════════════════════════════════════════════════════════

DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Sensor data structure
struct SensorData {
    float pm2_5;
    float pm10;
    float temperature;
    float humidity;
    float gas;
    float co;
    int time_of_day;
    unsigned long timestamp;
} currentSensorData;

// Model prediction structure
struct ModelPrediction {
    int predicted_class;  // 0: Safe, 1: Caution, 2: Hazardous
    float confidence;
    bool is_valid;
    uint32_t inference_time_ms;
} lastPrediction;

// System state
struct SystemState {
    int warmup_time_remaining;
    bool initialization_complete;
    unsigned long clearTimestamp;
    bool isWaitingAfterClear;
} systemState;

// Constants for display
const char* CLASS_NAMES[] = {"SAFE", "CAUTION", "HAZARDOUS"};
const int CLASS_COLORS[] = {GREEN_LED, YELLOW_LED, RED_LED};

// ════════════════════════════════════════════════════════════════════
// ████ SETUP FUNCTION
// ════════════════════════════════════════════════════════════════════

void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, 16, 17);
    delay(1000);
    
    // Initialize GPIO pins
    initializePins();
    blinkLED(YELLOW_LED, 3);  // Yellow blinks = initializing
    
    // Initialize sensors
    initializeSensors();
    
    // Initialize LCD display
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0); 
    lcd.print("MILES_Data_Station");
    lcd.setCursor(0, 1); 
    lcd.print("Initializing...");
    lcd.setCursor(0, 3); 
    lcd.print("Please wait...");
    delay(500);  // Reduced from 3000 to prevent watchdog starvation
    lcd.clear();
    
    // Initialize LittleFS
    if (!LittleFS.begin(true)) {
        Serial.println("✗ LittleFS Mount Failed");
    } else {
        Serial.println("✓ LittleFS Mounted Successfully");
    }
    
    // Create CSV header if not exists
    if (!LittleFS.exists("/data.csv")) {
        File file = LittleFS.open("/data.csv", FILE_WRITE);
        if (file) {
            file.println("Timestamp,PM25,PM10,MQ2_ppm,MQ7_ppm,Temp,Hum,Confidence,Status");
            file.close();
        }
    }
    
    // Setup WiFi Access Point
    WiFi.softAP(ap_ssid, ap_password);
    Serial.print("✓ WiFi AP Started: ");
    Serial.println(WiFi.softAPIP());
    yield();  // Allow WiFi stack to initialize
    delay(100);
    
    // Setup web server routes
    setupWebRoutes();
    server.begin();
    yield();  // Critical: Allow async server to start properly
    delay(200);
    
    // Initialize system state
    systemState.warmup_time_remaining = WARMUP_TIME;
    systemState.initialization_complete = false;
    systemState.clearTimestamp = 0;
    systemState.isWaitingAfterClear = false;
    
    Serial.println("\n╔════════════════════════════════════════════════════════════╗");
    Serial.println("║  AIR QUALITY PREDICTION - EMBEDDED ML (ESP32)              ║");
    Serial.println("║  Status: INITIALIZING... (WiFi Admin Panel Active)         ║");
    Serial.println("╚════════════════════════════════════════════════════════════╝\n");
    
    Serial.println("✓ SYSTEM READY - Entering 2-minute warm-up phase...");
    Serial.println("  (Sensors stabilizing, ML model ready)");
    Serial.println("  (Model: 200 Random Forest trees, 99.98% accuracy)");
    Serial.println("  (Access admin panel: 192.168.4.1/download)");
}

// ════════════════════════════════════════════════════════════════════
// ████ MAIN LOOP
// ════════════════════════════════════════════════════════════════════

void loop() {
    // Handle warm-up phase (first 2 minutes)
    if (!systemState.initialization_complete) {
        handleWarmupPhase();
        // No delay here - handleWarmupPhase already has yield() and delay(100)
        return;
    }
    
    // Main cycle
    static unsigned long lastReadTime = 0;
    static unsigned long lastLCDRefresh = 0;
    unsigned long currentMillis = millis();
    
    // Sensor reading cycle
    if (currentMillis - lastReadTime >= SENSOR_READ_INTERVAL) {
        lastReadTime = currentMillis;
        
        Serial.println("\n" + String('=', 70));
        Serial.println("Reading Sensors & Performing ML Inference...");
        Serial.println(String('=', 70));
        
        // Read all sensor data
        readSensorData();
        printSensorData();
        
        // Perform embedded ML inference
        performEmbeddedMLInference();
        
        // Execute action based on prediction
        executeAction(lastPrediction);
        
        // Log data to LittleFS
        logDataToLittleFS();
        
        printPredictionResults();
    }
    
    // LCD refresh cycle
    if (currentMillis - lastLCDRefresh >= LCD_REFRESH_INTERVAL) {
        lastLCDRefresh = currentMillis;
        updateLCDDisplay();
    }
    
    yield();  // Allow other tasks to run
    delay(100);
}

// ════════════════════════════════════════════════════════════════════
// ████ WEB ROUTES INITIALIZATION
// ════════════════════════════════════════════════════════════════════

String getTimestamp() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        return "2026-04-08 00:00:00 UTC";
    }
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", &timeinfo);
    return String(buffer);
}

void setupWebRoutes() {
    // Time sync endpoint
    server.on("/sync", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("t")) {
            time_t t = (time_t)request->getParam("t")->value().toInt();
            struct timeval tv = { .tv_sec = t };
            settimeofday(&tv, NULL);
            request->send(200, "text/plain", "SUCCESS: MILES Time Synced! Current: " + getTimestamp());
        } else {
            String html = "<html><script>window.location.href='/sync?t=' + Math.floor(Date.now()/1000);</script></html>";
            request->send(200, "text/html", html);
        }
    });

    // Admin panel endpoint
    server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request) {
        String html = "<html><body style='font-family:sans-serif; text-align:center;'>";
        html += "<h2>MILES Admin Panel</h2>";
        html += "<p>Time: " + getTimestamp() + "</p>";
        html += "<p>Status: ";
        html += systemState.initialization_complete ? "RUNNING" : "WARM-UP";
        html += "</p>";
        html += "<a href='/sync'><button style='padding:10px;'>1. SYNC TIME NOW</button></a><br><br>";
        html += "<a href='/data_file'><button style='padding:10px;'>2. DOWNLOAD CSV</button></a><br><br>";
        html += "<a href='/clear' onclick='return confirm(\"Clear all data?\")'><button style='color:red; padding:10px;'>3. CLEAR DATA</button></a>";
        html += "</body></html>";
        request->send(200, "text/html", html);
    });

    // CSV download endpoint
    server.on("/data_file", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/data.csv", "text/csv");
    });

    // Clear data endpoint
    server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request) {
        LittleFS.remove("/data.csv");
        File file = LittleFS.open("/data.csv", FILE_WRITE);
        if (file) {
            file.println("Timestamp,PM25,PM10,MQ2_ppm,MQ7_ppm,Temp,Hum,Confidence,Status");
            file.close();
        }
        systemState.clearTimestamp = millis();
        systemState.isWaitingAfterClear = true;
        request->send(200, "text/plain", "Data Cleared! System will be ready in 2 minutes.");
    });
}

// ════════════════════════════════════════════════════════════════════
// ████ INITIALIZATION FUNCTIONS
// ════════════════════════════════════════════════════════════════════

void initializePins() {
    Serial.println("Initializing GPIO pins...");
    
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(MQ2_PIN, INPUT);
    pinMode(MQ7_PIN, INPUT);
    
    // Turn off all LEDs initially
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    
    Serial.println("✓ GPIO Initialization Complete");
}

void initializeSensors() {
    Serial.println("Initializing sensors...");
    
    // DHT22
    dht.begin();
    delay(500);
    
    // PMS5003 UART
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(500);
    
    Serial.println("✓ Sensor Initialization Complete");
}

// ════════════════════════════════════════════════════════════════════
// ████ WARM-UP PHASE HANDLER
// ════════════════════════════════════════════════════════════════════

void handleWarmupPhase() {
    systemState.warmup_time_remaining = WARMUP_TIME - (millis());
    
    if (systemState.warmup_time_remaining <= 0) {
        Serial.println("\n✓ WARM-UP COMPLETE - ML INFERENCE ACTIVE");
        systemState.initialization_complete = true;
        blinkLED(GREEN_LED, 5);  // Green blinks = ready
        return;
    }
    
    // Read sensors but don't classify yet
    readSensorData();
    
    int remaining_seconds = systemState.warmup_time_remaining / 1000;
    if (remaining_seconds % 10 == 0) {
        Serial.print(".");
    }
    
    // Keep LED yellow during warm-up
    digitalWrite(YELLOW_LED, HIGH);
    
    // CRITICAL: Yield to scheduler to prevent watchdog timeout
    yield();
    delay(100);  // Allow other tasks (async server, WiFi) to run
}

// ════════════════════════════════════════════════════════════════════
// ████ SENSOR READING FUNCTIONS
// ════════════════════════════════════════════════════════════════════

void readSensorData() {
    currentSensorData.timestamp = millis();
    
    // Temperature & Humidity (DHT22)
    currentSensorData.humidity = dht.readHumidity();
    currentSensorData.temperature = dht.readTemperature();
    yield();  // Allow scheduler to run other tasks
    
    if (isnan(currentSensorData.humidity) || isnan(currentSensorData.temperature)) {
        Serial.println("✗ DHT22 Error!");
        currentSensorData.temperature = 25.0;
        currentSensorData.humidity = 50.0;
    }
    
    // Gas Sensor (MQ2)
    currentSensorData.gas = readMQ2Sensor();
    yield();  // Allow scheduler to run other tasks
    
    // CO Sensor (MQ7)
    currentSensorData.co = readMQ7Sensor();
    yield();  // Allow scheduler to run other tasks
    
    // PM2.5 & PM10 (PMS5003)
    readPMS5003();
    
    // Time of day (0-23 hours)
    currentSensorData.time_of_day = (millis() / 3600000) % 24;  // Simplified
}

float readMQ2Sensor() {
    // MQ2: Gas/VOC sensor
    int rawValue = analogRead(MQ2_PIN);
    // Conversion: ADC (0-4095) -> PPM (0-1000)
    float voltage = rawValue * (3.3 / 4095.0);
    float ppm = voltage * 500.0 / 3.3;  // Scale to PPM
    return constrain(ppm, 0, 1000);
}

float readMQ7Sensor() {
    // MQ7: CO sensor
    int rawValue = analogRead(MQ7_PIN);
    // Conversion: ADC (0-4095) -> PPM (0-100)
    float voltage = rawValue * (3.3 / 4095.0);
    float ppm = voltage * 100.0 / 3.3;  // Scale to PPM
    return constrain(ppm, 0, 100);
}

void readPMS5003() {
    // Read PMS5003 (particle sensor) via UART2
    // Format: 42 4D (start) + 28 bytes data
    
    if (Serial2.available()) {
        uint8_t buffer[32];
        uint8_t index = 0;
        unsigned long timeout = millis() + 50;  // Timeout after 50ms to prevent blocking
        
        while (Serial2.available() && index < 32 && millis() < timeout) {
            buffer[index++] = Serial2.read();
            yield();  // Don't starve other tasks
        }
        
        // Parse PM2.5 and PM10 from PMS5003 standard format
        if (index == 32 && buffer[0] == 0x42 && buffer[1] == 0x4D) {
            // Standard particulate matter data
            currentSensorData.pm2_5 = (buffer[10] << 8) | buffer[11];
            currentSensorData.pm10 = (buffer[12] << 8) | buffer[13];
        }
    }
    
    // Fallback values if no data
    if (currentSensorData.pm2_5 == 0 && currentSensorData.pm10 == 0) {
        currentSensorData.pm2_5 = 25.0;
        currentSensorData.pm10 = 50.0;
    }
}

void printSensorData() {
    Serial.println("\n📊 SENSOR READINGS:");
    Serial.println("───────────────────────────────────────────────────────────────");
    Serial.printf("  PM2.5:        %7.1f ug/m3\n", currentSensorData.pm2_5);
    Serial.printf("  PM10:         %7.1f ug/m3\n", currentSensorData.pm10);
    Serial.printf("  Temperature:  %7.1f C\n", currentSensorData.temperature);
    Serial.printf("  Humidity:     %7.1f %%\n", currentSensorData.humidity);
    Serial.printf("  Gas (MQ-2):   %7.1f ppm\n", currentSensorData.gas);
    Serial.printf("  CO (MQ-7):    %7.1f ppm\n", currentSensorData.co);
    Serial.println("───────────────────────────────────────────────────────────────");
}

// ════════════════════════════════════════════════════════════════════
// ████ EMBEDDED ML INFERENCE (NO WiFi!)
// ════════════════════════════════════════════════════════════════════

void performEmbeddedMLInference() {
    Serial.println("\n🤖 PERFORMING EMBEDDED ML INFERENCE...");
    
    // Prepare sensor array in feature order: [PM2.5, PM10, Temp, Humidity, Gas, CO, TimeOfDay]
    float sensor_array[7] = {
        currentSensorData.pm2_5,
        currentSensorData.pm10,
        currentSensorData.temperature,
        currentSensorData.humidity,
        currentSensorData.gas,
        currentSensorData.co,
        (float)currentSensorData.time_of_day
    };
    
    uint32_t start_time = millis();
    
    // Call embedded model prediction (from model.h)
    int prediction = predict(sensor_array);
    float confidence = get_confidence(sensor_array);
    
    uint32_t inference_time = millis() - start_time;
    
    lastPrediction.predicted_class = prediction;
    lastPrediction.confidence = confidence;
    lastPrediction.is_valid = true;
    lastPrediction.inference_time_ms = inference_time;
    
    Serial.printf("  Prediction: Class %d (%s)\n", prediction, CLASS_NAMES[prediction]);
    Serial.printf("  Confidence: %.2f%%\n", confidence * 100);
    Serial.printf("  Inference Time: %lu ms\n", inference_time);
    Serial.println("  Mode: EMBEDDED ML (On-Device, No WiFi)");
}

// ════════════════════════════════════════════════════════════════════
// ████ ACTION EXECUTION
// ════════════════════════════════════════════════════════════════════

void executeAction(ModelPrediction prediction) {
    if (!prediction.is_valid) {
        Serial.println("✗ Invalid prediction - no action taken");
        return;
    }
    
    // Only execute if confidence is high enough
    if (prediction.confidence < CONFIDENCE_THRESHOLD && prediction.predicted_class != 0) {
        Serial.printf("⚠ LOW CONFIDENCE (%.2f%%) - Caution Mode\n", 
                     prediction.confidence * 100);
        setLED(YELLOW_LED);
        digitalWrite(BUZZER_PIN, LOW);
        return;
    }
    
    // Execute response based on ML prediction (NO THRESHOLDS!)
    switch (prediction.predicted_class) {
        case 0:  // SAFE
            handleSafeStatus();
            break;
        case 1:  // CAUTION
            handleCautionStatus();
            break;
        case 2:  // HAZARDOUS
            handleHazardousStatus();
            break;
    }
}

void handleSafeStatus() {
    Serial.println("\n✓ STATUS: SAFE");
    Serial.println("  → Green LED ON");
    Serial.println("  → Buzzer OFF");
    
    setLED(GREEN_LED);
    digitalWrite(BUZZER_PIN, LOW);
}

void handleCautionStatus() {
    Serial.println("\n⚠ STATUS: CAUTION");
    Serial.println("  → Yellow LED ON (pulsing)");
    Serial.println("  → Buzzer: 1 beep per 10 seconds");
    
    blinkLED(YELLOW_LED, 1);
    buzzAlarm(1, 200);  // 1 beep, 200ms
}

void handleHazardousStatus() {
    Serial.println("\n🚨 STATUS: HAZARDOUS - IMMEDIATE ACTION REQUIRED!");
    Serial.println("  → Red LED ON (flashing)");
    Serial.println("  → Buzzer: Continuous alarm");
    Serial.println("  → Recommendation: Evacuate area immediately");
    
    setLED(RED_LED);
    buzzAlarm(0, 0);  // Continuous buzz
}

// ════════════════════════════════════════════════════════════════════
// ████ LED & BUZZER CONTROL
// ════════════════════════════════════════════════════════════════════

void setLED(int pin) {
    // Turn off all LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    
    // Turn on specified LED
    digitalWrite(pin, HIGH);
}

void blinkLED(int pin, int times) {
    for (int i = 0; i < times; i++) {
        digitalWrite(pin, HIGH);
        delay(200);
        digitalWrite(pin, LOW);
        delay(200);
    }
}

void buzzAlarm(int times, int duration) {
    if (times == 0) {
        // Continuous buzz (for hazardous)
        digitalWrite(BUZZER_PIN, HIGH);
    } else {
        // Beep pattern
        for (int i = 0; i < times; i++) {
            digitalWrite(BUZZER_PIN, HIGH);
            delay(duration);
            digitalWrite(BUZZER_PIN, LOW);
            delay(200);
        }
    }
}

// ════════════════════════════════════════════════════════════════════
// ████ LCD DISPLAY & DATA LOGGING FUNCTIONS
// ════════════════════════════════════════════════════════════════════

void updateLCDDisplay() {
    // Check if system is in warm-up or post-clear waiting period
    unsigned long uptimeMinutes = millis() / 60000;
    
    if (!systemState.initialization_complete) {
        // Warm-up phase
        int remaining_seconds = systemState.warmup_time_remaining / 1000;
        int remaining_minutes = remaining_seconds / 60;
        
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("WARM-UP MODE");
        lcd.setCursor(0, 2);
        lcd.print(remaining_minutes);
        lcd.print(" min remaining");
    } else if (systemState.isWaitingAfterClear) {
        // Post-clear waiting period (2 minutes)
        unsigned long timeSinceClear = millis() - systemState.clearTimestamp;
        int remainingMinutes = 2 - (timeSinceClear / 60000);
        
        lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("Data cleared!");
        lcd.setCursor(0, 2);
        lcd.print("Ready in: ");
        lcd.print(remainingMinutes);
        lcd.print("m");
        
        if (remainingMinutes <= 0) {
            systemState.isWaitingAfterClear = false;
        }
    } else {
        // Normal operation - display sensor data
        // Format: 2 columns × 2 rows layout
        // Row 1: PM2.5: 5412    PM10: 489
        // Row 2: MQ2: 58        MQ7: 12
        // Row 3: T: 23.5C       H: 97.1%
        // Row 4: STATUS: Hazardous
        
        lcd.clear();
        
        // Row 1: PM2.5 and PM10
        lcd.setCursor(0, 0);
        lcd.print("PM2.5:");
        lcd.print((int)currentSensorData.pm2_5);
        lcd.setCursor(11, 0);
        lcd.print("PM10:");
        lcd.print((int)currentSensorData.pm10);
        
        // Row 2: MQ2 and MQ7
        lcd.setCursor(0, 1);
        lcd.print("MQ2:");
        lcd.print((int)currentSensorData.gas);
        lcd.setCursor(11, 1);
        lcd.print("MQ7:");
        lcd.print((int)currentSensorData.co);
        
        // Row 3: Temperature and Humidity
        lcd.setCursor(0, 2);
        lcd.print("T:");
        lcd.print(currentSensorData.temperature, 1);
        lcd.print("C");
        lcd.setCursor(11, 2);
        lcd.print("H:");
        lcd.print(currentSensorData.humidity, 1);
        lcd.print("%");
        
        // Row 4: Status and Confidence
        lcd.setCursor(0, 3);
        lcd.print("STATUS: ");
        lcd.print(CLASS_NAMES[lastPrediction.predicted_class]);
    }
}

void logDataToLittleFS() {
    // Only log if initialization complete and not in waiting period
    unsigned long uptimeMinutes = millis() / 60000;
    
    if (!systemState.initialization_complete) {
        return;  // Don't log during warm-up
    }
    
    if (systemState.isWaitingAfterClear) {
        return;  // Don't log while waiting after clear
    }
    
    // Build CSV row: Timestamp,PM25,PM10,MQ2_ppm,MQ7_ppm,Temp,Hum,Confidence,Status
    String dataRow = getTimestamp() + "," + 
                     String((int)currentSensorData.pm2_5) + "," + 
                     String((int)currentSensorData.pm10) + "," + 
                     String(currentSensorData.gas, 1) + "," + 
                     String(currentSensorData.co, 1) + "," + 
                     String(currentSensorData.temperature, 1) + "," + 
                     String(currentSensorData.humidity, 1) + "," +
                     String(lastPrediction.confidence * 100, 1) + "," +
                     CLASS_NAMES[lastPrediction.predicted_class] + "\n";
    
    File file = LittleFS.open("/data.csv", FILE_APPEND);
    if (file) {
        file.print(dataRow);
        file.close();
        Serial.println("✓ Data logged to LittleFS");
    } else {
        Serial.println("✗ Failed to open CSV file");
    }
}

// ════════════════════════════════════════════════════════════════════
// ████ UTILITY FUNCTIONS
// ════════════════════════════════════════════════════════════════════

void printPredictionResults() {
    Serial.println("\n" + String('=', 70));
    Serial.println("FINAL PREDICTION:");
    Serial.println(String('=', 70));
    Serial.printf("  Class: %d (%s)\n", 
                 lastPrediction.predicted_class, 
                 CLASS_NAMES[lastPrediction.predicted_class]);
    Serial.printf("  Confidence: %.2f%%\n", lastPrediction.confidence * 100);
    Serial.printf("  Inference Time: %lu ms\n", lastPrediction.inference_time_ms);
    Serial.println("  Architecture: EMBEDDED ML (No WiFi Dependency)");
    Serial.println("  Model: 200 Random Forest Trees, 99.98% Accuracy");
    Serial.println(String('=', 70) + "\n");
}

// ════════════════════════════════════════════════════════════════════
// ████ END OF FILE
// ════════════════════════════════════════════════════════════════════
