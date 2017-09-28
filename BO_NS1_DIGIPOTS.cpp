#include <BO_NS1_DIGIPOTS.h>

void ns1digipots::i2c_send(uint8_t addr, uint8_t a, uint8_t b)
{
  Wire.beginTransmission(addr);
  Wire.write(a);
  Wire.write(b);
  Wire.endTransmission();
}

void ns1digipots::write(uint8_t pot, uint8_t val)
{
  i2c_send( DIGIPOT_ADDR, 0x40, 0xff );
  i2c_send( DIGIPOT_ADDR, 0xA0, 0xff );
  i2c_send( DIGIPOT_ADDR, gAddresses[pot], val);
}
