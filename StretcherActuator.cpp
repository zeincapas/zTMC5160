#include "StretcherActuator.h"
#include "TMC5160driver.h"
#include "bitfields.h"

TMC5160 driver(24,5);

void Actuator::init()
{
    driver.init();

    driver.mres(0);
    driver.tpfd(12);
    driver.vhighchm(0);
    driver.vhighfs(0);
    driver.tbl(2);
    driver.hend(0);
    driver.hstrt(4);
    driver.toff(5);

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
    driver.pwmMode(1);
    driver.shaft(0);
    driver.smallHysteresis(0);

    driver.iSenseFilt(0);
    driver.drvStrength(2);
    driver.otSelect(0);
    driver.bbmTime(0);
    driver.bbmClks(4);

    driver.currentScale(0);

    driver.holdCurrent(15);
    driver.runCurrent(31);
    driver.holdDelay(3);

    driver.delayToPowerDown(10);
    driver.upperVelocity(50);
    driver.lowerVelocity(75);
    driver.highThresh(100);

    driver.dcctrl(37);

    driver.rampMode(0);
    driver.vStart(10);
    driver.a1(500);
    driver.v1(5000);
    driver.amax(3000);
    driver.vmax(15000);
    driver.dmax(1000);
    driver.d1(500);
    driver.vstop(50);
    driver.tzerowait(256);
    driver.vdcmin(0);


    driver.pushInit();
}

void Actuator::setPosition(int32_t val)
{
    driver.xTarget(val);
    driver.write(&driver.XTARGET_CMD, XTARGET_ADDR);
}