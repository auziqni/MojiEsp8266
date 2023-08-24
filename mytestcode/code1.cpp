#include <Arduino.h>

#include <SoftwareSerial.h>

static const int RXPin = 14, TXPin = 12;
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
    Serial.begin(115200);
    ss.begin(9600);
}

void loop()
{
    while (ss.available() > 0)
    {
        // get the byte data from the GPS
        byte gpsData = ss.read();
        Serial.write(gpsData);
    }
}