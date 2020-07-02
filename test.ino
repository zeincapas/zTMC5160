#include <Arduino.h>
#include "TMC5160driver.h"
#include <SPI.h>
// #include "TMC5160_bitfields.h"

TMC5160 driver(1,2,3,24,5);


void setup()
{
    Serial.begin(9600);
    driver.init();
    driver.mres(2);
    driver.tpfd(12);
    driver.vhighchm(1);
    driver.vhighfs(0);
    driver.tbl(36);
    driver.hend(-1);
    driver.hstrt(6);
    driver.toff(7);
    
    driver.pushCommands();
}

void loop()
{
    ;
}