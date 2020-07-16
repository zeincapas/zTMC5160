#ifndef ISTRETCHERACTUATOR_H_
#define ISTRETCHERACTUATOR_H_
#include <stdint.h>

class IActuator
{
 public:
    virtual void init() = 0;
    virtual void setMicrostep(uint8_t) = 0;
    virtual void setSpeed(uint32_t) = 0;
    virtual void setMode(uint8_t) = 0; //Velocity +ve, Velocity -ve, position. 
    virtual uint32_t getPosition() = 0;
    virtual bool checkStall() = 0;
};
#endif