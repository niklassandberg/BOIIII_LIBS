#ifndef _BO_FILTER_H_
#define _BO_FILTER_H_

#include "Arduino.h"

void keyGlide1( uint16_t in, uint16_t& out, uint16_t factor );
void keyGlide2( uint16_t in, uint16_t & out, uint16_t factor );

template<uint8_t MINNOTE, uint8_t MAXNOTE, uint8_t DAC_SEMI_TONE, uint16_t MAX_DAC_KEY>
uint16_t midikeyToDac(uint8_t midiVal)
{
  if( midiVal > MAXNOTE ) return MAX_DAC_KEY;
  uint16_t dacVal = (midiVal - MINNOTE) * DAC_SEMI_TONE;
  dacVal += (2 & midiVal) ? 1 : 0; //correlate dac semitones based on analyse.
  return dacVal;
}

#endif
