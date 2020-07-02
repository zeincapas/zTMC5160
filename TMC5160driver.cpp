#include "TMC5160driver.h"
#include "bitfields.h"
#include <SPI.h>

CHOPCONF chopconf;
PWMCONF pwmconf;
COOLCONF coolconf;

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
    SPI.transfer(address);
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
    // write(&CHOPCONF_CMD, CHOPCONF_ADDR);
    // write(&COOLCONF_CMD, COOLCONF_ADDR);
    write(&PWMCONF_CMD, PWMCONF_ADDR);
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
