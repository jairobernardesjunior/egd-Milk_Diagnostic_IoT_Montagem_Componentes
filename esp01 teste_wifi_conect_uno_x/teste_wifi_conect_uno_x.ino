#include "SoftwareSerial.h"


SoftwareSerial serial2(2 , 3);

void setup()
{
   serial2.begin(9600);
   Serial.begin(9600);
}

void loop()
{
   while (serial2.available()) { Serial.write(serial2.read()); }
   while (Serial.available()) { serial2.write(Serial.read()); }
}