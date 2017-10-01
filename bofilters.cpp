#include <bofilters.h>

// simple LP filter taken from https://www.embeddedrelated.com/showarticle/779.php
void keyGlide1( uint16_t in, uint16_t& out, uint16_t factor )
{
  if (factor < 1) 
  {
    out = in;
    return;
  }
  uint16_t result =
  (
    (in > out) ? 
    out + (in - out) : 
    out - (out - in)
  ) >> factor;
  if (result == out) 
    result += (in > out) ? 1 : -1;
  out = result;
}

void keyGlide2(uint16_t in, uint16_t & out, uint16_t factor)
{
  static uint16_t accumilator = 0;
  if(factor==0) 
  {
    out = in;
    return;
  }
  else if(in==out) return;
  //TODO: AVR201.asm
  out = ((uint32_t)accumilator * ((uint32_t)1024 - factor)) >> 10;
  accumilator = accumilator - out + in;
}
