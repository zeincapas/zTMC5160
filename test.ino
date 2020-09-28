#include <Arduino.h>
#include <SPI.h>
#include "StretcherActuator.h"
// #include "TMC5160_bitfields.h"

Actuator stretcher;

void setup()
{
    Serial.begin(9600);
    stretcher.init();
    stretcher.setToDefault();
    stretcher.setPosition(500000); //+ve is stretching, -ve is destretching
}

void loop()
{
    ;
}