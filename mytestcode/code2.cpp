#include <Arduino.h>
#include <ESP8266WiFi.h> //menggunakan library wifi
#include <WiFiClient.h>
#include <ESP8266WebServer.h> //menggunakan library web
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char *ssid = "moji";
const char *password = "12345678";
String jsonPayload;

void wifiCon()
{
    WiFi.mode(WIFI_OFF); // Prevents reconnection issue (taking too long to connect)
    delay(1000);
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    Serial.print("Connecting"); // menunggu koneksi
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

    jsonPayload = "";
    StaticJsonDocument<200> D2W;

    D2W["id"] = d_id;

    // D2W["title"] = 'foo';
    // D2W["body"] = 'bar';
    // D2W["userId"] = 1;

    serializeJson(D2W, jsonPayload);
    Serial.println(jsonPayload);

    HTTPClient http;
    WiFiClient client;
    http.begin(client, "http://www.moji.auziqni.com/api/deletejamaah");
    // http.begin(client, "http://192.168.107.219:3000/api/updatejamaahloc");
    // http.begin(client, "http://jsonplaceholder.typicode.com/posts"); // mulai request ke alamat
    http.addHeader("Content-Type", "application/json; charset=UTF-8");
    http.addHeader("Content-Length", String(jsonPayload.length()));
    http.setUserAgent("101");
    Serial.println("now is getting");

    int httpResponseCode = http.POST(jsonPayload);
    Serial.println(httpResponseCode);

    String payload = http.getString(); // mengambil respon

    Serial.println(payload);
    delay(5000);
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

    pushData(101, 2, 3, 4, 5);
    delay(1000);
}