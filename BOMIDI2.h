#ifndef _BO_MIDI_TEMPLATE_
#define _BO_MIDI_TEMPLATE_

#include "Arduino.h"

struct MIDITYPE
{
  const static uint8_t NOTEOFF = 0x80;
  const static uint8_t NOTEON = 0x90;
  const static uint8_t POLYAFTER = 0xA0;
  const static uint8_t CC = 0xB0; //Control Change
  const static uint8_t PC = 0xC0; //Program Change
  const static uint8_t CA = 0xD0; //Channel aftertouch
  const static uint8_t PB = 0xE0; //Pitch bend
};

typedef void (*callbackf_t)(uint8_t, uint8_t);
typedef bool (*comparef_t)(MIDIEvent&);

bool returnTrue(MIDIEvent& e)
{
        return true;
}


template<uint8_t LOWVAL,uint8_t HIGHVAL>
bool between(uint8_t value)
{
  if(HIGHVAL >= value && value >= LOWVAL)
    return true;
  else
    return false;
}


template<uint8_t LOWVAL,uint8_t HIGHVAL>
inline bool between(MIDIEvent& e)
{
  return between<LOWVAL,HIGHVAL>(e.m2);
}

template<uint8_t LOWVAL,uint8_t HIGHVAL>
bool controlBetween(MIDIEvent& e)
{
  return between<LOWVAL,HIGHVAL>(e.m2);
}



template<uint8_t CH, uint8_t TYPE, callbackf_t CALLBFUNC, comparef_t COMPFUNC = returnTrue >
struct BoMidiFilter
{
  static const uint8_t STATE = (CH-1|TYPE);

  static void filter(MIDIEvent& e) {
    if ( e.m1 == STATE && COMPFUNC(e) ) {
      CALLBFUNC(e.m2, e.m3);
    }
  }
};

template <class... Ts>
struct RecFilter
{
  void doMidi(MIDIEvent& e) {}
};

template <class T, class... Ts>
struct RecFilter<T, Ts...> : RecFilter<Ts...>
{
  void doMidi(MIDIEvent& e)
  {
    T::filter(e);
    RecFilter<Ts...>::doMidi(e);
  }
  RecFilter(){}
};

template<class T,class ... Ts>
struct BoMidi {

  RecFilter<T,Ts...> mRecFilter;

  void ifMidiDo()
  {
    if ( MIDIUSB.available() > 0 ) {
      MIDIEvent e = MIDIUSB.read();
      mRecFilter.doMidi(e);
      MIDIUSB.flush();
    }
  }

  void whileMidiDo()
  {
    while ( MIDIUSB.available() > 0 ) {
      MIDIEvent e = MIDIUSB.read();
      mRecFilter.doMidi(e);
      MIDIUSB.flush();
    }
  }

};

#endif
