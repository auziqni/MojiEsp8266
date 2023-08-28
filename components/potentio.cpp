#include <Arduino.h>
static const int potentioPin = 0;
int data = 0;
void setup()
{
    Serial.begin(115200);
}

void loop()
{
    data = analogRead(potentioPin);
    Serial.println(data);
    delay(1000);
}