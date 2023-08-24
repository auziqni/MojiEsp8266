#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
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
    D2W["lat"] = d_id;
    D2W["lng"] = d_id;
    D2W["temp"] = d_id;
    D2W["humid"] = d_id;

    serializeJson(D2W, jsonPayload);
    Serial.println(jsonPayload);

    HTTPClient http;
    WiFiClient client;
    http.begin(client, "https://www.moji.my.id/api/updatejamaahloc");
    http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    // http.begin(client, "http://192.168.107.219:3000/api/updatejamaahloc");
    // http.begin(client, "http://jsonplaceholder.typicode.com/posts"); // mulai request ke alamat
    http.addHeader("Content-Type", "application/json; charset=UTF-8");
    // http.addHeader("Content-Length", String(jsonPayload.length()));
    // http.setUserAgent("jamaah" + String(d_id));

    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode > 0)
    {
        Serial.print("respon :");
        Serial.println(httpResponseCode);

        // if (httpResponseCode == 308)
        // {
        //     // Mengambil lokasi redirect
        //     String redirectUrl = http.header("Location");
        //     Serial.print("Received 308 Redirect to: ");
        //     Serial.println(redirectUrl);
        // }

        if (httpResponseCode == 200)
        {
            String payload = http.getString();
            Serial.println("Received response after following redirect:");
            Serial.println(payload);
        }
        else
        {
            Serial.print("Error following redirect. HTTP response code: ");
            Serial.println(httpResponseCode);
        }

        // String payload = http.getString(); // mengambil respon
        // Serial.println(payload);
    }
    delay(5000);
    // http.end();
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