/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#include "sysfuncs.h"

uint8_t SREG;

// enable interrupts
void enable_irq (void)
{
	__asm volatile ("cpsie i");
}

// disable interrupts
void disable_irq (void)
{
	__asm volatile ("cpsid i");
}


#if 0
	uint8_t save_reg = SREG;
	cli();
	CLI_SEI_BUG_MEMORY_BARRIER();
	
	
		MEMORY_BARRIER();
	SREG = save_reg;
#endif


// disable interrupts etc
void enter_critical (void)
{
	disable_irq();
	//MEMORY_BARRIER()
}

// enable interrupts etc
void leave_critical (void)
{
	MEMORY_BARRIER();
	enable_irq();
}

	                                                              