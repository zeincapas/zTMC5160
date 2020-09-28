#ifndef STRETCHERACTUATOR_H_ 
#define STRETCHERACTUATOR_H_

class Actuator
{
    public:
        void init(void);
        void setPosition(int32_t);
        void setMicrostep(uint8_t);
        void stop(void);
        void setToDefault(void);  //PLEASE CALL ME AFTER CALLING INIT, DRIVER WONT WORK OTHERWISE.
        void setAcceleration(uint16_t);
        void setVelocity(uint32_t);
        void setVelocity(uint32_t, bool);
        void setMode(uint8_t);
        int32_t getPosition(void);
        void powerMode(bool);
        bool checkStall(void);

        static const int CLOCKWISE = 0;
        static const int ANTI_CLOCKWISE = 1;
};

#endif