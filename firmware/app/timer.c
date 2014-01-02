/* ========================================================================== */
/*                                                                            */
/*   Filename.c                                                               */
/*   (c) 2001 Author                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */


#include "ch.h"
#include "hal.h" 

#include "config.h"
#include "timer.h"

#ifdef	HOST
#include	"dda_queue.h"
#endif

/// 
#define		TICK_TIME_MS 	2


/// every time our clock fires, we increment this so we know when 10ms has elapsed
uint8_t						clock_counter_10ms = 0;
/// keep track of when 250ms has elapsed
uint8_t						clock_counter_250ms = 0;
/// keep track of when 1s has elapsed
uint8_t						clock_counter_1s = 0;

/// flags to tell main loop when above have elapsed
volatile uint8_t	clock_flag_10ms = 0;
volatile uint8_t	clock_flag_250ms = 0;
volatile uint8_t	clock_flag_1s = 0;

static uint32_t timer1_interval;

// system tick 
static void timer3_Handler(GPTDriver *gptp);

GPTConfig gpt3cfg = {1000000,  // 1MHz clock? 
	timer3_Handler};

// stepper timer
static void timer1_Handler(GPTDriver *gptp);

GPTConfig gpt1cfg = {1000000,  // 1MHz clock? 
	timer1_Handler};


/// step timer
static void timer1_Handler(GPTDriver *gptp)
{   
    palTogglePad(PORT_LED1, PIN_LED1);
	//   
   	
   	queue_step();
   	
   	
}

/// system tick handler
static void timer3_Handler(GPTDriver *gptp)
{   
    palTogglePad(PORT_LED2, PIN_LED2);
   
	/*
	clock stuff
	*/
	clock_counter_10ms += TICK_TIME_MS;
	if (clock_counter_10ms >= 10) {
		clock_counter_10ms -= 10;
		clock_flag_10ms = 1;

		clock_counter_250ms++;
		if (clock_counter_250ms >= 25) {
			clock_counter_250ms = 0;
			clock_flag_250ms = 1;

			clock_counter_1s++;
			if (clock_counter_1s >= 4) {
				clock_counter_1s = 0;
				clock_flag_1s = 1;
			}
		}
	}
}  

void timer_init(void) 
{
  	// start system tick timer
	gptStart (&GPTD3, &gpt3cfg);
	gptStartContinuous (&GPTD3, TICK_TIME_MS * 1000);

	// start stepper timer
	timer1_interval = 50000; // nominal rate
	gptStart (&GPTD1, &gpt1cfg);
	//gptStartOneShot (&GPTD1, timer1_interval);
}

#define DIV (F_CPU/1000000)

void setTimer(uint32_t delay)
{
	timer1_interval = delay / DIV;
	if (dbg_is_isr())
	{
		chSysLockFromIsr();
	  	gptStartOneShotI(&GPTD1, timer1_interval);
	   	chSysUnlockFromIsr();
	}
	else
	{
		gptStopTimer (&GPTD1);
		gptStartOneShot (&GPTD1, timer1_interval);
	}
}

void setTimerI(uint32_t delay)
{
}

void timer_stop(void)
{
}