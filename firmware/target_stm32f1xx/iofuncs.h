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

// --------------------------------------------------------------------------
// Defines
// --------------------------------------------------------------------------

#define PIN_DEF(port,pin) (port)<<5 | (pin)
#define GET_PORT(port_pin) ((port_pin)>>5)
#define GET_PIN(port_pin) ((port_pin)&0x1F)

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2

#define PIO_0 0
#define PIO_1 1
#define PIO_2 2

// --------------------------------------------------------------------------
// Types
// --------------------------------------------------------------------------

typedef uint8_t port_t;
// --------------------------------------------------------------------------
// Public Variables
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
// Public functions
// --------------------------------------------------------------------------

void WRITE (port_t port_pin, uint8_t val);

uint8_t READ (port_t port_pin);

void SET_OUTPUT(port_t port_pin);

void SET_INPUT(port_t port_pin);

//
void PWM_SET_VALUE (uint8_t channel, uint16_t width);

// --------------------------------------------------------------------------
//
// --------------------------------------------------------------------------

#endif // _IOFUNCS_H

