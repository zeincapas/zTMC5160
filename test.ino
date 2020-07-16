#include <Arduino.h>
#include "TMC5160driver.h"
#include <SPI.h>
#include "StretcherActuator.h"
// #include "TMC5160_bitfields.h"

Actuator stretcher;

void setup()
{
    Serial.begin(9600);
    stretcher.init();
    stretcher.setPosition(5000);
}

void loop()
{
    ;
}