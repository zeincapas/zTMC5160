#ifndef TMC5160_BITFIELDS_H_
#define TMC5160_BITFIELDS_H_

#include <stdint.h>

//GENERAL CONFIGURATION REGISTERS
const uint8_t GCONF_ADDR =  0x00;
const uint8_t DRV_CONF_ADDR = 0x0A;
const uint8_t GLOBAL_SCALER_ADDR = 0x0B;

//VELOCITY DEPENDENT REGISTERS
const uint8_t IHOLD_RUN_ADDR = 0x10;
const uint8_t TPOWER_DOWN_ADDR = 0x11;
const uint8_t TSTEP_ADDR = 0x12;
const uint8_t TPWMTHRS_ADDR = 0x13;
const uint8_t TCOOLTHRS_ADDR = 0x14;
const uint8_t THIGH_ADDR = 0x15;

//RAMP GENERATOR REGISTERS 
const uint8_t RAMPMODE_ADDR = 0x20;
const uint8_t XACTUAL_ADDR = 0x21;
const uint8_t VACTUAL_ADDR = 0x22;
const uint8_t VSTART_ADDR = 0x23;
const uint8_t ACC1_ADDR = 0x24;
const uint8_t VEL1_ADDR = 0x25;
const uint8_t AMAX_ADDR = 0x26;
const uint8_t VMAX_ADDR = 0x27;
const uint8_t DMAX_ADDR = 0x28;
const uint8_t DEC1_ADDR = 0x2A;
const uint8_t VSTOP_ADDR = 0x2B;
const uint8_t TZEROWAIT_ADDR = 0x2C;
const uint8_t XTARGET_ADDR = 0x2D;
const uint8_t VDCMIN_ADDR = 0x33;
const uint8_t SW_MODE_ADDR = 0x34; //Lookup table
const uint8_t RAMP_STAT_ADDR = 0x35; //Lookup table
const uint8_t XLATCH_ADDR = 0x36;

//MOTOR DRIVER REGISTERS
const uint8_t MSLUT0_ADDR = 0x60;
const uint8_t MSLUT1_ADDR = 0x61;
const uint8_t MSLUT2_ADDR = 0x62;
const uint8_t MSLUT3_ADDR = 0x63;
const uint8_t MSLUT4_ADDR = 0x64;
const uint8_t MSLUT5_ADDR = 0x65;
const uint8_t MSLUT6_ADDR = 0x66;
const uint8_t MSLUT7_ADDR = 0x67;
const uint8_t MSLUTSEL_ADDR = 0x68;
const uint8_t MSLUTSTART_ADDR = 0x69;
const uint8_t CHOPCONF_ADDR = 0x6C;
const uint8_t COOLCONF_ADDR = 0x6D;
const uint8_t PWMCONF_ADDR = 0x70;

struct TMC5160_reg
{
    const uint8_t address;
    uint32_t data;
    const uint8_t bitlength;

};

// TMC5160_reg GCONF{GCONF_ADDR, data, bitlength};




#endif