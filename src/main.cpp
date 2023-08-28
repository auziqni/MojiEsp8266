#include <Arduino.h>
#include "DHTesp.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h> //menggunakan library wifi
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>

static const int Device_Id = 100;

static const int DhtPin = 16;            // D0
static const int RXPin = 14, TXPin = 12; // D5,D6
static const int potentioPin = 0;
static const int buzzer = 2;

static const uint32_t GPSBaud = 9600;
DHTesp dht;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const char *ssid = "moji";
const char *password = "12345678";
const uint8_t fingerprint[20] = {0xFF, 0xB9, 0xE3, 0xB5, 0x5B, 0x5C, 0xE6, 0xF4, 0xAC, 0x94, 0x77, 0x98, 0xD9, 0xB6, 0xE0, 0x97, 0x60, 0xA8, 0xC2, 0x88};

float latitude, longitude;
float temperature, humidity;
int potenRead = 0, potenReadPrev = 0;
String jsonReqPayload, responsePayload;
float distToAdmin;

int lastmillis = 0, nowmillis = 0;
int timeCountToPush;
bool gpsReady, dhtReady;
bool spottedError[5] = {false}; // doc error 0=>wifi; 1=>gps; 2=>dht;

void getDataSensor()
{
    potenRead = analogRead(potentioPin);

    if (potenRead > 100)
    {
        int diffrence = abs(potenRead - potenReadPrev);
        if (potenRead > 100 && diffrence > 10)
        {
            latitude = -50 + (potenRead * 120 / 1024);
            longitude = -60 + (potenRead * 160 / 1024);
            potenReadPrev = potenRead;
        }
    }
    else
    {
        while (ss.available() > 0)
        {
            byte gpsData = ss.read();
            Serial.write(gpsData);

            gps.encode(gpsData);
            if (gps.location.isValid())
            {
                latitude = gps.location.lat();
                longitude = gps.location.lng();
                gpsReady = true;
                spottedError[1] = false;
            }
            else
            {
                spottedError[1] = true;
            }
        }
    }

    if (nowmillis - lastmillis > dht.getMinimumSamplingPeriod())
    {
        humidity = dht.getHumidity();
        temperature = dht.getTemperature();
        dhtReady = true;
    }
}

void timer()
{
    nowmillis = millis(); // Timer
    if (nowmillis - lastmillis > 10000)
    {
        lastmillis = nowmillis;
        if (timeCountToPush > 5) // todo: make it 10
        {
            timeCountToPush = 0;
        }
        else
        {
            timeCountToPush++;
        }
    }
}

void buzzering()
{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   PERINGATAN!  ");
    lcd.setCursor(0, 1);
    lcd.print("  TERLALU JAUH  ");
    delay(1000);
    lcd.setCursor(0, 1);
    lcd.print("Jarak:  ");
    lcd.setCursor(6, 1);
    lcd.print(distToAdmin);
    for (size_t i = 0; i < 3; i++)
    {
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        delay(1000);
    }
}

void lcdPrint()
{
    bool foundError = false; // Untuk menandai apakah ada nilai true dalam array

    // Mengecek apakah ada nilai true dalam array
    for (int i = 0; i < 5; ++i)
    {
        if (spottedError[i])
        {
            foundError = true;
            break;
        }

        if (foundError)
        {
            // todo error
            lcd.setCursor(0, 0);
            lcd.print("error           ");
            lcd.setCursor(0, 1);
            lcd.print("error           ");
        }
        else
        {
            if ((nowmillis - lastmillis) % 5000 > 2500)
            {
                lcd.setCursor(0, 0);
                lcd.print("temp  :     ");
                lcd.setCursor(12, 0);
                lcd.print(temperature);
                lcd.setCursor(0, 1);
                lcd.print("humid :     ");
                lcd.setCursor(12, 1);
                lcd.print(humidity);
            }
            else
            {
                lcd.setCursor(0, 0);
                lcd.print("lat:   ");
                lcd.setCursor(7, 0);
                lcd.print(latitude, 6);
                lcd.setCursor(0, 1);
                lcd.print("lng:  ");
                lcd.setCursor(6, 1);
                lcd.print(longitude, 6);
            }
        }
    }
}

