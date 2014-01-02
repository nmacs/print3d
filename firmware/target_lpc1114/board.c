
#include "ch.h"
#include "hal.h"

/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
#if HAL_USE_PAL || defined(__DOXYGEN__)
const PALConfig pal_default_config = {
 {VAL_GPIO0DATA, VAL_GPIO0DIR},
 {VAL_GPIO1DATA, VAL_GPIO1DIR},
 {VAL_GPIO2DATA, VAL_GPIO2DIR},
 {VAL_GPIO3DATA, VAL_GPIO3DIR},
};
#endif

/*
 * Early initialization code.
 * This initialization must be performed just after stack setup and before
 * any other initialization.
 */
void __early_init(void) {

  lpc111x_clock_init();
}

/*
 * Board-specific initialization code.
 */
void boardInit(void) {

  /*
   * Extra, board-specific, initializations.
   */
  LPC_IOCON->PIO0_7 = 0xC0;             /* Disables pull-up on LED output. */
}
