#ifndef _BO_ENV_H_
#define _BO_ENV_H_

#ifdef MOCK_ARDUINO
#include "unittest/arduinomock.h"
#else
#include "Arduino.h"
#endif

double cubicInterpolate( double y0,double y1, double y2,double y3, double mu);
double linearInterpolate( double y1,double y2, double mu);
float calcExp(float x);

namespace ENVPART
{
    const uint8_t ATTACK = 0;
    const uint8_t DECAY = 1;
    const uint8_t END = 2;
};

class BoEnvCore
{
    typedef uint8_t EnvPart_t;

    float mPosition;

    float mStartValue;

    float mAmp;
    float mAttack;
    float mAttackSlope;
    float mDecay;
    float mDecaySlope;

    float mSpeed;
    float mSpeed2;

    EnvPart_t mEnvPart;

    float getMoment(float lin, float slope);
    float getPart();

public:

    BoEnvCore();

    float operator()();

    void setStartValue(float value);
    bool hasEnded();
    bool hasAttackEnded();
    void retrig();

    float calcParams(uint8_t value)
    {
        return 1/float(value+1);
    }

    void attack(uint8_t value)
    {
        mAttack = calcParams(value);
    }

    void decay(uint8_t value)
    {
        mDecay = calcParams(value);
    }

    void balance(uint8_t value)
    {
        attack(value);
        decay(127.0-value);
    }

    void speed(uint8_t value)
    {
        mSpeed = (1/float(128.0-value));//*0.25;
    }

    void speed2(uint8_t value)
    {
        mSpeed2 = 32.0*float(value)/127.0 + (1.0/16.0); //1-4
    }

    void slope(uint8_t value)
    {
        mAttackSlope = float(value)/127.0;
        mDecaySlope = mAttackSlope;
    }
};

#endif
