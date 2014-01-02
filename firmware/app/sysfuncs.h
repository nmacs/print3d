#ifndef	_SYSFUNCS_H
#define	_SYSFUNCS_H


#include <stdint.h>


// enable interrupts
void enable_irq (void);
// disable interrupts
void disable_irq (void);
 
// enter a critical section
void enter_critical (void);

// leave a critical section
void leave_critical (void);


#define	MEMORY_BARRIER() asm volatile("" ::: "memory")

#if 0 
#define CLI_SEI_BUG_MEMORY_BARRIER()
extern uint8_t SREG;
#endif

#define PROGMEM

#endif	/* _SYSFUNCS_H */
