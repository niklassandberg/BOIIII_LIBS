#ifndef _BO_PINS_H_
#define _BO_PINS_H_

struct AnalogPin {

  typedef void (*pinfunction_t)(uint16_t);

  uint8_t mPin;
  uint16_t mValue;
  pinfunction_t mCallback;

 
  void update()
  {
    uint16_t value = analogRead(mPin);
    if( value != mValue )
    {
      mCallback(value);
      mValue = value;
    }
  }

  
  AnalogPin(uint8_t pin, pinfunction_t func ) : mPin(pin), mValue(), mCallback(func)
  {
    pinMode(pin,INPUT);
    update();
  }
  
  void operator()()
  {
    update();
  }
};

#endif
