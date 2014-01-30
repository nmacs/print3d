/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010,
                 2011,2012 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"
#include "iofuncs.h"
#include "config.h"
#include "max31855.h"

#if HAL_USE_PAL || defined(__DOXYGEN__)
/**
 * @brief   PAL setup.
 * @details Digital I/O ports static configuration as defined in @p board.h.
 *          This variable is used by the HAL when initializing the PAL driver.
 */
const PALConfig pal_default_config =
{
  {VAL_GPIOA_MODER, VAL_GPIOA_OTYPER, VAL_GPIOA_OSPEEDR, VAL_GPIOA_PUPDR,
   VAL_GPIOA_ODR,   VAL_GPIOA_AFRL,   VAL_GPIOA_AFRH},
  {VAL_GPIOB_MODER, VAL_GPIOB_OTYPER, VAL_GPIOB_OSPEEDR, VAL_GPIOB_PUPDR,
   VAL_GPIOB_ODR,   VAL_GPIOB_AFRL,   VAL_GPIOB_AFRH},
  {VAL_GPIOC_MODER, VAL_GPIOC_OTYPER, VAL_GPIOC_OSPEEDR, VAL_GPIOC_PUPDR,
   VAL_GPIOC_ODR,   VAL_GPIOC_AFRL,   VAL_GPIOC_AFRH}
};
#endif

/**
 * @brief   Early initialization code.
 * @details This initialization must be performed just after stack setup
 *          and before any other initialization.
 */
void __early_init(void) {
  stm32_clock_init();
}

#if HAL_USE_MMC_SPI || defined(__DOXYGEN__)
/**
 * @brief   MMC_SPI card detection.
 */
bool_t mmc_lld_is_card_inserted(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return TRUE;
}

/**
 * @brief   MMC_SPI card write protection detection.
 */
bool_t mmc_lld_is_write_protected(MMCDriver *mmcp) {

  (void)mmcp;
  /* TODO: Fill the implementation.*/
  return FALSE;
}
#endif

/**
 * @brief   Board-specific initialization code.
 * @todo    Add your board-specific code, if any.
 */
void boardInit(void) {
	SET_OUTPUT(BLUE_LED_PIN);
	SET_OUTPUT(GREEN_LED_PIN);

	palSetPadMode(GET_PORT(SSCK), 13, PAL_MODE_STM32_ALTERNATE_PUSHPULL);     /* SCK. */
	palSetPadMode(GET_PORT(SMISO), 14, PAL_MODE_STM32_ALTERNATE_PUSHPULL);    /* MISO.*/
	palSetPadMode(GET_PORT(SMOSI), 15, PAL_MODE_STM32_ALTERNATE_PUSHPULL);    /* MOSI.*/
}

static const SPIConfig extruder_sensor_spicfg = {
  NULL,
  GET_PORT(SS),
  GET_PIN(SS),
#if (STM32_PCLK1 == 24000000)
  SPI_CR1_BR_2 | SPI_CR1_BR_1 // F = (Fapb2 = 24MHz) / (128) = 187.5 kHz
#else
#error "Unknown clock"
#endif
};

struct max31855_plat_data extruder_sensor = {
    .bus = &SPID2,
    .config = &extruder_sensor_spicfg,
};



extern void emergency_stop(void);

void _unhandled_exception(void)
{
	emergency_stop();
}