void serialPrint()
{
    if ((nowmillis - lastmillis) % 1000 == 0)
    {
        Serial.print(timeCountToPush);
        Serial.print(" ");
        Serial.print(lastmillis);
        Serial.print("\t");
        Serial.print(nowmillis);
        Serial.print("\t");

        Serial.print(gpsReady);
        Serial.print(" ");
        Serial.print(dhtReady);
        Serial.print("\t");
        for (int i = 0; i < 5; ++i)
        {
            Serial.print(spottedError[i]);
        }
        Serial.println("");

        Serial.print(potenRead);
        Serial.print("\t");
        Serial.print(latitude, 6);
        Serial.print("\t");
        Serial.print(longitude, 6);
        Serial.print("\t");
        Serial.print(temperature);
        Serial.print("\t");
        Serial.println(humidity);
        Serial.println("");
    }
}

void wifiCon()
{
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    lcd.setCursor(0, 0);
    lcd.print("  MENGHUBUGKAN  ");
    lcd.setCursor(0, 1);
    lcd.print("    KE WIFI     ");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }

    Serial.println(""); // connected
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    lcd.setCursor(0, 0);
    lcd.print("    TERHUBUNG   ");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
    delay(1000);
    lcd.clear();
}

void pushData(int d_id, float d_lat, float d_lng, float d_temp, float d_humid)
{
    lcd.setCursor(0, 0);
    lcd.print("    MEMPROSES   ");
    lcd.setCursor(0, 1);
    lcd.print("   KIRIM DATA   ");

    jsonReqPayload = "";
    StaticJsonDocument<200> D2W;

    D2W["id"] = d_id;
    D2W["lat"] = d_lat;
    D2W["lng"] = d_lng;
    D2W["temp"] = d_temp;
    D2W["humid"] = d_humid;

    serializeJson(D2W, jsonReqPayload);
    Serial.println(jsonReqPayload);

    HTTPClient http;
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setFingerprint(fingerprint);

    http.begin(*client, "https://www.moji.my.id/api/updatejamaahloc");
    http.setTimeout(10000);
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    http.addHeader("Content-Type", "application/json; charset=UTF-8");

    int httpResponseCode = http.POST(jsonReqPayload);
    Serial.print("respon :");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0)
    {
        if (httpResponseCode == 200)
        {
            responsePayload = http.getString();
            Serial.println("Data recive:");
            Serial.println(responsePayload);

            DynamicJsonDocument doc(1024);
            deserializeJson(doc, responsePayload);
            if (doc["admin"] == "ready")
            {
                distToAdmin = doc[String("jarak")];
                if (distToAdmin > 5) // jarak dalam kilo
                {
                    buzzering();
                }
            }
            else
            {
                distToAdmin = -1;
            }
            Serial.print("distToAdmin :");
            Serial.println(distToAdmin);
        }
        else
        {
            Serial.print("Sending data error");
            Serial.println(httpResponseCode);
        }
    }
    delay(1000);
    http.end();
}

void setup()
{
    Serial.begin(115200);

    lcd.init();
    lcd.backlight();

    ss.begin(GPSBaud);
    dht.setup(DhtPin, DHTesp::DHT22);
    pinMode(buzzer, OUTPUT);

    lcd.setCursor(0, 0);
    lcd.print(" SELAMAT DATANG ");
    lcd.setCursor(0, 1);
    lcd.print("      MOJI      ");
    delay(3500);

    wifiCon();
    lcd.setCursor(0, 0);
    lcd.print("  MOHON TUNGGU  ");
    lcd.setCursor(0, 1);
    lcd.print("MENYIAPKAN ALAT.");

    nowmillis = millis();
    lastmillis = nowmillis;

    while (!gpsReady || !dhtReady)
    {
        nowmillis = millis();
        getDataSensor();
        serialPrint();

        if (nowmillis - lastmillis > 10000)
        {
            Serial.println("detik ke 10");
            lastmillis = nowmillis;
        }
    }

    lcd.clear();
}

void loop()
{
    timer();

    while (WiFi.status() != WL_CONNECTED) // checking wifi
    {
        Serial.println("terputus");
        wifiCon();
    }

    getDataSensor();
    lcdPrint();
    serialPrint();

    if (timeCountToPush == 0 && gpsReady && dhtReady)
    {
        pushData(Device_Id, latitude, longitude, temperature, humidity);
        timeCountToPush++;
    }
}