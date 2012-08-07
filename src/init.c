#include "init.h"
#include "motor.h"
#include "uC.h"

void init_base(void)
{
  // disable interrupts for time of configuration
  EA=0;

  // set turbo and mode pins high (i.e. input)
  TURBO_PIN=1;
  MODE_PIN =1;
}

void init_motor(void)
{
  if(MODE_PIN==0)
    motor_bipolar();
  else
    motor_unipolar();
}

void init_interrupts(void)
{
  // rise INT0, INT1 pins
  P3_2=1;
  P3_3=1;
  // set reaction on level (not edge) for INT0, INT1
  IT0 =0;
  IT1 =0;
  // enable interrupts from INT0, INT1
  EX0 =1;
  EX1 =1;
  EA  =1;
}
