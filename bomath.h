#ifndef _AVR_MATH_H_
#define _AVR_MATH_H_

inline uint32_t mulu8x16_24(uint8_t uint8in, uint16_t uint16in)
{
  uint32_t res;
  asm volatile (
  "clr r16 \n\t"
  "mul %A1, %A2 \n\t"
  "movw %A0, r0 \n\t"
  "mov %C0, r16 \n\t"
  "mov %D0, r16 \n\t"
  "mul %A1, %B2 \n\t"
  "add %B0, r0 \n\t"
  "adc %C0, r1 \n\t"
  "adc %D0, r16 \n\t"
  "clr r1 \n\t"
  :
  "=&r" (res)
  :
  "a" (uint8in),
  "a" (uint16in)
  :
  "r16"
  );
  return res;
}

#endif
