#include <Arduino.h>

static const int buzzer = 2;
static const int potentioPin = 0;
int potenRead = 0, potenReadPrev = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(buzzer, OUTPUT);
}

void loop()
{
    potenRead = analogRead(potentioPin);

    float latitude = -50 + (potenRead * 120 / 1024);
    float longitude = -60 + (potenRead * 160 / 1024);
    // float latitude = -50 +  (potenRead*2);
    // float longitude = -60 + (potenRead/2);

    Serial.print(potenRead);
    Serial.print("\t");
    Serial.print(latitude);
    Serial.print("\t");
    Serial.print(longitude);
    Serial.println("");
    int diffrence = abs(potenRead - potenReadPrev);
    if (potenRead > 100 && diffrence > 10)
    {
        digitalWrite(buzzer, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        potenReadPrev = potenRead;
    }
}