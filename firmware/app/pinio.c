#ifdef STM32
#include 	"iofuncs.h"
#endif
#include	"pinio.h"
#include	"delay.h"

static char ps_is_on = 0;

/// step/psu timeout
volatile uint8_t	psu_timeout = 0;

void power_on() {
	if (ps_is_on == 0) {
		#ifdef POWER_LED_PIN
			WRITE(POWER_LED_PIN, 1);
		#endif
		#ifdef	PS_ON_PIN
		#ifdef PS_INVERT_ON
			WRITE(PS_ON_PIN, 1);
		#else
			WRITE(PS_ON_PIN, 0);
		#endif
			SET_OUTPUT(PS_ON_PIN);
			delay_ms(500);
		#endif
    #ifdef PS_MOSFET_PIN
      WRITE(PS_MOSFET_PIN, 1);
      delay_ms(10);
    #endif
		ps_is_on = 1;
	}

	psu_timeout = 0;
}

void power_off() {
	stepper_disable();
	x_disable();
	y_disable();
	z_disable();
	e_disable();
	
	#ifdef POWER_LED_PIN
		WRITE(POWER_LED_PIN, 0);
	#endif

	#ifdef	PS_ON_PIN
	#ifdef PS_INVERT_ON
		WRITE(PS_ON_PIN, 0);
	#else
		WRITE(PS_ON_PIN, 1);
	#endif
	#endif

  #ifdef PS_MOSFET_PIN
    WRITE(PS_MOSFET_PIN, 0);
  #endif

	ps_is_on = 0;
}
