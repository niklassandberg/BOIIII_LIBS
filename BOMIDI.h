#ifndef _BO_MIDI_
#define _BO_MIDI_

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
inline bool keyBetween(MIDIEvent& e)
{
  return between<LOWVAL,HIGHVAL>(e.m2);
}

template<uint8_t LOWVAL,uint8_t HIGHVAL>
bool controlBetween(MIDIEvent& e) 
{
  return between<LOWVAL,HIGHVAL>(e.m2);
}

struct BoMidiFilter
{
  uint8_t mStatus;
  comparef_t mCompare;
  callbackf_t mCallback;

  BoMidiFilter() : mStatus(0), mCompare(NULL), mCallback(NULL) {}
  BoMidiFilter(
      uint8_t channel, 
      uint8_t type, 
      callbackf_t callback,
      comparef_t compare = returnTrue
  ) :
    mStatus(channel-1|type), 
    mCallback(callback),
    mCompare(compare)
  {}
  
  void filter(MIDIEvent& e) {
    if ( e.m1 == mStatus ) {
      if(!mCompare(e)) return;
      mCallback(e.m2, e.m3);
    }
  }

  bool isNull() const 
  {
    return mCallback == NULL;
  }

};

#define BO_MIDI_FILTER_ARRAY_END BoMidiFilter(0,0, NULL)

struct BoMidi {
  
  size_t mLen;
  BoMidiFilter * mMidiFilters;

  void removeFilters()
  {
    if(mMidiFilters!= NULL)
      delete [] mMidiFilters;
    mLen = 0;
  }

  void setup(const BoMidiFilter * midiFilters)
  {
    removeFilters();
    size_t len = 0;
    for( ; ! midiFilters[len].isNull() ; ++len);
    mMidiFilters = new BoMidiFilter[len];
    for(size_t i = 0; i < len; i++)
    {
      mMidiFilters[i] = midiFilters[i];      
    }
    
    mLen = len;
  }
  
  ~BoMidi()
  {
    removeFilters();
  }

  BoMidi()
  {
    mLen = 0;
    mMidiFilters = NULL;
  }

  void doMidi()
  {
    MIDIEvent e = MIDIUSB.read();
    for(size_t i = 0 ; i < mLen ; ++i )
      mMidiFilters[i].filter(e);
    MIDIUSB.flush();
  }

  void ifMidiDo()
  {
   if ( MIDIUSB.available() > 0 ) {
      doMidi();
    }
  }

  void whileMidiDo()
  {
    while ( MIDIUSB.available() > 0 ) {
      doMidi();
    }
  }

};

#endif
