#ifndef _DIGITAL_GATE_H_
#define _DIGITAL_GATE_H_

class DigitalGate
{
    typedef void(*changedf_t)(bool);
    typedef void(*not_changedf_t)(void);

    uint8_t mInputPin;
    uint8_t mPrevValue;
    bool mChanged;

    changedf_t mChangedFunc;
    not_changedf_t mNotChangedFunc;

  public:
    DigitalGate(uint8_t inputPin, changedf_t changedfunc, not_changedf_t notchangedfunc) :
      mInputPin(inputPin), mPrevValue(LOW), mChanged(false),
      mChangedFunc(changedfunc), mNotChangedFunc(notchangedfunc)
    {
      pinMode( inputPin, INPUT );
    }

    void operator()()
    {
      uint8_t value = digitalRead(mInputPin);
      if ( value != mPrevValue )
      {
        mChangedFunc(value==HIGH);
        mChanged = true;
      }
      else if(mChanged)
      {
        mNotChangedFunc();
        mChanged = false;
      }
      mPrevValue = value;
    }
};

#endif
