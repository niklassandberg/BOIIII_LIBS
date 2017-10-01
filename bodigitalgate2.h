#ifndef _DIGITAL_GATE_H_
#define _DIGITAL_GATE_H_

class DigitalGate
{
    uint8_t mInputPin;
    uint8_t mPrevValue;
    uint8_t mValue;
    bool mChanged;
  public:
    DigitalGate(uint8_t inputPin) :
      mInputPin(inputPin), mPrevValue(LOW), mValue(LOW), mChanged(false)
    {
      pinMode( inputPin, INPUT );
    }

    bool operator()()
    {
      uint8_t value = digitalRead(mInputPin);
      if ( value != mPrevValue )
      {
        mValue = value;
        mChanged = true;
      }
      else
      {
        mChanged = false;
      }
      mPrevValue = value;
      return mChanged;
    }

    bool changed()
    {
      return mChanged;
    }

    bool high()
    {
      return mValue == HIGH;
    }
};

#endif
