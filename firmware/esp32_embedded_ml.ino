/*
 * ══════════════════════════════════════════════════════════════════════
 * MILES DATA STATION - INTEGRATED FIRMWARE (ESP32-S3)
 * ══════════════════════════════════════════════════════════════════════
 */

#include "model.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <time.h>
#include <esp_system.h>

// ════════════ CONFIGURATION ════════════
const char* ap_ssid = "MILES_Data_Station";
const char* ap_password = "password123";

const int SENSOR_READ_INTERVAL = 30000;
const int WARMUP_TIME = 120000;
const int LCD_REFRESH_INTERVAL = 10000;
const int CAUTION_BEEP_DURATION_MS = 100;

// ════════════ PIN DEFINITIONS (FIREBEETLE 2 S3) ════════════
#define MQ2_PIN 1         // A0 - Gas Sensor
#define MQ7_PIN 2         // A1 - CO Sensor
#define DHTPIN 4          // D2 - Temp/Humid
#define BUZZER_PIN 48     // D6 - Alarm
#define GREEN_LED 5       // D10 - Safe
#define YELLOW_LED 6      // D11 - Caution
#define RED_LED 8         // D12 - Hazardous
#define RXD2 44           // PMS5003 RX
#define TXD2 43           // PMS5003 TX
#define DHTTYPE DHT22

// ════════════ GLOBAL OBJECTS ════════════
DHT dht(DHTPIN, DHTTYPE);
AsyncWebServer server(80);
LiquidCrystal_I2C lcd(0x27, 20, 4);

struct SensorData {
    float pm2_5, pm10, temperature, humidity, gas, co;
} currentSensorData;

struct ModelPrediction {
    int predicted_class;
    float confidence;
} lastPrediction;

const char* CLASS_NAMES[] = {"SAFE", "CAUTION", "HAZARDOUS"};

// Track timing
unsigned long lastLCDUpdate = 0;
unsigned long lastSensorRead = 0;
bool systemReady = false;
unsigned long warmupStart = 0;
unsigned long cautionBeepStart = 0;
bool cautionBeepActive = false;

// Circular buffer for data storage in PSRAM
#define MAX_RECORDS 500  // Reduced for stability
struct DataRecord {
    char timestamp[32];
    float pm2_5, pm10, gas, co, temp, hum, confidence;
    int status;
};

DataRecord* dataRecords = nullptr;
int recordCount = 0;
int currentRecord = 0;
bool bufferFull = false;

