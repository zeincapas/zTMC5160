#ifndef TMC5160_BITFIELDS_H_
#define TMC5160_BITFIELDS_H_

#include <stdint.h>

//GENERAL CONFIGURATION REGISTERS

struct GCONF
{
    const uint8_t address = 0x00;
};

struct DRV_CONF
{
    const uint8_t address = 0x0A;
};

struct GLOBAL_SCALER
{
    const uint8_t address = 0x0B;
};



//VELOCITY DEPENDENT REGISTERS

struct IHOLD_IRUN 
{
    const uint8_t address = 0x10;
};

struct TPOWER_DOWN
{
    const uint8_t address = 0x11;
};

struct TSTEP
{
    const uint8_t address = 0x12;
};

struct TPWMTHRS
{
    const uint8_t address = 0x13;
};

struct TCOOLTHRS
{
    const uint8_t address = 0x14;
};

struct THIGH
{
    const uint8_t address = 0x15;
};



//RAMP GENERATOR REGISTERS 

struct RAMPMODE
{
    const uint8_t address = 0x20; 
};

struct XACTUAL
{
    const uint8_t address = 0x21;
};

struct VACTUAL
{
    const uint8_t address = 0x22;
};

struct VSTART
{
    const uint8_t address = 0x23;
};

struct ACC1
{
    const uint8_t address = 0x24;
};

struct VEL1
{
    const uint8_t address = 0x25;
};

struct AMAX 
{
    const uint8_t address = 0x26;
};

struct VMAX
{
    const uint8_t address = 0x27;
};

struct DMAX
{
    const uint8_t address = 0x28;
};

struct DEC1
{
    const uint8_t address = 0x2A;
};

struct VSTOP
{
    const uint8_t address = 0x2B;
};

struct TZEROWAIT
{
    const uint8_t address = 0x2C;
};

struct XTARGET
{
    const uint8_t address = 0x2D;
};

struct VDCMIN 
{
    const uint8_t address = 0x33;
};

//This is a big register, each bits is a configuration
struct SW_MODE
{
    const uint8_t address = 0x34;
};

//This is a big register, each bits is a configuration
struct RAMP_STAT
{
    const uint8_t address = 0x35;
};

struct XLATCH
{
    const uint8_t address = 0x36;
};



//MOTOR DRIVER REGISTERS

struct MSLUT0
{
    const uint8_t address = 0x60;
    uint32_t reg;
};

struct MSLUT1
{
    const uint8_t address = 0x61;
    uint32_t reg;
};

struct MSLUT2
{
    const uint8_t address = 0x62;
    uint32_t reg;
};

struct MSLUT3
{
    const uint8_t address = 0x63;
    uint32_t reg;
};

struct MSLUT4
{
    const uint8_t address = 0x64;
    uint32_t reg;
};

struct MSLUT5
{
    const uint8_t address = 0x65;
    uint32_t reg;
};

struct MSLUT6
{
    const uint8_t address = 0x66;
    uint32_t reg;
};

struct MSLUT7
{
    const uint8_t address = 0x67;
    uint32_t reg;
};

//Look up table later
struct MSLUTSEL
{
    const uint8_t address = 0x68;
    uint32_t reg;
};

struct MSLUTSTART
{
    const uint8_t address = 0x69;
    uint32_t reg;
};

//Look up table
struct CHOPCONF
{
    const uint8_t address = 0x6C;
    uint32_t reg;
};

//Look up table
struct COOLCONF
{
    const uint8_t address = 0x6D;
    uint32_t reg; 
};

//Lookup table
struct PWMCONF
{
    const uint8_t address = 0x70;
    uint32_t reg;
};


#endif