#ifndef STRETCHERACTUATOR_H_ 
#define STRETCHERACTUATOR_H_

class Actuator
{
    public:
        void init(void);
        void setPosition(int32_t);
        void setMicrostep(uint8_t);
        void setMode(uint8_t);
        void setAcceleration(uint16_t);
        void setVelocity(uint32_t);
        uint32_t getPosition(void);
        void powerMode(bool);
        bool checkStall(void);

};

#endif