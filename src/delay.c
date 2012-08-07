#include "delay.h"

void delay_ms(const unsigned char n)
{
  if(n==0)
    return;

  // NOTE: this loop waits 1ms on 24MHz oscilator - you have to
  //       rework it when used with other oscilators!
  __asm
    mov r0,dpl  ; get n
    ; loop for given ms count
00001$:

    ; loop for one ms
    mov r1,#4
00003$:

    ; loop for 1/4 ms
    mov r2,#250
00002$:
    djnz r2,00002$

    djnz r1,00003$

    djnz r0,00001$
  __endasm;
}
