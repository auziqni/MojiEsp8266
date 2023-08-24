#include <Arduino.h>
#include <ESP8266WiFi.h> //menggunakan library wifi
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "moji";
const char *password = "12345678";
const uint8_t fingerprint[20] = {0xFF, 0xB9, 0xE3, 0xB5, 0x5B, 0x5C, 0xE6, 0xF4, 0xAC, 0x94, 0x77, 0x98, 0xD9, 0xB6, 0xE0, 0x97, 0x60, 0xA8, 0xC2, 0x88};

String jsonReqPayload, responsePayload;
float distToAdmin;

void wifiCon()
{
    WiFi.mode(WIFI_OFF);
    delay(1000);
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    Serial.print("Connecting");
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
}

void pushData(int d_id, float d_lat, float d_lng, float d_temp, float d_humid)
{
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
            }
            else
            {
                distToAdmin = 0;
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

    wifiCon();
}

void loop()
{
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println("terputus");
        wifiCon();
    }

    pushData(1, 2, 3, 4, 5);
    delay(5000);
}