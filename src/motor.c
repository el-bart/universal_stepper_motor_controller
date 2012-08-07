#include <stdlib.h>

#include "motor.h"
#include "delay.h"
#include "uC.h"

#define EOUT0    (1<<6) // P1_6
#define EOUT1    (1<<5) // P1_5
#define EOUT2    (1<<7) // P1_7
#define EOUT3    (1<<4) // P1_4
#define ENG_MASK (EOUT0|EOUT1|EOUT2|EOUT3)  // mask for engine pins

// state tables for bipolar engine
static const unsigned char g_steps_bipolar []={EOUT0, EOUT2, EOUT1, EOUT3};
// state tables for unipolar engine
static const unsigned char g_steps_unipolar[]={EOUT0, EOUT1, EOUT2, EOUT3};

// state tables in use
static const unsigned char *g_steps=NULL;
static int                  g_step =0;

static void set_state(const unsigned char state)
{
  // NOTE: we can write to whole P1 port, since board design
  //       does NOT use any of the remaining pins, thus their
  //       state is not relevant.

  // enable given engines
  P1=state&ENG_MASK;

  // wait a while to ensure proper engine move
  // (blink led to inform about hte event)
  LED_PIN=0;
  delay_ms(20);
  LED_PIN=1;
  delay_ms(20);
  LED_PIN=0;

  // turn off all engines
  P1=~ENG_MASK;
}

void motor_bipolar(void)
{
  g_steps=g_steps_bipolar;
  g_step =0;
  // turn off all engines
  P1=~ENG_MASK;
}

void motor_unipolar(void)
{
  g_steps=g_steps_unipolar;
  g_step =0;
  // turn off all engines
  P1=~ENG_MASK;
}

void motor_step_left(void)
{
  --g_step;
  if(g_step<0)
    g_step=3;

  set_state(g_steps[g_step]);
}

void motor_step_right(void)
{
  ++g_step;
  if(g_step>3)
    g_step=0;

  set_state(g_steps[g_step]);
}