// ════════════ HTML ADMIN PANEL (PROGMEM) ════════════
const char INDEX_HTML[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html><head><meta charset="UTF-8"><meta name="viewport" content="width=device-width, initial-scale=1">
<title>MILES Admin Panel</title><style>
body { font-family: sans-serif; text-align: center; padding: 20px; background: #f0f0f0; }
.container { max-width: 400px; margin: 0 auto; background: white; padding: 20px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
button { width: 100%; padding: 15px; margin: 10px 0; font-size: 16px; cursor: pointer; border: none; border-radius: 5px; transition: 0.2s; }
button:active { transform: scale(0.98); }
.blue { background: #3498db; color: white; } .green { background: #2ecc71; color: white; } .red { background: #e74c3c; color: white; }
.info { background: #ecf0f1; padding: 10px; border-radius: 5px; margin: 10px 0; text-align: left; }
</style></head><body><div class="container"><h2>🌫️ MILES Admin</h2>
<div class="info"><p>📅 Time: <span id="time">--</span></p><p>📊 Records: <span id="records">--</span></p><p>📱 Clients: <span id="clients">--</span></p></div>
<button class="blue" onclick="syncTime()">🕐 SYNC TIME</button>
<button class="green" onclick="downloadCSV()">📥 DOWNLOAD DATA</button>
<button class="red" onclick="if(confirm('Clear all data?')) clearData()">🗑️ CLEAR DATA</button>
</div><script>
function syncTime() { 
    fetch('/sync?t='+Math.floor(Date.now()/1000))
        .then(()=>alert('Time synced!'))
        .catch(err=>alert('Sync failed: '+err));
}
function downloadCSV() { 
    window.location.href='/data_fast'; 
}
function clearData() { 
    fetch('/clear')
        .then(()=>alert('Data cleared!'))
        .catch(err=>alert('Clear failed: '+err));
}
setInterval(()=>{ fetch('/time').then(r=>r.text()).then(t=>document.getElementById('time').innerText=t).catch(e=>console.log(e)); }, 5000);
setInterval(()=>{ fetch('/record_count').then(r=>r.text()).then(c=>document.getElementById('records').innerText=c).catch(e=>console.log(e)); }, 10000);
setInterval(()=>{ fetch('/client_count').then(r=>r.text()).then(c=>document.getElementById('clients').innerText=c).catch(e=>console.log(e)); }, 3000);
</script></body></html>)rawliteral";

// ════════════ UTILITIES ════════════
const char* getTimestampSafe() {
    static char buffer[32];
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        snprintf(buffer, sizeof(buffer), "2026-04-11 00:00:00 UTC");
    } else {
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S UTC", &timeinfo);
    }
    return buffer;
}

int getRecordCount() {
    return bufferFull ? MAX_RECORDS : recordCount;
}

void logHeapStats(const char* tag) {
    Serial.printf("[HEAP] %s free=%u min=%u maxAlloc=%u\n",
                  tag,
                  ESP.getFreeHeap(),
                  ESP.getMinFreeHeap(),
                  ESP.getMaxAllocHeap());
}

DataRecord* getRecordByLogicalIndex(int i) {
    if (bufferFull) {
        int idx = (i + currentRecord) % MAX_RECORDS;
        return &dataRecords[idx];
    }
    return &dataRecords[i];
}

void sendCsvDownload(AsyncWebServerRequest *request, int startRecord, int totalRecords) {
    AsyncResponseStream *response = request->beginResponseStream("text/csv");
    response->addHeader("Content-Disposition", "attachment; filename=miles_data.csv");
    response->print("Timestamp,PM25,PM10,MQ2_ppm,MQ7_ppm,Temp,Hum,Confidence,Status\n");

    for (int i = startRecord; i < totalRecords; i++) {
        DataRecord* rec = getRecordByLogicalIndex(i);
        response->printf("%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%s\n",
                         rec->timestamp,
                         rec->pm2_5, rec->pm10,
                         rec->gas, rec->co,
                         rec->temp, rec->hum,
                         rec->confidence,
                         CLASS_NAMES[rec->status]);

        if (i % 20 == 0) {
            yield();
        }
    }

    request->send(response);
}

void serviceBuzzer(unsigned long nowMillis) {
    if (cautionBeepActive && (nowMillis - cautionBeepStart >= CAUTION_BEEP_DURATION_MS)) {
        digitalWrite(BUZZER_PIN, LOW);
        cautionBeepActive = false;
    }
}

// ════════════ WEB ROUTES ════════════
void setupWebRoutes() {
    server.on("/download", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/html", INDEX_HTML);
    });
    
    server.on("/time", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", getTimestampSafe());
    });
    
    server.on("/record_count", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(getRecordCount()));
    });
    
    server.on("/client_count", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", String(WiFi.softAPgetStationNum()));
    });
    
    // Fast download - last 100 records only (safe and fast)
    server.on("/data_fast", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (recordCount == 0 && !bufferFull) {
            request->send(404, "text/plain", "No data available");
            return;
        }

        int totalRecords = bufferFull ? MAX_RECORDS : recordCount;
        int startRecord = (totalRecords > 100) ? totalRecords - 100 : 0;

        logHeapStats("before /data_fast");
        sendCsvDownload(request, startRecord, totalRecords);
        logHeapStats("after /data_fast");
    });
    
    // Full download - use with caution (may timeout)
    server.on("/data_full", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (recordCount == 0 && !bufferFull) {
            request->send(404, "text/plain", "No data available");
            return;
        }

        int totalRecords = bufferFull ? MAX_RECORDS : recordCount;

        logHeapStats("before /data_full");
        sendCsvDownload(request, 0, totalRecords);
        logHeapStats("after /data_full");
    });
    
    server.on("/sync", HTTP_GET, [](AsyncWebServerRequest *request) {
        if (request->hasParam("t")) {
            time_t t = (time_t)request->getParam("t")->value().toInt();
            struct timeval tv = { .tv_sec = t };
            settimeofday(&tv, NULL);
            request->send(200, "text/plain", "Time Synced!");
        } else {
            String redirect = "<script>location.href='/sync?t='+Math.floor(Date.now()/1000);</script>";
            request->send(200, "text/html", redirect);
        }
    });
    
    server.on("/clear", HTTP_GET, [](AsyncWebServerRequest *request) {
        recordCount = 0;
        currentRecord = 0;
        bufferFull = false;
        if (dataRecords) {
            memset(dataRecords, 0, sizeof(DataRecord) * MAX_RECORDS);
        }
        request->send(200, "text/plain", "Data Cleared!");
    });
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { 
        request->redirect("/download"); 
    });
}

