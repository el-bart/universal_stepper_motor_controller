#ifndef INCLUDE_INTERRUPTS_H_FILE
#define INCLUDE_INTERRUPTS_H_FILE

#include "uC.h"
#include "delay.h"

volatile char g_dir=NONE_DIR;

// interrupt for INT0
void handle_int0(void) __interrupt(0) // __using(1)
{
  g_dir=LEFT_DIR;
}

// interrupt for INT1
void handle_int1(void) __interrupt(2) // __using(1)
{
  g_dir=RIGHT_DIR;
}

#endif
