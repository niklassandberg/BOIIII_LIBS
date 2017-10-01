#ifndef _BO_PINS_H_
#define _BO_PINS_H_

struct Pin {

  typedef void (*pinfunction_t)(uint16_t);

  uint8_t mPin;
  uint16_t mValue;
  pinfunction_t mFunc;
  
  Pin(uint8_t pin, pinfunction_t func ) : mPin(pin), mValue(), mFunc(func)
  {
    pinMode(pin,INPUT);
  }
  
  void operator()()
  {
    uint16_t value = analogRead(mPin);
    if( value != mValue )
    {
      mFunc(value);
      mValue = value;
    }
  }
};

#endif
