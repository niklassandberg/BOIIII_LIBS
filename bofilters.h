#ifndef _BO_FILTER_H_
#define _BO_FILTER_H_

#ifdef MOCK_ARDUINO
#include <arduinomock.h>
#else
#include <Arduino.h>
#endif

#include <bomath.h>

// in - ADC value (key value)
// out - ADC value (key slide value)
// factor - 255 indecates no tone slide, 0 max tone slide
void inline toneSlide( int16_t in, int16_t & out, uint8_t factor );

// in - ADC value (key value)
// out - ADC value (key slide value)
// midiCC - 0 indecates no tone slide, 127 max tone slide
void inline toneSlide2( int16_t in, int16_t & out, uint8_t midiCC );

void inline toneSlide3( int16_t in, int16_t & out, uint8_t midiCC );

template<uint8_t MINNOTE, uint8_t MAXNOTE, uint8_t DAC_SEMI_TONE, uint16_t MAX_DAC_KEY>
uint16_t inline midikeyToDac(uint8_t midiVal)
{
  if( midiVal > MAXNOTE ) return MAX_DAC_KEY;
  uint16_t dacVal = mulu8x8_16( (midiVal - MINNOTE),  DAC_SEMI_TONE);
  //dacVal += (2 & midiVal) ? 1 : 0; equals.
  //dacVal += (2 & midiVal) >> 1;
  dacVal += (2 & midiVal) >> 1; //correlate dac semitones based on analyse.
  return dacVal;
}

//inline does not work
#include <bofilters.cpp>

#endif
