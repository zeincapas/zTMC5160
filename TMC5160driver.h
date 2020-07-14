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
        void write(uint32_t* cmd, uint8_t address); //TODO
        void write(int32_t* cmd, uint8_t address);
        void modifyBits(uint32_t mask, uint32_t edit, uint32_t* reg); //TODO
        void pushCommands(void); //TODO

        //CHOPCONF
        void mres( uint8_t val); //4 bits: 0000 = 256, 0001 = 128, 1000 = FULLSTEP
        void tpfd(uint8_t val); //4 bits: Dampens motor mid-range resonances, 0000:Disable, 1111:1...15
        void vhighchm(bool val); //1 bit:  VHIGH (velocity) threshold can be exceeded
        void vhighfs(bool val); //1 bit: Go into fullstep when VHIGH is exceeded
        void tbl(uint8_t val); //2 bit: Comparator blank time. 00 = 16, 01 = 24, 10 = 36, 11 = 54
        void hend(int8_t val); //4 bit: Hysteresis low value offset
        void hstrt(uint8_t val); //3 bit: Hysteresis start value added to hend
        void toff(uint8_t val); //4 bit: Off time setting control duration of slow decay phase

        //PWMCONF
        void pwm_lim(uint8_t val); //4 bit: Reduce current jerk during mode change back to stealtchop from spreadcycle. set to 12.
        void pwm_reg(uint8_t val); //4 bit: Regulation loop gradient set to 4
        void freewheel(uint8_t val); //2 bit: 0: normal operation, 1: frewheeling
        void pwm_autograd(bool val); //1 bit: Automatic gradient adaptation 0: Fixed value for PWM_GRAD, 1: Automatic tuning
        void pwm_autoscale(bool val); //1 bit: PWM automatic amplitude scaling 0: User define PWM amplitude  1: Enable automatic current control
        void pwm_freq(uint8_t val); //2 bit: Set to 1
        void pwm_grad(uint8_t val); //8 bit: Initialize user defined amplitude gradient; Set to 25
        void pwm_ofs(uint8_t val); //8 bits: Initialize user defined amplited offset; Set to 30

        //COOLCONF
        void sfilt(bool val); //1 bit: 0: Stall guard is sampled every high time. 1: Filtered, only stall guard sampled every 4 high time. 
        void sgt(uint8_t val); //7 bit: Stall guard threshold value, the higher it is, the more torque required to indicate stall.
        void seimin(bool val); //1 bit: Minimum current for smart current control 0: 1/2 of current setting  1: 1/4 of current setting
        void sedn(uint8_t val); //2 bit: Current down step speed, the higher the value, the more sensitive the current step down is.
        void semax(uint8_t val); //4 bit: stallGuard2 hysteresis value for smart current control.
        void seup(uint8_t val); //2 bit: current up step size
        void semin(uint8_t val); //4 bit: minimum stallGuard2 value for smart current control
        
        //GCONF
        void smallHysteresis(bool val);
        void shaft(bool val);
        void pwmMode(bool val);
        void fastStandStill(bool val);

        //XCOMPARE
        void positionCompare(uint32_t val);

        //DRVCONF
        void iSenseFilt(uint8_t val);
        void drvStrength(uint8_t val);
        void otSelect(uint8_t val);
        void bbmClks(uint8_t val);
        void bbmTime(uint8_t val);

        //GlOBAL_SCALER
        void currentScale(uint8_t val);

        //IHOLD 
        void holdCurrent(uint8_t val);
        void runCurrent(uint8_t val);
        void holdDelay(uint8_t val);

        //Velocity driven functions
        void delayToPowerDown(uint8_t val);
        void upperVelocity(uint32_t val);
        void lowerVelocity(uint32_t val);
        void highThresh(uint32_t val);

        //Motion controller functions
        void rampMode(uint8_t val);
        void xActual(int32_t val);
        void vStart(uint32_t val);
        void a1(uint16_t val);
        void v1(uint32_t val);
        void amax(uint16_t val);
        void vmax(uint32_t val);
        void dmax(uint16_t val);
        void d1(uint16_t val);
        void vstop(uint32_t val);
        void tzerowait(uint16_t val);
        void vdcmin(uint32_t val);
        void xTarget(int32_t val);

        //DRIVER functions
        void dcctrl(uint32_t val);

        //READ buffer
        uint32_t READ_BUF = 0;
        
        //WRITE CMD
        uint32_t COOLCONF_CMD = 0;
        uint32_t CHOPCONF_CMD = 0;
        uint32_t PWMCONF_CMD = 0;
        uint32_t GCONF_CMD = 0;
        uint32_t DRVCONF_CMD = 0;
        uint32_t XCOMPARE_CMD = 0;
        uint32_t GLOBAL_SCALER_CMD = 0;
        uint32_t IHOLD_CMD = 0;
        uint32_t TPOWERD_CMD = 0;
        uint32_t TPWMTHRS_CMD = 0;
        uint32_t TCOOLTHRS_CMD = 0;
        uint32_t THIGH_CMD = 0;
        uint32_t RAMP_MODE_CMD = 0;
        int32_t XACTUAL_CMD = 0;
        uint32_t VSTART_CMD = 0;
        uint32_t A1_CMD = 0;
        uint32_t V1_CMD = 0;
        uint32_t AMAX_CMD = 0;
        uint32_t VMAX_CMD = 0;
        uint32_t DMAX_CMD = 0;
        uint32_t D1_CMD = 0;
        uint32_t VSTOP_CMD = 0;
        uint32_t TZEROWAIT_CMD = 0;
        uint32_t VDCMIN_CMD = 0;
        int32_t XTARGET_CMD = 0;
        uint32_t DCCTRL_CMD = 0;


};

#endif