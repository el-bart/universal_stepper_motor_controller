#include "idle.h"
#include "uC.h"

void idle_mode(void)
{
  // this is required by the documentation (probably to prevent
  // interrupt from A/D converter, which is disabled here any way).
  P1_0=0;
  P1_1=0;
  // it is required that instruction done before entering idle mode
  // does not write to port nor external memory.
  __asm
    nop
  __endasm;
  // now enter the idle mode!
  PCON|=IDL;
}
