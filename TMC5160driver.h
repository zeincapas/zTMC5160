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



};

#endif