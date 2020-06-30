#ifndef TMC5160DRIVER_H_
#define TMC5160DRIVER_H_

#include <stdint.h>

class TMC5160
{
    public:
        uint8_t mosi;
        uint8_t miso;
        uint8_t clk;
        uint8_t cs;
        uint8_t sg;

        TMC5160(uint8_t mosi_pin, uint8_t miso_pin, uint8_t clk_pin, uint8_t cs_pin, uint8_t sg_pin)
        {
            mosi = mosi_pin;
            miso = miso_pin;
            clk = clk_pin;
            cs = cs_pin;
            sg = sg_pin;
        }

    //Bitfield constructor functions
    void init(void); //TODO
    void write(void); //TODO
    void modifyBits(void); //TODO
    void pushCommands(void); //TODO

    //CHOPCONF
    void mres(uint32_t* buffer); //4 bits: 0000 = 256, 0001 = 128, 1000 = FULLSTEP
    void tpfd(uint32_t* buffer); //4 bits: Dampens motor mid-range resonances, 0000:Disable, 1111:1...15
    void vhighchm(uint32_t* buffer); //1 bit:  VHIGH (velocity) threshold can be exceeded
    void vhighfs(uint32_t* buffer); //1 bit: Go into fullstep when VHIGH is exceeded
    void tbl(uint32_t* buffer); //2 bit: Comparator blank time. 00 = 16, 01 = 24, 10 = 36, 11 = 54
    void hend(uint32_t* buffer); //4 bit: Hysteresis low value offset
    void hstrt(uint32_t* buffer); //3 bit: Hysteresis start value added to hend
    void toff(uint32_t* buffer); //4 bit: Off time setting control duration of slow decay phase

    


    //General Configuration Registers
    
    //GCONF
    

    //Ramp Generator Motion Control Register Set

    //Velocity Dependent Driver Feature Control Register Set

    //Motor Driver Register Set

};

#endif