#include "TMC5160driver.h"
#include "bitfields.h"
#include <SPI.h>

CHOPCONF chopconf;
PWMCONF pwmconf;
COOLCONF coolconf;
DRVCONF drvconf;
IHOLD ihold;


void TMC5160::init()
{
    pinMode(cs, OUTPUT);
}

void TMC5160::write(uint32_t* cmd, uint8_t address)
{
    //Acquire constructed bitfield and chop it up to 4 bytes. 
    char writeField[4] = {(*cmd >> 24) & 0xFF, (*cmd >> 16) & 0xFF, (*cmd >> 8) & 0xFF, (*cmd) & 0xFF};
    SPI.begin();
    digitalWrite(cs, LOW);
    SPI.transfer(address + WRITE_ACCESS);
    SPI.transfer(&writeField, 4);
    digitalWrite(cs, HIGH);
    SPI.endTransaction();
}

void TMC5160::write(int32_t* cmd, uint8_t address)
{
    //Acquire constructed bitfield and chop it up to 4 bytes. 
    char writeField[4] = {(*cmd >> 24) & 0xFF, (*cmd >> 16) & 0xFF, (*cmd >> 8) & 0xFF, (*cmd) & 0xFF};
    SPI.begin();
    digitalWrite(cs, LOW);
    SPI.transfer(address + WRITE_ACCESS);
    SPI.transfer(&writeField, 4);
    digitalWrite(cs, HIGH);
    SPI.endTransaction();
}

void TMC5160::modifyBits(uint32_t mask, uint32_t edit, uint32_t* reg)
{
    //clear the register first and then "OR" it after. 
    *reg = (*reg & ~mask) | edit;
}

void TMC5160::pushCommands()
{
    // Write to stepper driver
    write(&CHOPCONF_CMD, CHOPCONF_ADDR);
    write(&COOLCONF_CMD, COOLCONF_ADDR);
    write(&PWMCONF_CMD, PWMCONF_ADDR);
    write(&GCONF_CMD, GCONF_ADDR);
    write(&DRVCONF_CMD, DRV_CONF_ADDR);
    write(&XCOMPARE_CMD, XCOMPARE_ADDR);
    write(&GLOBAL_SCALER_CMD, GLOBAL_SCALER_ADDR);
    write(&IHOLD_CMD, IHOLD_RUN_ADDR);
    write(&TPOWERD_CMD, TPOWER_DOWN_ADDR);
    write(&TPWMTHRS_CMD, TPWMTHRS_ADDR);
    write(&TCOOLTHRS_CMD, TCOOLTHRS_ADDR);
    write(&THIGH_CMD, THIGH_ADDR);
    write(&RAMP_MODE_CMD, RAMPMODE_ADDR);
    write(&XACTUAL_CMD, XACTUAL_ADDR);
    write(&VSTART_CMD, VSTART_ADDR);
    write(&A1_CMD, ACC1_ADDR);
    write(&V1_CMD, VEL1_ADDR);
    write(&AMAX_CMD, AMAX_ADDR);
    write(&VMAX_CMD, VMAX_ADDR);
    write(&DMAX_CMD, DMAX_ADDR);
    write(&D1_CMD, DEC1_ADDR);
    write(&VSTOP_CMD, VSTOP_ADDR);
    write(&TZEROWAIT_CMD, TZEROWAIT_ADDR);
    write(&XTARGET_CMD, XTARGET_ADDR);


}

/*********************************************************************************
************************************ CHOPCONF FUNCTIONS **************************
*********************************************************************************/


void TMC5160::mres(uint8_t mStep)
{
    uint32_t bits;
    uint32_t mask;
    switch(mStep)
    {
        case 255:   bits = 0x00; break;
        case 128:   bits = 0x01; break;
        case  64:   bits = 0x02; break;
        case  32:   bits = 0x03; break;
        case  16:   bits = 0x04; break;
        case   8:   bits = 0x05; break;
        case   4:   bits = 0x06; break;
        case   2:   bits = 0x07; break;
        case   1:   bits = 0x08; break;    
        default:    bits = 0x00; break;
    }
    bits = bits << CHOPCONF_MRES_SHIFT;
    mask = chopconf.mres << CHOPCONF_MRES_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}


