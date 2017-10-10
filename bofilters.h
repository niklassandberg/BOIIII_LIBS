#ifndef _BO_FILTER_H_
#define _BO_FILTER_H_

#ifdef MOCK_ARDUINO
#include <arduinomock.h>
#else
#include <Arduino.h>
#endif

#include <bomath.h>

void toneSlide( int16_t in, int16_t& out, int8_t midiCC );

// in - ADC value (key value)
// out - ADC value (key slide value)
// midiCc - 0 indecates no tone slide => 127 max tone slide
void toneSlide2( int16_t in, int16_t & out, int8_t midiCC );

template<uint8_t MINNOTE, uint8_t MAXNOTE, uint8_t DAC_SEMI_TONE, uint16_t MAX_DAC_KEY>
uint16_t midikeyToDac(uint8_t midiVal)
{
  if( midiVal > MAXNOTE ) return MAX_DAC_KEY;
  uint16_t dacVal = (midiVal - MINNOTE) * DAC_SEMI_TONE;
  dacVal += (2 & midiVal) ? 1 : 0; //correlate dac semitones based on analyse.
  return dacVal;
}

#endif
