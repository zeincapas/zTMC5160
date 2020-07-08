#include <Arduino.h>
#include "TMC5160driver.h"
#include <SPI.h>
// #include "TMC5160_bitfields.h"

TMC5160 driver(1,2,3,24,5);


void setup()
{
    Serial.begin(9600);
    driver.init();


    driver.mres(255);
    driver.tpfd(12);
    driver.vhighchm(0);
    driver.vhighfs(0);
    driver.tbl(36);
    driver.hend(20);
    driver.hstrt(8);
    driver.toff(2);

    driver.sfilt(1);
    driver.sgt(3);
    driver.seimin(1);
    driver.sedn(2);
    driver.semax(20);
    driver.seup(8);
    driver.semin(3);

    driver.pwm_lim(7);
    driver.pwm_reg(8); //Hardcoded to output 5
    driver.freewheel(0);
    driver.pwm_autograd(1);
    driver.pwm_autoscale(1);
    driver.pwm_freq(1);
    driver.pwm_grad(25);
    driver.pwm_ofs(30);

    driver.fastStandStill(0);
    driver.pwmMode(2);
    driver.shaft(0);
    driver.smallHysteresis(0);

    driver.iSenseFilt(0);
    driver.drvStrength(2);
    driver.otSelect(0);
    driver.bbmTime(0);
    driver.bbmClks(4);

    driver.currentScale(0);

    driver.holdCurrent(0);
    driver.runCurrent(31);
    driver.holdDelay(3);

    driver.delayToPowerDown(10);
    driver.upperVelocity(30000);
    driver.lowerVelocity(4000);
    driver.highThresh(500);

    driver.rampMode(0);
    // driver.xActual();
    driver.vStart(0);
    driver.a1(20000);
    driver.v1(30000);
    driver.amax(5000);
    driver.vmax(15000);
    driver.dmax(5000);
    driver.d1(20000);
    driver.vstop(10);
    driver.tzerowait(256);
    driver.vdcmin(0);
    driver.xTarget(50000);


    driver.pushCommands();
}

void loop()
{
    ;
}