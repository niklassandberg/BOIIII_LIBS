#ifndef _NS1_DIGIPOTS_H_
#define _NS1_DIGIPOTS_H_

#include "Wire.h"       //i2c lib to drive the quad digipot chip

namespace ns1digipots
{	
  //i2c bus digipot IC addr
  #define DIGIPOT_ADDR 0x2C

  const uint8_t gAddresses[4] = { 0x00, 0x10, 0x60, 0x70 }; //digipot address

  //wrapper for I2C routines
  void i2c_send(uint8_t addr, uint8_t a, uint8_t value); 

  //write a value on one of the four digipots in the IC
  void write(uint8_t pot, uint8_t val);
};

#endif
