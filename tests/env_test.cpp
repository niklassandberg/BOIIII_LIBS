#define MOCK_ARDUINO 

#include "../BOENV.h"

#include <cstddef>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

#define NR_TEST_POINTS 21

//TODO: test class for testEnv and morpher.
//      remove speed parameter or simular. Make att and dec v/oct.
//
/*
class Morph
{
    const size_t TO_ZERO_Y;
    const size_t FROM_ZERO_Y;

    const size_t ROOF;

    Morph( size_t slideMax, size_t nrOfMorph ) :
        TO_ZERO_Y( (slideMax/nrOrMorph) - 1 ),
};
*/

void testEnv(int argc, char *argv[])
{
    BoEnvCore boEnv;
    boEnv.attack( (uint8_t) atoi(argv[1]));
    boEnv.decay( (uint8_t) atoi(argv[2]));
    boEnv.slope( (uint8_t) atoi(argv[3]));
    boEnv.speed(atoi(argv[4]));

    for(float output = 0.0; ! boEnv.hasEnded() ; output = boEnv())
    {
        cout << "|" << int( output * 127.f );
    }
}

/*
float shape(uint16_t x)
{
    float ret;
    if( x < 255 )
        ret = 255 - x;
    else if( x > 768 )
        ret = x - 768;
    else
        ret = 0;
    return ret/255.f;
}

//x: 0 - 2^10
//offset: 0 - 3
float morph(int x, int offset)
{
    offset *= 256;
    int calc = x - offset;
    if( calc < 0 )
        x = 1024 + calc;
    else
        x = calc;
    return shape(x);
}

void testMorph(int argc, char *argv[])
   uint16_t all[1024];
    for(size_t i = 0; i < 1024; ++i) all[i] = 0;
    for(size_t output = 0; output < 4; ++output)
    {
        for(size_t i = 0; i < 1024; ++i)
            all[i] += int( (morph(i,output)*256.f)+.5 );
    }
    for(size_t i = 0; i < 1024; ++i)
        cout << "|" << all[i];

    cout << endl << endl;


    for(size_t output = 0; output < 4; ++output)
        cout << "|" <<  int( morph(output*150,output)*256.f );

}
*/

int main(int argc, char *argv[])
{
    testEnv( argc, argv);
    return 0;
}
