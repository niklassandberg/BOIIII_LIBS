#include <bofilters.h>

#ifndef _BO_FILTERS_H_
#define _BO_FILTERS_H_

void inline toneSlide( int16_t in, int16_t& out, uint8_t factor )
{
  if(factor == 255) { out = in; return; }
  else if(in==out) { return; }
  int16_t o = (in - out);
  //int16_t c = abs(o);
  int16_t c;
  MUL_U8_x_16_RSHIFT_8_16( c, factor , o );
  //if(factor > 1) return; //TODO: testing... dummy.
  if(!c) c = (o>0)-(o<0);
  out += c;
}


void inline toneSlide2(int16_t in, int16_t & out, uint8_t factor)
{
  static int16_t accumilator = 0;
  if(factor == 255 ) { out = in; return; }
  else if(in==out) { return; }
  //if(midiCC > 119) midiCC = 119; //because if becomes unstable otherwice.
  MUL_U8_x_16_RSHIFT_8_16( out, factor , accumilator);
  accumilator = accumilator - out + in;
}

void inline toneSlide3( int16_t in, int16_t& out, uint8_t midiCC )
{
  if(! midiCC) { out = in; return; };
  midiCC <<= 1;
  midiCC = ~midiCC; // 0-127 => 255-0
  int16_t o = (in - out);
  if (o > 1) {
    out += (int16_t) midiCC;
    if (out > in) out = in;
  } else if (0 < 1) {
    out -= (int16_t) midiCC;
    if (out < in) out = in;
  } else {
    return;
  }
}

#endif
