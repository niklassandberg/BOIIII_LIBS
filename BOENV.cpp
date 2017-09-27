#include "BOENV.h"

double cubicInterpolate(
        double y0,double y1,
        double y2,double y3,
        double mu)
{
    double a0,a1,a2,a3,mu2;

    mu2 = mu*mu;
    a0 = y3 - y2 - y0 + y1;
    a1 = y0 - y1 - a0;
    a2 = y2 - y0;
    a3 = y1;

    return(a0*mu*mu2+a1*mu2+a2*mu+a3);
}

double linearInterpolate(
        double y1,double y2,
        double mu)
{
    return(y1*(1.0-mu)+y2*mu);
}

float calcExp(float x)
{
    return x*x*x*x;
}

BoEnvCore::BoEnvCore() :
    mPosition(0.0), mStartValue(0.0),
    mEnvPart(ENVPART::ATTACK)
{
    speed(64);
    speed2(0);
    decay(64);
    attack(64);
    slope(64);
}

float BoEnvCore::getMoment(float lin, float slope)
{
    return ( ( 1.0 - slope ) * ( 1.0 - calcExp(1.0-lin) ) + slope *  calcExp(lin) );
}

float BoEnvCore::getPart()
{
    mPosition += mSpeed * mSpeed2 * ( (mEnvPart == ENVPART::ATTACK) ? mAttack : mDecay ) ;
    while(mPosition >= 1.0)
    {
        if(!hasEnded())
            ++mEnvPart;
        mPosition = 1.0 - mPosition;
    }
    return mPosition;
}

float  BoEnvCore::operator()()
{
    if(hasEnded()) return 0.0;
    float pos = getPart();
    switch(mEnvPart)
    {
        case ENVPART::ATTACK :
            return getMoment(pos, mAttackSlope);
        case ENVPART::DECAY :
            return getMoment(1.0-pos, mDecaySlope);
    }
    return 0;
}

void BoEnvCore::setStartValue(float value)
{
    mStartValue = value;
}

bool BoEnvCore::hasEnded()
{
    return mEnvPart == ENVPART::END;
}

bool BoEnvCore::hasAttackEnded()
{
    return mEnvPart > ENVPART::ATTACK;
}

void BoEnvCore::retrig()
{
    mEnvPart = ENVPART::ATTACK;
    mPosition = 0;
}
