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

    driver.sfilt(1);
    driver.sgt(3);
    driver.seimin(0);
    driver.sedn(1);
    driver.semax(13);
    driver.seup(8);
    driver.semin(13);

    driver.pwm_lim(12);
    driver.pwm_reg(8); //Hardcoded to output 5
    driver.freewheel(0);
    driver.pwm_autograd(1);
    driver.pwm_autoscale(1);
    driver.pwm_freq(1);
    driver.pwm_grad(25);
    driver.pwm_ofs(30);


    driver.pushCommands();
}

void loop()
{
    ;
}