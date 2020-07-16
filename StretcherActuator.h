#ifndef STRETCHERACTUATOR_H_ 
#define STRETCHERACTUATOR_H_

class Actuator
{
    public:
        void init(void);
        void setPosition(int32_t);
        void setMicrostep(uint8_t);
        void setMode(uint8_t);
        uint32_t getPosition(void);
        bool checkStall(void);

};

#endif