void TMC5160::tpfd(uint8_t decay)
{
    uint32_t bits;
    uint32_t mask;
    if (decay > 15)
    {
        bits = 15;
    }
    else
    {
        bits = decay;
    }
    bits = bits << CHOPCONF_TPFD_SHIFT;
    mask = chopconf.tpfd << CHOPCONF_TPFD_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::vhighchm(bool mode)
{
    uint32_t bits;
    uint32_t mask;
    bits = mode << CHOPCONF_VHIGHCHM_SHIFT;
    mask = chopconf.vhighchm << CHOPCONF_VHIGHCHM_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::vhighfs(bool mode)
{
    uint32_t bits;
    uint32_t mask;
    bits = mode << CHOPCONF_VHIGHFS_SHIFT;
    mask = chopconf.vhighfs << CHOPCONF_VHIGHFS_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::tbl(uint8_t time)
{
    uint32_t bits;
    uint32_t mask;
    switch(time)
    {
        case  16:   bits = 0x00; break;
        case  24:   bits = 0x01; break;
        case  36:   bits = 0x02; break;
        case  54:   bits = 0x03; break;
        default:    bits = 0x01; break;
    }
    bits = bits << CHOPCONF_TBL_SHIFT;
    mask = chopconf.tbl << CHOPCONF_TBL_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::hend(int8_t val)
{
    uint32_t bits;
    uint8_t mask;
    if(val > 12 || val < -3)
    {
        val = 2;
    }
    bits = val + 3;
    bits = bits << CHOPCONF_HEND_SHIFT;
    mask = chopconf.hend << CHOPCONF_HEND_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::hstrt(uint8_t offset)
{
    uint32_t bits;
    uint8_t mask;
    if (offset > 8)
    {
        offset = 8;
    }
    bits = offset - 1;
    bits = bits << CHOPCONF_HSTRT_SHIFT;
    mask = chopconf.hstrt << CHOPCONF_HSTRT_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

void TMC5160::toff(uint8_t offTime)
{
    uint32_t bits;
    uint32_t mask;
    if (offTime > 15)
    {
        bits = 15;
    }
    else
    {
        bits = offTime;
    }
    bits = bits << CHOPCONF_TOFF_SHIFT;
    mask = chopconf.toff << CHOPCONF_TOFF_SHIFT;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}


/*********************************************************************************
************************************ PWMCONF FUNCTIONS ***************************
*********************************************************************************/

void TMC5160::pwm_lim(uint8_t lim)
{
    uint32_t bits;
    uint32_t mask;
    if (lim > 15)
    {
        bits = 12;
    }
    else
    {
        bits = lim;
    }
    bits = bits << PWMCONF_LIM_SHIFT;
    mask = pwmconf.pwm_lim << PWMCONF_LIM_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_reg(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    
    //Currently hard coded to default
    bits = 0x06;
    bits = bits << PWMCONF_REG_SHIFT;
    mask = pwmconf.pwm_reg << PWMCONF_REG_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::freewheel(uint8_t mode)
{
    uint32_t bits;
    uint32_t mask;
    bits = mode;
    bits = bits << PWMCONF_FREEWHEEL_SHIFT;
    mask = pwmconf.freewheel << PWMCONF_FREEWHEEL_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_autograd(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << PWMCONF_AUTOGRAD_SHIFT;
    mask = pwmconf.pwm_autograd << PWMCONF_AUTOGRAD_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_autoscale(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << PWMCONF_AUTOSCALE_SHIFT;
    mask = pwmconf.pwm_autoscale << PWMCONF_AUTOSCALE_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_freq(uint8_t mode)
{
    uint32_t bits;
    uint32_t mask;
    bits = mode;
    bits = bits << PWMCONF_FREQ_SHIFT;
    mask = pwmconf.pwm_freq << PWMCONF_FREQ_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_grad(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 255 || val < 0)
    {
        bits = 128;
    }
    else
    {
        bits = val;
    }
    bits = bits << PWMCONF_GRAD_SHIFT;
    mask = pwmconf.pwm_grad << PWMCONF_GRAD_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

void TMC5160::pwm_ofs(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 255 || val < 0)
    {
        bits = 128;
    }
    else
    {
        bits = val;
    }
    bits = bits << PWMCONF_OFS_SHIFT;
    mask = pwmconf.pwm_ofs << PWMCONF_OFS_SHIFT;
    modifyBits(mask, bits, &PWMCONF_CMD);
}

/*********************************************************************************
************************************ COOLCONF FUNCTIONS ***************************
*********************************************************************************/

void TMC5160::sfilt(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << COOLCONF_SFILT_SHIFT;
    mask = coolconf.sfilt << COOLCONF_SFILT_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

void TMC5160::sgt(uint8_t val)
{
    //TODO SIgned value
    uint32_t bits;
    uint32_t mask; 
    bits = 4;
    bits = bits << COOLCONF_SGT_SHIFT;
    mask = coolconf.sgt << COOLCONF_SGT_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);    
}

void TMC5160::seimin(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << COOLCONF_SEIMIN_SHIFT;
    mask = coolconf.seimin << COOLCONF_SEIMIN_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

void TMC5160::sedn(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 3 || val < 0)
    {
        bits = 1;
    }
    else 
    {
        bits = val;
    }
    bits = bits << COOLCONF_SEDN_SHIFT;
    mask = coolconf.sedn << COOLCONF_SEDN_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

void TMC5160::semax(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 15 || val < 0)
    {
        bits = 7;
    }
    else 
    {
        bits = val;
    }
    bits = bits << COOLCONF_SEMAX_SHIFT;
    mask = coolconf.semax << COOLCONF_SEMAX_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

void TMC5160::seup(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 3 || val < 0)
    {
        bits = 3;
    }
    else 
    {
        bits = val;
    }
    bits = bits << COOLCONF_SEUP_SHIFT;
    mask = coolconf.seup << COOLCONF_SEUP_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

void TMC5160::semin(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 15 || val < 0)
    {
        bits = 12;
    }
    else 
    {
        bits = val;
    }
    bits = bits << COOLCONF_SEMIN_SHIFT;
    mask = coolconf.semin << COOLCONF_SEMIN_SHIFT;
    modifyBits(mask, bits, &COOLCONF_CMD);
}

/*********************************************************************************
********************************** GCONF FUNCTIONS *******************************
*********************************************************************************/

void TMC5160::smallHysteresis(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << GCONF_SMALL_HYSTERESIS_SHIFT;
    mask = 0b1 << GCONF_SMALL_HYSTERESIS_SHIFT;
    modifyBits(mask, bits, &GCONF_CMD);
}

void TMC5160::shaft(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << GCONF_SHAFT_SHIFT;
    mask = 0b1 << GCONF_SHAFT_SHIFT;
    modifyBits(mask, bits, &GCONF_CMD);
}

void TMC5160::pwmMode(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << GCONF_PWM_MODE_SHIFT;
    mask = 0b1 << GCONF_PWM_MODE_SHIFT;
    modifyBits(mask, bits, &GCONF_CMD);
}

void TMC5160::fastStandStill(bool flag)
{
    uint32_t bits;
    uint32_t mask;
    bits = flag << GCONF_FAST_STANDSTILL_SHIFT;
    mask = 0b1 << GCONF_FAST_STANDSTILL_SHIFT;
    modifyBits(mask, bits, &GCONF_CMD);
}

/*********************************************************************************
********************************** XCOMPARE FUNCTIONS ****************************
*********************************************************************************/

void TMC5160::positionCompare(uint32_t val)
{
    uint32_t* reg;
    reg = &XCOMPARE_CMD;
    *reg = val;
}

/*********************************************************************************
********************************** DRVCONF FUNCTIONS *****************************
*********************************************************************************/

void TMC5160::bbmTime(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 24 || val < 0)
    {
        bits = 24;
    }
    else 
    {
        bits = val;
    }
    bits = bits << DRVCONF_BBM_TIME_SHIFT;
    mask = drvconf.bbmtime << DRVCONF_BBM_TIME_SHIFT;
    modifyBits(mask, bits, &DRVCONF_CMD);
}

void TMC5160::bbmClks(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 15 || val < 0)
    {
        bits = 15;
    }
    else 
    {
        bits = val;
    }
    bits = bits << DRVCONF_BBM_CLKS_SHIFT;
    mask = drvconf.bbmclks << DRVCONF_BBM_CLKS_SHIFT;
    modifyBits(mask, bits, &DRVCONF_CMD);
}

void TMC5160::otSelect(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 3 || val < 0)
    {
        bits = 3;
    }
    else 
    {
        bits = val;
    }
    bits = bits << DRVCONF_OTSELECT_SHIFT;
    mask = drvconf.otselect << DRVCONF_OTSELECT_SHIFT;
    modifyBits(mask, bits, &DRVCONF_CMD);
}

void TMC5160::drvStrength(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 3 || val < 0)
    {
        bits = 3;
    }
    else 
    {
        bits = val;
    }
    bits = bits << DRVCONF_DRV_STRENGTH_SHIFT;
    mask = drvconf.drvstrength << DRVCONF_DRV_STRENGTH_SHIFT;
    modifyBits(mask, bits, &DRVCONF_CMD);
}

void TMC5160::iSenseFilt(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 3 || val < 0)
    {
        bits = 3;
    }
    else 
    {
        bits = val;
    }
    bits = bits << DRVCONF_FILT_ISENSE_SHIFT;
    mask = drvconf.filt_isense << DRVCONF_FILT_ISENSE_SHIFT;
    modifyBits(mask, bits, &DRVCONF_CMD);
}

/*********************************************************************************
*************************** GLOBAL CURRENT SCALER FUNCTIONS **********************
*********************************************************************************/

void TMC5160::currentScale(uint8_t val)
{
    uint32_t* reg;
    reg = &GLOBAL_SCALER_CMD;
    if (val > 31 || val < 0)
    {
        *reg = 31;
    }
    else 
    {
        *reg = val;
    }
}

/*********************************************************************************
********************************* CURRENT FUNCTIONS ******************************
*********************************************************************************/

void TMC5160::holdCurrent(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 32 || val < 0)
    {
        bits = 32;
    }
    else 
    {
        bits = val;
    }
    bits = bits << IHOLD_IHOLD_SHIFT;
    mask = ihold.ihold << IHOLD_IHOLD_SHIFT;
    modifyBits(mask, bits, &IHOLD_CMD);
}

void TMC5160::runCurrent(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 32 || val < 0)
    {
        bits = 32;
    }
    else 
    {
        bits = val;
    }
    bits = bits << IHOLD_IRUN_SHIFT;
    mask = ihold.irun << IHOLD_IRUN_SHIFT;
    modifyBits(mask, bits, &IHOLD_CMD);
}

void TMC5160::holdDelay(uint8_t val)
{
    uint32_t bits;
    uint32_t mask;
    if (val > 15 || val < 0)
    {
        bits = 15;
    }
    else 
    {
        bits = val;
    }
    bits = bits << IHOLD_DELAY_SHIFT;
    mask = ihold.delay << IHOLD_DELAY_SHIFT;
    modifyBits(mask, bits, &IHOLD_CMD);
}

/*********************************************************************************
************************* VELOCITY DEPENDENT DRV FUNCTIONS ***********************
*********************************************************************************/

void TMC5160::delayToPowerDown(uint8_t val)
{
    uint32_t* reg;
    reg = &TPOWERD_CMD;

    if (val > 255 || val < 0)
    {
        *reg = 255;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::upperVelocity(uint32_t val)
{
    uint32_t* reg;
    reg = &TPWMTHRS_CMD;
    *reg = val;
}

void TMC5160::lowerVelocity(uint32_t val)
{
    uint32_t* reg;
    reg = &TCOOLTHRS_CMD;
    *reg = val;
}

void TMC5160::highThresh(uint32_t val)
{
    uint32_t* reg;
    reg = &THIGH_CMD;
    *reg = val;
}

/*********************************************************************************
************************* VELOCITY DEPENDENT DRV FUNCTIONS ***********************
*********************************************************************************/

void TMC5160::rampMode(uint8_t val)
{
    uint32_t* reg;
    reg = &RAMP_MODE_CMD;
    if (val > 3 || val < 0)
    {
        *reg = 0;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::xActual(int32_t val)
{
    int32_t* reg;
    reg = &XACTUAL_CMD;
    *reg = val;
}


void TMC5160::vStart(uint32_t val)
{
    uint32_t* reg;
    reg = &VSTART_CMD;
    if (val > 262143 || val < 0)
    {
        *reg = 262143;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::a1(uint16_t val)
{
    uint32_t* reg;
    reg = &A1_CMD;
    *reg = val;
}

void TMC5160::v1(uint32_t val)
{
    uint32_t* reg;
    reg = &V1_CMD;
    if (val > 1048575 || val < 0)
    {
        *reg = 1048575;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::amax(uint16_t val)
{
    uint32_t* reg;
    reg = &AMAX_CMD;
    *reg = val;
}

void TMC5160::vmax(uint32_t val)
{
    uint32_t* reg;
    reg = &VMAX_CMD;
    if (val > 8388607 || val < 0)
    {
        *reg = 8388607;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::dmax(uint16_t val)
{
    uint32_t* reg;
    reg = &DMAX_CMD;
    *reg = val;
}

void TMC5160::d1(uint16_t val)
{
    uint32_t* reg;
    reg = &D1_CMD;
    *reg = val;
}

void TMC5160::vstop(uint32_t val)
{
    uint32_t* reg;
    reg = &VSTOP_CMD;
    if (val > 262143 || val < 0)
    {
        *reg = 262143;
    }
    else 
    {
        *reg = val;
    }
}

void TMC5160::tzerowait(uint16_t val)
{
    uint32_t* reg;
    reg = &TZEROWAIT_CMD;
    *reg = val;
}

void TMC5160::xTarget(int32_t val)
{
    int32_t* reg;
    reg = &XTARGET_CMD;
    *reg = val;
}