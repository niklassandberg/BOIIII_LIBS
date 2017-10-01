#ifndef _NS1_CC_DIGIPOTS_h_
#define _NS1_CC_DIGIPOTS_h_

#include <utils/ns1_digipots.cpp>

#define NUM_OT_POTS 4

class Pots
{
    class Pot {

        uint8_t mCC = 0;
        uint8_t mValue = 0;
        bool mCCReady = false;

      public:

        void cc(uint8_t cc)
        {
          mCC = cc;
        }

        void readIfCC(uint8_t cc, uint8_t value)
        {
          mCCReady = true;
          mValue = value << 1;
        }

        void writeIfReady(uint8_t potIndex)
        {
          if ( mCCReady )
          {
            ns1digipots::write(potIndex, mValue);
            mCCReady = false;
          }
        }
    };

    Pot mPots[NUM_OT_POTS];

  public:

    Pots()
    {
    }

    void setup(uint8_t cc[])
    {
      for (size_t i = 0 ; i < NUM_OT_POTS ; ++i)
        mPots[i].cc(cc[i]);
    }

    void write()
    {
      //it is necessary to move the i2c routines out of the callback.
      //probably due to some interrupt handling!
      for ( int i = 0; i < NUM_OT_POTS; ++i )
      {
        mPots[i].writeIfReady(i);
      }
    }

    void read(uint8_t cc, uint8_t value)
    {
      for ( int i = 0; i < NUM_OT_POTS; ++i )
      {
        mPots[i].readIfCC(cc, value);
      }
    }
};

#endif
