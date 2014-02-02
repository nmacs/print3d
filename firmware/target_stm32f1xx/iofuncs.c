/* Copyright (c) 2012 Bob Cousins bobcousins42@googlemail.com       */
/* All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/
// **************************************************************************
// Description:
//
// **************************************************************************

// --------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------

#include "ch.h"
#include "hal.h"
#include "iofuncs.h"

// --------------------------------------------------------------------------
// Externals
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Local defines
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Private Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Function prototypes
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Private functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

static port_t pwm_pins[PWM_CHANNELS];

static void pwmpcb(PWMDriver *pwmp)
{
  int i;
  (void)pwmp;
  for (i = 0; i < PWM_CHANNELS; i++) {
      if (pwm_pins[i] != 0) {
          WRITE(pwm_pins[i], 0);
      }
  }
}

static void pwmc0cb(PWMDriver *pwmp)
{
  (void)pwmp;
  if (pwm_pins[0] != 0)
      WRITE(pwm_pins[0], 1);
}

static void pwmc1cb(PWMDriver *pwmp)
{
  (void)pwmp;
  if (pwm_pins[1] != 0)
      WRITE(pwm_pins[1], 1);
}

static void pwmc2cb(PWMDriver *pwmp)
{
  (void)pwmp;
  if (pwm_pins[2] != 0)
      WRITE(pwm_pins[2], 1);
}

static void pwmc3cb(PWMDriver *pwmp)
{
  (void)pwmp;
  if (pwm_pins[3] != 0)
      WRITE(pwm_pins[3], 1);
}

static PWMConfig pwmcfg = {
  1000,                                    /* 2Hz PWM clock frequency.   */
  1000,                                    /* Initial PWM period 1S.       */
  pwmpcb,
  {
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc0cb},
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb},
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc2cb},
   {PWM_OUTPUT_ACTIVE_HIGH, pwmc3cb}
  },
  0,
#if STM32_PWM_USE_ADVANCED
  0
#endif
};

void iofuncsInit(void)
{
  pwmStart(&PWMD2, &pwmcfg);
}

// --------------------------------------------------------------------------
//! @brief
//! @param[in]
//! @param[out]
//! @return
// --------------------------------------------------------------------------

// target specific
void WRITE (port_t port_pin, uint8_t val)
{
        palWritePad (GET_PORT(port_pin), GET_PIN(port_pin), val);
}

uint8_t READ (port_t port_pin)
{
        return palReadPad (GET_PORT(port_pin), GET_PIN(port_pin));
}

void TOGGLE (port_t port_pin)
{
        palTogglePad (GET_PORT(port_pin), GET_PIN(port_pin));
}

void SET_OUTPUT(port_t port_pin)
{
        palSetPadMode (GET_PORT(port_pin), GET_PIN(port_pin), PAL_MODE_OUTPUT_PUSHPULL);
}

void SET_INPUT(port_t port_pin)
{
        palSetPadMode(GET_PORT(port_pin), GET_PIN(port_pin), PAL_MODE_INPUT_PULLUP);
}

void PWM_SET_VALUE (port_t port_pin, uint8_t value)
{
    if (pwm_pins[GET_PWM(port_pin)] == 0)
      pwm_pins[GET_PWM(port_pin)] = port_pin;
    if (value == 255) {
        pwmDisableChannel(&PWMD2, GET_PWM(port_pin));
        WRITE(port_pin, 1);
    }
    else if (value > 0)
      pwmEnableChannel(&PWMD2, GET_PWM(port_pin), PWM_FRACTION_TO_WIDTH(&PWMD2, 255, 255 - value));
    else {
      pwmDisableChannel(&PWMD2, GET_PWM(port_pin));
      WRITE(port_pin, 0);
    }
}
