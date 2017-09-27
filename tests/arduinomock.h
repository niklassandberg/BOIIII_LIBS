#ifndef _ARDUINO_MOCK_H
#define _ARDUINO_MOCK_H

#define LOW 0
#define HIGH 255

#define INPUT 0
#define OUTPUT 1

//TODO: bad define
//typedef int size_t;
#define uint16_t unsigned int
#define uint8_t unsigned char

static int gPinRW[100];

void pinMode( int pin, int type );
int digitalRead(int pin);
void digitalWrite( int pin, int value );
int analogRead(int pin);
long map(long x, long in_min, long in_max, long out_min, long out_max);

#endif
