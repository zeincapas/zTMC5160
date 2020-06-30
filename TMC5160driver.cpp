#include "TMC5160driver.h"
#include "TMC5160_bitfields.h"

CHOPCONF chopconf;

void TMC5160::modifyBits(uint32_t mask, uint32_t edit, uint32_t* reg)
{
    //clear the register first and then "OR" it after. 
    *reg = (*reg & ~mask) | edit;
}

void TMC5160::mres(uint8_t mStep)
{
    uint32_t bits;
    uint32_t mask;
    uint8_t shift  = 24;
    switch(mStep)
    {
        case 256:   bits = 0x00; break;
        case 128:   bits = 0x01; break;
        case  64:   bits = 0x02; break;
        case  32:   bits = 0x03; break;
        case  16:   bits = 0x04; break;
        case   8:   bits = 0x05; break;
        case   4:   bits = 0x06; break;
        case   2:   bits = 0x07; break;
        case   1:   bits = 0x08; break;    
    }
    bits = bits << shift;
    mask = chopconf.mres << shift;
    modifyBits(mask, bits, &CHOPCONF_CMD);
}