// ════════════ READ SENSORS ════════════
void readSensors() {
    // Read DHT22 with retry
    int retryCount = 0;
    bool dhtSuccess = false;
    
    while (retryCount < 3 && !dhtSuccess) {
        currentSensorData.humidity = dht.readHumidity();
        currentSensorData.temperature = dht.readTemperature();
        
        if (!isnan(currentSensorData.humidity) && !isnan(currentSensorData.temperature)) {
            dhtSuccess = true;
        } else {
            retryCount++;
            delay(50);
            yield();
        }
    }
    
    if (!dhtSuccess) {
        currentSensorData.temperature = 25.0;
        currentSensorData.humidity = 50.0;
    }
    
    // Read MQ2 (Gas)
    int mq2Raw = analogRead(MQ2_PIN);
    float mq2Voltage = mq2Raw * (3.3 / 4095.0);
    currentSensorData.gas = constrain(mq2Voltage * 500.0 / 3.3, 0, 1000);
    
    // Read MQ7 (CO)
    int mq7Raw = analogRead(MQ7_PIN);
    float mq7Voltage = mq7Raw * (3.3 / 4095.0);
    currentSensorData.co = constrain(mq7Voltage * 100.0 / 3.3, 0, 100);
    
    // Read PMS5003
    bool pmsSuccess = false;
    if (Serial2.available() >= 32) {
        uint8_t buf[32];
        Serial2.readBytes(buf, 32);
        if (buf[0] == 0x42 && buf[1] == 0x4D) {
            currentSensorData.pm2_5 = (buf[10] << 8) | buf[11];
            currentSensorData.pm10 = (buf[12] << 8) | buf[13];
            pmsSuccess = true;
        }
    }
    
    if (!pmsSuccess) {
        currentSensorData.pm2_5 = 25.0;
        currentSensorData.pm10 = 50.0;
    }
}

// ════════════ UPDATE LEDS AND BUZZER ════════════
void updateOutputs() {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
    
    if (lastPrediction.predicted_class == 0) {
        cautionBeepActive = false;
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(GREEN_LED, HIGH);
    } else if (lastPrediction.predicted_class == 1) {
        digitalWrite(YELLOW_LED, HIGH);
        if (!cautionBeepActive) {
            cautionBeepStart = millis();
            cautionBeepActive = true;
            digitalWrite(BUZZER_PIN, HIGH);
        }
    } else if (lastPrediction.predicted_class == 2) {
        cautionBeepActive = false;
        digitalWrite(RED_LED, HIGH);
        digitalWrite(BUZZER_PIN, HIGH);
    }
}

// ════════════ UPDATE LCD ════════════
void updateLCD() {
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("P2.5:");
    lcd.print((int)currentSensorData.pm2_5);
    lcd.setCursor(11, 0);
    lcd.print("P10:");
    lcd.print((int)currentSensorData.pm10);
    
    lcd.setCursor(0, 1);
    lcd.print("MQ2:");
    lcd.print((int)currentSensorData.gas);
    lcd.setCursor(11, 1);
    lcd.print("CO:");
    lcd.print((int)currentSensorData.co);
    
    lcd.setCursor(0, 2);
    lcd.print("T:");
    lcd.print(currentSensorData.temperature, 1);
    lcd.print("C");
    lcd.setCursor(11, 2);
    lcd.print("H:");
    lcd.print(currentSensorData.humidity, 1);
    lcd.print("%");
    
    lcd.setCursor(0, 3);
    lcd.print(CLASS_NAMES[lastPrediction.predicted_class]);
    
    if (WiFi.softAPgetStationNum() > 0) {
        lcd.setCursor(12, 3);
        lcd.print("📱");
    }
}

