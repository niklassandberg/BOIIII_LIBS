#include <bofilters.h>

void toneSlide( int16_t in, int16_t& out, int8_t midiCC )
{
  if(midiCC < 1) { out = in; return; }
  else if(in==out) { return; }
  midiCC = (127 - midiCC) << 1; // 0-127 => 0-255
  int16_t o = (in - out);
  int16_t c;
  if(o > 0)
  {
    c = mulu8x16div8_16( midiCC , o );
    if(!c) c = 1;
  }
  else
  {
    c = - mulu8x16div8_16( midiCC , -o );
    if(!c) c = -1;
  }
  out += c;
}


void toneSlide2(int16_t in, int16_t & out, int8_t midiCC)
{
  static int16_t accumilator = 0;
  if(midiCC < 1) { out = in; return; }
  else if(in==out) { return; }
  if(midiCC > 119) midiCC = 119; //because if becomes unstable otherwice.
  midiCC = 127 - midiCC;
  out = mulu8x16div8_16( midiCC << 1, accumilator);
  accumilator = accumilator - out + in;
}
