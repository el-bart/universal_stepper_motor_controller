#ifndef INCLUDE_INIT_H_FILE
#define INCLUDE_INIT_H_FILE

// first init call to be made
extern void init_base(void);

// init stepper motor controller
extern void init_motor(void);

// init interrupts
extern void init_interrupts(void);

#endif