// ════════════ LOG DATA (CIRCULAR BUFFER IN PSRAM) ════════════
void logData() {
    if (dataRecords == nullptr) return;
    
    // Don't log if client connected
    if (WiFi.softAPgetStationNum() > 0) {
        return;
    }
    
    DataRecord* rec = &dataRecords[currentRecord];
    
    // Store timestamp
    strncpy(rec->timestamp, getTimestampSafe(), sizeof(rec->timestamp) - 1);
    rec->timestamp[sizeof(rec->timestamp) - 1] = '\0';
    
    // Store sensor data
    rec->pm2_5 = currentSensorData.pm2_5;
    rec->pm10 = currentSensorData.pm10;
    rec->gas = currentSensorData.gas;
    rec->co = currentSensorData.co;
    rec->temp = currentSensorData.temperature;
    rec->hum = currentSensorData.humidity;
    rec->confidence = lastPrediction.confidence * 100;
    rec->status = lastPrediction.predicted_class;
    
    // Move to next record
    currentRecord++;
    if (currentRecord >= MAX_RECORDS) {
        currentRecord = 0;
        bufferFull = true;
    }
    
    if (!bufferFull) {
        recordCount++;
    } else {
        recordCount = MAX_RECORDS;
    }
}

// ════════════ SETUP ════════════
void setup() {
    Serial.begin(115200);
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
    delay(1000);

    Serial.printf("Reset reason: %d\n", (int)esp_reset_reason());
    logHeapStats("boot");
    
    Serial.println("\n╔════════════════════════════════════════════════════════════╗");
    Serial.println("║  MILES DATA STATION - AIR QUALITY MONITOR                 ║");
    Serial.println("║  Board: ESP32-S3 (FireBeetle 2)                           ║");
    Serial.println("╚════════════════════════════════════════════════════════════╝\n");
    
    // Initialize pins
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(MQ2_PIN, INPUT);
    pinMode(MQ7_PIN, INPUT);
    
    // Turn off all LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    
    // Blink sequence to show boot
    for (int i = 0; i < 2; i++) {
        digitalWrite(YELLOW_LED, HIGH);
        delay(200);
        digitalWrite(YELLOW_LED, LOW);
        delay(200);
    }
    
    // Allocate PSRAM for circular buffer
    Serial.print("Allocating PSRAM for data buffer... ");
    dataRecords = (DataRecord*)ps_calloc(MAX_RECORDS, sizeof(DataRecord));
    if (dataRecords) {
        Serial.printf("✓ %d records allocated (%d bytes)\n", MAX_RECORDS, MAX_RECORDS * (int)sizeof(DataRecord));
    } else {
        Serial.println("✗ FAILED! Using limited memory mode");
    }
    
    // Initialize DHT
    Serial.print("Initializing DHT22... ");
    dht.begin();
    delay(500);
    Serial.println("✓ DONE");
    
    // Initialize LCD
    Serial.print("Initializing LCD... ");
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("MILES Data Station");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");
    Serial.println("✓ DONE");
    
    // Check PSRAM
    Serial.print("Checking PSRAM... ");
    if (psramFound()) {
        Serial.printf("✓ %d bytes available\n", ESP.getPsramSize());
        lcd.setCursor(0, 2);
        lcd.print("PSRAM: OK");
    } else {
        Serial.println("⚠ PSRAM not found");
        lcd.setCursor(0, 2);
        lcd.print("PSRAM: NOT FOUND");
    }
    
    // Setup WiFi Access Point
    Serial.print("Starting WiFi AP... ");
    WiFi.softAP(ap_ssid, ap_password);
    Serial.println("✓ DONE");
    Serial.print("  IP Address: ");
    Serial.println(WiFi.softAPIP());
    
    lcd.setCursor(0, 2);
    lcd.print("WiFi: ");
    lcd.print(WiFi.softAPIP());
    
    // Setup web server
    setupWebRoutes();
    server.begin();
    Serial.println("✓ Web server started");
    
    lcd.setCursor(0, 3);
    lcd.print("Ready!");
    delay(2000);
    lcd.clear();
    
    warmupStart = millis();
    
    Serial.println("\n───────────────────────────────────────────────────────────────");
    Serial.println("✓ SYSTEM READY - Warming up sensors for 2 minutes");
    Serial.print("✓ Access admin panel: http://");
    Serial.println(WiFi.softAPIP());
    Serial.println("  Use /data_fast for quick downloads (last 100 records)");
    Serial.println("  Use /data_full for all records (may take longer)");
    Serial.println("───────────────────────────────────────────────────────────────\n");
}

