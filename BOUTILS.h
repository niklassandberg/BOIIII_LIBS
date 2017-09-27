#ifndef _BO_UTILS_H
#define _BO_UTILS_H

//Get free ram (function found at sparkfun)
int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

#endif
