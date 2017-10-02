template<uint8_t MODES>
class Mode
{
  typedef void(*modef_t)(void);

  const uint8_t mPin;
  const uint8_t mShift;
  
  uint8_t mModeIndex;
  modef_t mModes[MODES];

  uint8_t countShift()
  {
    uint8_t ret = 1;
    while( 1024 >> ret > MODES ) ++ret;
    return ret;
  }
public:
  Mode(uint8_t pin, modef_t firstMode) : mPin(pin), mModeIndex(0), mShift(countShift())
  {
    mModes[0] = firstMode;
  }

  modef_t& operator[](uint8_t index)
  {
    return mModes[index];
  }

  void operator()()
  {
    uint8_t modeIndex = analogRead(mPin) >> mShift;
    if(modeIndex != mModeIndex)
    {
      modef_t func = mModes[modeIndex];
      func();
    }
    mModeIndex = modeIndex;
  }
};
