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

// --------------------------------------------------------------------------
//! @brief
//! @param[in]
//! @param[out]
//! @return
// --------------------------------------------------------------------------

// target specific
void WRITE (port_t port_pin, uint8_t val)
{
	switch (GET_PORT(port_pin))
	{
	case 0: 
		palWritePad (GPIOA, GET_PIN(port_pin), val);
		break;
	case 1:
		palWritePad (GPIOB, GET_PIN(port_pin), val);
		break;
	case 2:
		palWritePad (GPIOC, GET_PIN(port_pin), val);
		break;
	}	
}

uint8_t READ (port_t port_pin)
{
	switch (GET_PORT(port_pin))
	{
	case 0: 
		return palReadPad (GPIOA, GET_PIN(port_pin));
		break;
	case 1:
		return palReadPad (GPIOB, GET_PIN(port_pin));
		break;
	case 2:
		return palReadPad (GPIOC, GET_PIN(port_pin));
		break;
	}	
}

void SET_OUTPUT(port_t port_pin)
{
	switch (GET_PORT(port_pin))
	{
	case 0: 
		palSetPadMode (GPIOA, GET_PIN(port_pin), PAL_MODE_OUTPUT_PUSHPULL);
		break;
	case 1:
		palSetPadMode (GPIOB, GET_PIN(port_pin), PAL_MODE_OUTPUT_PUSHPULL);
		break;
	case 2:
		palSetPadMode (GPIOC, GET_PIN(port_pin), PAL_MODE_OUTPUT_PUSHPULL);
		break;
	}	
}

void SET_INPUT(port_t port_pin)
{
	switch (GET_PORT(port_pin))
	{
	case 0: 
		palSetPadMode (GPIOA, GET_PIN(port_pin), PAL_MODE_INPUT_PULLUP);
		break;
	case 1:
		palSetPadMode (GPIOB, GET_PIN(port_pin), PAL_MODE_INPUT_PULLUP);
		break;
	case 2:
		palSetPadMode (GPIOC, GET_PIN(port_pin), PAL_MODE_INPUT_PULLUP);
		break;
	}	
}

//
void PWM_SET_VALUE (uint8_t channel, uint16_t width)
{
	//TODO
}