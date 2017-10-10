#include <bofilters.h>

void toneSlide( int16_t in, int16_t& out, int8_t midiCC )
{
  if(midiCC < 1) { out = in; return; }
  else if(in==out) { return; }
  midiCC = 127 - midiCC;
  int16_t o = (in - out);
  int16_t c;
  if(o > 0)
  {
    c = mulu8x16_24( midiCC , o ) >> 7;
    if(!c) c = 1;
  }
  else
  {
    c = - (mulu8x16_24( midiCC , -o ) >> 7);
    if(!c) c = -1;
  }
  out += c;
}


void keyGlide2(int16_t in, int16_t & out, int8_t midiCC)
{
  static int16_t accumilator = 0;
  if(midiCC==0) 
  {
    out = in;
    return;
  }
  else if(in==out) return;
  //TODO: AVR201.asm
  out = mulu8x16_24( midiCC, accumilator );
  accumilator = accumilator - out + in;
}
