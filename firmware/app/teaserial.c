
#include "ch.h"
#include "hal.h"

#include "config.h"

#include "pgmspace.h"
#include "serial.h"

// Note: this assumes default settings are 8 data bits, no parity, 1 stop bit
static const SerialConfig config =
{
#if defined (STM32F0XX)
  BAUD,
  0,
  0,
  0
#else // LPC1114 
  BAUD,
  LCR_WL8 | LCR_STOP1 | LCR_NOPARITY,
  FCR_TRIGGER0
#endif  
};
 
 
// initialise serial subsystem
void serial_init(void)
{
  /*
   * Activates the serial driver 1 using the driver default configuration.
   */
	tgt_serial_init();

    //sdObjectInit(&SD1, NULL, notify1);
	
  	sdStart(&SD1, &config);
}

// return number of characters in the receive buffer,
uint8_t serial_rxchars(void)
{
	if (sdGetWouldBlock (&SD1))
		return 0;
	else
		return 1;

}

// number of spaces in the send buffer
// uint8_t serial_txchars(void);

// read one character
uint8_t serial_popchar(void)
{
	char c;
	int num_bytes;
	
  	num_bytes = chSequentialStreamRead(&SD1, (uint8_t *)&c, 1);
  	if (num_bytes != 1)
  		c = 0xff;
  
  	return c;
}

// send one character
void serial_writechar(uint8_t data)
{
 	chSequentialStreamPut(&SD1, data);
}

// read/write many characters
// uint8_t serial_recvblock(uint8_t *block, int blocksize);
void serial_writeblock(void *data, int datalen)
{
}

void serial_writestr(uint8_t *data)
{
  	while (*data)
    	chSequentialStreamPut(&SD1, *data++);
}

// write from flash
void serial_writeblock_P(PGM_P data, int datalen)
{
}

void serial_writestr_P(PGM_P data)
{
  	while (*data)
    	chSequentialStreamPut(&SD1, *data++);
}
