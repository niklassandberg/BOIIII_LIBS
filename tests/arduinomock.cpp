#include "arduinomock.h"

void pinMode( int pin, int type )
{
	gPinRW[pin] = 0;
}

int digitalRead(int pin)
{
	return (gPinRW[pin]) > 128 ? HIGH : LOW;
}

int analogRead(int pin)
{
	return gPinRW[pin];
}

void digitalWrite( int pin, int value )
{
	gPinRW[pin] = value;
}

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

