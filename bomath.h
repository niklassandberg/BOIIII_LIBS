#ifndef _AVR_MATH_H_
#define _AVR_MATH_H_

uint16_t inline mulu8x8_16(uint8_t x, uint8_t y)
{
  uint16_t res;
  asm volatile (
  "mul %A1, %A2 \n\t"
  "movw %A0, __tmp_reg__ \n\t"
  "clr r1 \n\t"
  :
  "=&r" (res)
  :
  "a" (x),
  "a" (y)
  );
  return res;

} 

uint32_t inline mulu8x16_24(uint8_t uint8in, uint16_t uint16in)
{
  uint32_t res;
  asm volatile (
  "clr %D0 \n\t"
  "clr %C0 \n\t"
  "mul %A1, %A2 \n\t"
  "movw %A0, __tmp_reg__ \n\t"
  "mul %A1, %B2 \n\t"
  "add %B0, __tmp_reg__ \n\t"
  "adc %C0, __zero_reg__ \n\t"
  "clr r1 \n\t"
  :
  "=&r" (res)
  :
  "a" (uint8in),
  "a" (uint16in)
  );
  return res;
}

inline uint16_t mulu8x16div8_16(uint8_t uint8in, uint16_t uint16in)
{
  uint16_t res;
  asm volatile (
  "clr %B0 \n\t"
  "mul %A1, %A2 \n\t"
  "mov %A0, __zero_reg__ \n\t"
  "mul %A1, %B2 \n\t"
  "add %A0, __tmp_reg__ \n\t"
  "adc %B0, __zero_reg__ \n\t"
  "clr r1 \n\t"
  :
  "=&r" (res)
  :
  "a" (uint8in),
  "a" (uint16in)
  );
  return res;
}

#endif
