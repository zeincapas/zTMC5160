#ifndef STRETCHERACTUATOR_H_ 
#define STRETCHERACTUATOR_H_

#include "IStretcherActuator.h"
#include "TMC5160driver.h"

class Actuator: public IActuator
{
    public:

        Actuator(uint8_t cs_pin, uint8_t sg_pin)
        {
            TMC5160 driver(cs_pin, sg_pin);
        }

        void init(void);
        void setMicrostep(uint8_t);
        void setSpeed(uint32_t);
        void setMode(uint8_t);
        uint32_t getPosition(void);
        bool checkStall(void);

};

#endif