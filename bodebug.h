//#ifdef _BO_DEBUG_H_
//#define _BO_DEBUG_H_

//#define BODEBUG

#define SETOVERLAP 1
#define ALLPEGIATOR 2
#define CURRENT_TONE 4

#define DEBUG_MASK ALLPEGIATOR

#ifdef BODEBUG
#define DEBUG_START(x) Serial.begin(x);
#define DEBUG(toDebug,x) if( toDebug & DEBUG_MASK ) Serial.println(x);
#define DEBUG_2(toDebug,x,y) if( toDebug & DEBUG_MASK ) Serial.print(x); Serial.println(y);
#define DEBUG_3(toDebug,x,y,z) if( toDebug & DEBUG_MASK ) Serial.print(x); Serial.print(y); Serial.println(z);

#else
#define DEBUG_START(x)
#define DEBUG(toDebug,x)
#define DEBUG_2(toDebug,x,y)
#define DEBUG_3(toDebug,x,y,z)

#endif

//#endif //_BO_DEBUG_H_
