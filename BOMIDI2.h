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


template<int LOWVAL,int HIGHVAL>
bool mTwoBetween(MIDIEvent& e)
{
  if(HIGHVAL < e.m2 || e.m2 < LOWVAL)
    return false;
  else
    return true;
}


template<int LOWVAL,int HIGHVAL>
inline bool keyBetween(MIDIEvent& e)
{
  return mTwoBetween<LOWVAL,HIGHVAL>(e);
}

template<int LOWVAL,int HIGHVAL>
bool controlBetween(MIDIEvent& e)
{
  return mTwoBetween<LOWVAL,HIGHVAL>(e);
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