// ════════════ MAIN LOOP ════════════
void loop() {
    unsigned long currentMillis = millis();
    serviceBuzzer(currentMillis);
    
    // Handle warm-up phase (2 minutes)
    if (!systemReady) {
        if (currentMillis - warmupStart < WARMUP_TIME) {
            int remaining = (WARMUP_TIME - (currentMillis - warmupStart)) / 1000;
            
            static unsigned long lastWarmupLCD = 0;
            if (currentMillis - lastWarmupLCD > 5000) {
                lastWarmupLCD = currentMillis;
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("WARMING UP");
                lcd.setCursor(0, 1);
                lcd.print("Time left:");
                lcd.setCursor(0, 2);
                lcd.print(remaining / 60);
                lcd.print("m ");
                lcd.print(remaining % 60);
                lcd.print("s");
                lcd.setCursor(0, 3);
                lcd.print("AP: ");
                lcd.print(WiFi.softAPIP());
            }
            
            static unsigned long lastBlink = 0;
            if (currentMillis - lastBlink > 1000) {
                digitalWrite(YELLOW_LED, !digitalRead(YELLOW_LED));
                lastBlink = currentMillis;
            }
            
            delay(10);
            return;
        } else {
            systemReady = true;
            digitalWrite(YELLOW_LED, LOW);
            lcd.clear();
            Serial.println("\n✓ WARM-UP COMPLETE - SYSTEM ACTIVE\n");
        }
    }
    
    // Sensor reading cycle (every 30 seconds)
    if (currentMillis - lastSensorRead >= SENSOR_READ_INTERVAL) {
        lastSensorRead = currentMillis;
        
        Serial.println("───────────────────────────────────────────────────────────────");
        Serial.println("📊 READING SENSORS");
        
        readSensors();
        
        Serial.printf("  PM2.5: %.1f ug/m3 | PM10: %.1f ug/m3\n", 
                      currentSensorData.pm2_5, currentSensorData.pm10);
        Serial.printf("  Temp: %.1f C | Humidity: %.1f %%\n", 
                      currentSensorData.temperature, currentSensorData.humidity);
        Serial.printf("  Gas: %.1f ppm | CO: %.1f ppm\n", 
                      currentSensorData.gas, currentSensorData.co);
        
        // Run ML inference
        float input[7] = {
            currentSensorData.pm2_5,
            currentSensorData.pm10,
            currentSensorData.temperature,
            currentSensorData.humidity,
            currentSensorData.gas,
            currentSensorData.co,
            12.0
        };
        
        uint32_t startTime = millis();
        lastPrediction.predicted_class = predict(input);
        lastPrediction.confidence = get_confidence(input);
        uint32_t inferenceTime = millis() - startTime;
        
        Serial.printf("  🤖 Prediction: %s (%.1f%%) [%d ms]\n", 
                      CLASS_NAMES[lastPrediction.predicted_class],
                      lastPrediction.confidence * 100, inferenceTime);
        
        updateOutputs();
        logData();
        
        Serial.printf("  💾 Total records: %d\n", getRecordCount());
        Serial.println("───────────────────────────────────────────────────────────────");
    }
    
    // LCD refresh cycle (every 10 seconds)
    if (currentMillis - lastLCDUpdate >= LCD_REFRESH_INTERVAL) {
        lastLCDUpdate = currentMillis;
        updateLCD();
    }
    
    delay(10);
}
