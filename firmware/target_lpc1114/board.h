
#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for a LPC1114 
 */

/*
 * Board identifiers.
 */
#define BOARD_LPC1114
#define BOARD_NAME "Gen7-ARM with LPC1114"

/*
 * Board frequencies.
 */
#define SYSOSCCLK               12000000

/*
 * SCK0 connection on this board.
 */
//#define LPC11xx_SPI_SCK0_SELECTOR SCK0_IS_PIO2_11

/*
 * GPIO 0 initial setup.
 */
#define VAL_GPIO0DIR			0x00000000            
                                
#define VAL_GPIO0DATA			0x00000000           

/*
 * GPIO 1 initial setup.
 */
#define VAL_GPIO1DIR			0x00000000            
                                
#define VAL_GPIO1DATA			0x00000000           

/*
 * GPIO 2 initial setup.
 */
#define VAL_GPIO2DIR            0x00000000
#define VAL_GPIO2DATA           0x00000000

/*
 * GPIO 3 initial setup.
 */
#define VAL_GPIO3DIR            0x00000000
#define VAL_GPIO3DATA           0x00000000

/*
 * Pin definitions.
 */
 
#define PORT_LED1 	GPIO1
#define PIN_LED1 	9
 
//todo
#define PORT_LED2 		GPIO1
#define PIN_LED2		9

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
