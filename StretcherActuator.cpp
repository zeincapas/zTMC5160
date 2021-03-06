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
    driver.toff(5); // should be 5, turn to 0 for turning off chopper

    driver.sfilt(1);
    driver.sgt(3);
    driver.seimin(1);
    driver.sedn(2);
    driver.semax(20);
    driver.seup(8);
    driver.semin(3);

    driver.pwm_lim(15);
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

    driver.holdCurrent(0);
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
    driver.rampMode(0);
    driver.xTarget(val);
    driver.write(&driver.XTARGET_CMD, XTARGET_ADDR);
}

void Actuator::setMicrostep(uint8_t val)
{
    driver.mres(val);
    driver.write(&driver.CHOPCONF_CMD, CHOPCONF_ADDR);
}

void Actuator::powerMode(bool flag)
{
    if (flag == 1)
    {
        driver.toff(5);
    }
    else
    {
        driver.toff(0);
    }
    driver.write(&driver.CHOPCONF_CMD, CHOPCONF_ADDR);
}

int32_t Actuator::getPosition()
{
    int32_t position = driver.read(XACTUAL_ADDR);
    return position;
}

void Actuator::setAcceleration(uint16_t value)
{
    driver.a1(value);
    driver.amax(value/2);
    driver.d1(value);
    driver.dmax(value/2);
    driver.write(&driver.A1_CMD, ACC1_ADDR);
    driver.write(&driver.AMAX_CMD, AMAX_ADDR);
    driver.write(&driver.D1_CMD, DEC1_ADDR);
    driver.write(&driver.DMAX_CMD, DMAX_ADDR);
}

void Actuator::setVelocity(uint32_t value)
{
    driver.vmax(value);
    driver.write(&driver.VMAX_CMD, VMAX_ADDR);
}

void Actuator::setVelocity(uint32_t value, bool dir)
{
    switch(dir)
    {
        case 0:     driver.rampMode(1); break;
        case 1:     driver.rampMode(2); break;
    }
    driver.vmax(value);
    driver.write(&driver.VMAX_CMD, VMAX_ADDR);
}

void Actuator::setToDefault(void)
{
    driver.vStart(10);
    driver.a1(2000);
    driver.v1(1000);
    driver.amax(1000);
    driver.vmax(200000); //THIS IS THE SPEED VALUE
    driver.dmax(1000);
    driver.d1(2000);
    driver.vstop(10);
    driver.tzerowait(256);
    driver.vdcmin(0);
    driver.write(&driver.VSTART_CMD, VSTART_ADDR);
    driver.write(&driver.A1_CMD, ACC1_ADDR);
    driver.write(&driver.V1_CMD, VEL1_ADDR);
    driver.write(&driver.AMAX_CMD, AMAX_ADDR);
    driver.write(&driver.VMAX_CMD, VMAX_ADDR);
    driver.write(&driver.DMAX_CMD, DMAX_ADDR);
    driver.write(&driver.D1_CMD, DEC1_ADDR);
    driver.write(&driver.VSTOP_CMD, VSTOP_ADDR);
    driver.write(&driver.TZEROWAIT_CMD, TZEROWAIT_ADDR);
    driver.write(&driver.VDCMIN_CMD, VDCMIN_ADDR);
}

void Actuator::setMode(uint8_t val)
{
    driver.rampMode(val);
}