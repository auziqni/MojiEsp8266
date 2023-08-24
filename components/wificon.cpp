#include <Arduino.h>
#include <ESP8266WiFi.h> //menggunakan library wifi

// wifi init

const char *ssid = "moji";
const char *password = "12345678";

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
    Serial.println("berhasil");
    delay(1000);
}