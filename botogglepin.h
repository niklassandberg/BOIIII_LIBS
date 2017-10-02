/* 
   Modified code from David A. Mellis to fit uint8_to a class.
   Found in https://www.arduino.cc/en/tutorial/switch
   
   switch

   Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
   press), the output pin is toggled from LOW to HIGH or HIGH to LOW.  There's
   a minimum delay between toggles to debounce the circuit (i.e. to ignore
   noise).

   David A. Mellis
   21 November 2006
*/
class TogglePin {
private:
  typedef void(*statef_t)(bool);

  uint8_t mPin; // the number of the input pin
  uint8_t mPrevious; // the previous reading from the input pin
  uint8_t mState; // the current state of the output pin
  
  // the follow variables are uint16_t's because the time, measured in miliseconds,
  // will quickly become a bigger number than can be stored in an uint8_t.
  uint16_t mTime; // the last time the output pin was toggled
  uint32_t mDebounce; // the debounce time, increase if the output flickers

  statef_t mCallback;

public:
  TogglePin(uint8_t pin, statef_t stateFunc, uint16_t debounce, bool highOnStart = false) :
    mPin(pin),
    mCallback(stateFunc),
    mTime(0),
    mPrevious((highOnStart) ? LOW : HIGH),
    mState((highOnStart) ? HIGH : LOW),
    mDebounce(debounce)
  {
    pinMode(pin, INPUT);  
  }

  // if the input just went from LOW and HIGH and we've waited uint16_t enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time    
  void operator()() {
    uint8_t reading = digitalRead(mPin);
    if (reading == HIGH && mPrevious == LOW && millis() - mTime > mDebounce) {
      mState = ! mState;
      mCallback(mState);
      mTime = millis();
    }
    mPrevious = reading;
  }
};
