#ifndef _ARDUINO_MOCK_H
#define _ARDUINO_MOCK_H

//Arduino IDE has it ways to compile files that it des not need. 
//Make it empty in that case
#include <iostream>

using namespace std;

#include <stdlib.h>

#define LOW 0
#define HIGH 255

#define INPUT 0
#define OUTPUT 1

#define uint32_t unsigned long
#define int16_t int
#define uint16_t unsigned int
#define uint8_t unsigned char

static int gPinRW[100];

void pinMode( int pin, int type );
int digitalRead(int pin);
void digitalWrite( int pin, int value );
int analogRead(int pin);
long map(long x, long in_min, long in_max, long out_min, long out_max);


/* initialize seed: */
long int random(size_t range);

#endif
