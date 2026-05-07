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
const unsigned long WIFI_RETRY_MS = 15000;
const unsigned long BLYNK_RETRY_MS = 5000;
const unsigned long WARMUP_MS = 120000;

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

void manageConnections() {
    unsigned long now = millis();

    if (WiFi.status() != WL_CONNECTED) {
        if (now - lastWifiAttempt >= WIFI_RETRY_MS) {
            lastWifiAttempt = now;
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid, pass);
        }
        return;
    }

    if (!blynkConfigured) {
        Blynk.config(BLYNK_AUTH_TOKEN);
        blynkConfigured = true;
    }

    if (!Blynk.connected() && now - lastBlynkAttempt >= BLYNK_RETRY_MS) {
        lastBlynkAttempt = now;
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

void processDecisions(int cls, float pm25, float pm10, float co, float gas, float hum, float temp) {
    float Tw = temp * atan(0.151977 * pow(hum + 8.313659, 0.5)) + atan(temp + hum) - atan(hum - 1.676331) + 0.00391838 * pow(hum, 1.5) * atan(0.023101 * hum) - 4.686035;

    bool isPm25Haz = (pm25 > 100.0);
    bool isPm10Haz = (pm10 > 230.0);
    bool isGasHaz = (gas >= 176.0);
    bool isCoHaz = (co > 30.0);

    bool isPm25Cau = (pm25 >= 51.0);
    bool isPm10Cau = (pm10 >= 151.0);
    bool isGasCau = (gas >= 131.0);
    bool isCoCau = (co >= 10.0);

    int cautionCount = isPm25Cau + isPm10Cau + isGasCau + isCoCau;
    int hazardCount = isPm25Haz + isPm10Haz + isGasHaz + isCoHaz;

    if (Tw > 30.0 || hazardCount >= 1) {
        cls = 2;
    } else if (cautionCount >= 1 && cls == 0) {
        cls = 1;
    }

    if (hum >= 95.0 && gas <= 130.0 && Tw <= 35.0) {
        cls = 0;
    }

    String status = "";
    String note = "";

    if (Tw > 35.0) {
        status = "HAZARDOUS: EVACUATE TO COOLING AREA NOW";
        note = "Extreme heat is life-threatening.";
    } else if (cls == 2) {
        if (Tw > 30.0) { status = "HAZARDOUS: STOP NON-ESSENTIAL PHYSICAL WORK"; note = "Heat stress critical."; }
        else if (hazardCount >= 3) { status = "HAZARDOUS: EXECUTE FULL EMERGENCY PROTOCOL"; note = "Multi-sensor trigger."; }
        else if (isGasHaz && isCoHaz) { status = "HAZARDOUS: EVACUATE AFFECTED ZONE NOW"; note = "Gas and CO critical."; }
        else if (isPm25Haz && isCoHaz) { status = "HAZARDOUS: TREAT AS FIRE RISK NOW"; note = "PM2.5 and CO critical."; }
        else if (isPm25Haz && isGasHaz) { status = "HAZARDOUS: CHECK COMBUSTION AND PREPARE EVACUATION"; note = "PM2.5 and Gas critical."; }
        else if (isPm25Haz && isPm10Haz) { status = "HAZARDOUS: ENFORCE RESPIRATORS IMMEDIATELY"; note = "PM2.5 and PM10 critical."; }
        else if (isCoHaz) { status = "HAZARDOUS: MOVE UPWIND IMMEDIATELY"; note = "CO hazardous."; }
        else if (isGasHaz) { status = "HAZARDOUS: STOP IGNITION ACTIVITIES NOW"; note = "Gas hazardous."; }
        else if (isPm10Haz) { status = "HAZARDOUS: ACTIVATE DUST SUPPRESSION NOW"; note = "PM10 hazardous."; }
        else if (isPm25Haz) { status = "HAZARDOUS: STOP DUST WORK NOW"; note = "PM2.5 hazardous."; }
        else { status = "HAZARDOUS: PAUSE OPERATIONS UNTIL STABLE"; note = "Hazard detected."; }
    } else if (cls == 1) {
        if (Tw >= 27.0 && Tw <= 30.0 && cautionCount == 0) { status = "CAUTION: SLOW WORK AND HYDRATE"; note = "Heat stress rising."; }
        else if (cautionCount >= 3) { status = "CAUTION: ACTIVATE PROTECTIVE PROTOCOL"; note = "Multi-sensor caution."; }
        else if (isPm10Cau && isCoCau) { status = "CAUTION: START FIRE-SOURCE CHECK"; note = "PM10 and CO caution."; }
        else if (isPm10Cau && isGasCau) { status = "CAUTION: PREPARE RESPIRATORY PROTECTION"; note = "PM10 and Gas caution."; }
        else if (isCoCau) { status = "CAUTION: MOVE TO CLEANER AIR ZONE"; note = "CO caution."; }
        else if (isGasCau) { status = "CAUTION: CHECK COMBUSTION SOURCES NOW"; note = "Gas caution."; }
        else if (isPm10Cau) { status = "CAUTION: IMPROVE VENTILATION NOW"; note = "PM10 caution."; }
        else if (isPm25Cau) { status = "CAUTION: REDUCE DUST EXPOSURE NOW"; note = "PM2.5 caution."; }
        else { status = "CAUTION: APPLY PPE AND REASSESS"; note = "Caution detected."; }
    } else {
        if (hum >= 95.0 && gas <= 130.0) {
            status = "SAFE: CONTINUE WORK, NO EVACUATION";
            note = "Extreme PM with extreme humidity indicates mist.";
        } else if (hum > 70.0) {
            status = "SAFE: CONTINUE TASKS WITH HYDRATION";
            note = "Elevated humidity alone is not a pollutant hazard.";
        } else {
            status = "SAFE: CONTINUE OPERATIONS";
            note = "All sensors normal.";
        }
    }

    lcdRemark = status;
    blynkFullRemark = "REMARKS: " + status + "\n\nNote: " + note;
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

    lcd.clear(); lcd.setCursor(0, 0); lcd.print("CHECKING SD CARD...");
    while (!SD.begin(SD_CS)) {
        lcd.setCursor(0, 1); lcd.print("SD CARD: NOT FOUND");
        delay(1000);
    }

    int fileNum = 1;
    while (SD.exists("/MILES_S" + String(fileNum) + ".csv")) fileNum++;
    fileName = "/MILES_S" + String(fileNum) + ".csv";

    File file = SD.open(fileName, FILE_WRITE);
    if (file) {
        file.println("Timestamp,PM2.5,PM10,Temp,Hum,Gas,CO,Class,Remark");
        file.close();
    }

    lcd.clear(); lcd.setCursor(0, 0); lcd.print("CONNECTING WIFI...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    lastWifiAttempt = millis();
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
        data.gas = ((analogRead(MQ2_PIN) / 4095.0) * 1000.0) - 400.0;
        if (data.gas < 30.0) data.gas = 30.0;
        data.co = ((analogRead(MQ7_PIN) / 4095.0) * 100.0) - 40.0;
        if (data.co < 2.0) data.co = 2.0;

        float pm25Read = 0.0, pm10Read = 0.0;
        if (readPMS7003Frame(pm25Read, pm10Read, 1200)) {
            data.pm2_5 = pm25Read;
            data.pm10 = pm10Read;
            hasValidPM = true;
        } else if (!hasValidPM) {
            data.pm2_5 = 0.0;
            data.pm10 = 0.0;
        }

        float input[7] = {data.pm2_5, data.pm10, data.temp, data.hum, data.gas, data.co, 12.0};
        lastClass = predict(input);
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

        File file = SD.open(fileName, FILE_APPEND);
        if (file) {
            file.printf("%s,%.1f,%.1f,%.1f,%.1f,%.1f,%.1f,%d,%s\n",
                        reading.timestamp.c_str(), reading.pm2_5, reading.pm10, reading.temp, reading.hum, reading.gas, reading.co, reading.cls, reading.remark.c_str());
            file.close();
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
        lcd.setCursor(0, 1); lcd.print("GAS:"); lcd.print((int)data.gas); lcd.print("  ");
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
