/* Copyright (c) 2012 Bob Cousins bobcousins42@googlemail.com              */
/* **************************************************************************
   All rights reserved.

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
****************************************************************************/
// **************************************************************************
// Description:
//
// **************************************************************************

#ifndef _IOFUNCS_H
#define _IOFUNCS_H

// --------------------------------------------------------------------------
// Includes
// --------------------------------------------------------------------------

#include <stdint.h>
#include "config.h"

// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------

// 5 bits - pin number
// 3 bits - port number
//

#define PIN_OFFSET  0
#define PIN_MASK    (0x1F << PIN_OFFSET)

#define PORT_OFFSET 5
#define PORT_MASK   (0x7 << PORT_OFFSET)

#define PWM_OFFSET  8
#define PWM_MASK    (0x7 << PWM_OFFSET)

#define PIN_DEF(port, pin)                     (((pin) << PIN_OFFSET) | ((port) << PORT_OFFSET))
#define PIN_DEF_PWM(port, pin, pwm)            (((pin) << PIN_OFFSET) | ((port) << PORT_OFFSET) | ((pwm) << PWM_OFFSET))

#define GET_PORTN(port_pin)                    (((port_pin) & PORT_MASK) >> PORT_OFFSET)
#define GET_PORT(port_pin)                     (GET_PORTN(port_pin) == PORT_A ? GPIOA : (GET_PORTN(port_pin) == PORT_B ? GPIOB : GPIOC))
#define GET_PIN(port_pin)                      (((port_pin) & PIN_MASK) >> PIN_OFFSET)
#define GET_PWM(port_pin)                      (((port_pin) & PWM_MASK) >> PWM_OFFSET)

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

typedef unsigned port_t;

// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

void iofuncsInit(void);

void WRITE (port_t port_pin, uint8_t val);

uint8_t READ (port_t port_pin);

void TOGGLE (port_t port_pin);

void SET_OUTPUT(port_t port_pin);

void SET_INPUT(port_t port_pin);

void PWM_SET_VALUE (port_t port_pin, uint8_t value);

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

#endif // _IOFUNCS_H

