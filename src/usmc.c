#include "uC.h"
#include "init.h"
#include "idle.h"
#include "motor.h"
#include "delay.h"
#include "interrupts.h"


void process_normal(void)
{
  switch(g_dir)
  {
    case LEFT_DIR:
      motor_step_left();
      break;

    case RIGHT_DIR:
      motor_step_right();
      break;

    case NONE_DIR:
    detault:
      // oops?!
      break;
  }
}

void process_turbo(void)
{
  switch(g_dir)
  {
    case LEFT_DIR:
      while(LEFT_PIN==0)
        motor_step_left();
      break;

    case RIGHT_DIR:
      while(RIGHT_PIN==0)
        motor_step_right();
      break;

    case NONE_DIR:
    default:
      // oops?!
      break;
  }
}


void main(void)
{
  // initialize uC
  init_base();
  init_motor();
  init_interrupts();

  // do the work
  for(;;)
  {
    // ligh up led (in case it's not done yet)
    LED_PIN=0;

    // process in turbo/normal mode
    if(TURBO_PIN)
      process_turbo();
    else
      process_normal();

    // wait until both buttons are released
    while(LEFT_PIN==0 || RIGHT_PIN==0)
    {
    }
    // nivelate mechanical buttons side-effects
    delay_ms(80);

    // go to idle mode (to save power)
    g_dir=0;        // mark that nothing happens now
    EA   =1;        // enable interrupts
    idle_mode();    // go to power save mode (will wake on interrupt)
    EA   =0;        // ok - buttin is pressed - not more interrupts for now
  } // for(ever)
}
