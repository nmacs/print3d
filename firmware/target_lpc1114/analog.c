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

#include "analog.h"

#include "board.h"

// LPC1114
#include "lpc1114_adc.h"


#define SystemCoreClock 48000000	//probably

void analog_init(void)
{
	// use AD1 and AD2
	
  uint32_t i;

  /* Disable Power down bit to the ADC block. */  
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);

  /* Enable AHB clock to the ADC. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);

  /*  Bit 7 needs to be cleared according to design team. */
  
  LPC_IOCON->R_PIO1_0  &= ~0x8F;	
  LPC_IOCON->R_PIO1_0  |= 0x02;  /* ADC IN1 */
  LPC_IOCON->R_PIO1_1  &= ~0x8F;	
  LPC_IOCON->R_PIO1_1  |= 0x02;  /* ADC IN2 */
  
  LPC_IOCON->R_PIO1_0    = 0x02;	// Select AD1 pin function
  LPC_IOCON->R_PIO1_1    = 0x02;	// Select AD2 pin function

  // 
  LPC_ADC->CR = ((SystemCoreClock/LPC_SYSCON->SYSAHBCLKDIV)/ADC_CLK-1) << 8;

  /* If POLLING, no need to do the following */
#if CONFIG_ADC_ENABLE_ADC_IRQHANDLER==1
  NVIC_EnableIRQ(ADC_IRQn);
  LPC_ADC->INTEN = 0x1FF;		/* Enable all interrupts */
#endif

}

uint16_t	analog_read(uint8_t channelNum)
{
  uint32_t regVal, ADC_Data;
	
  // Index 0 -> AD1
  // Index 1 -> AD2
  channelNum = channelNum + 1;
	
  LPC_ADC->CR &= 0xFFFFFF00;
  LPC_ADC->CR |= (1 << 24) | (1 << channelNum);
  	
  /* switch channel,start A/D convert */

  while ( 1 )			/* wait until end of A/D convert */
  {
	regVal = *(volatile unsigned long *)(LPC_ADC_BASE + ADC_OFFSET + ADC_INDEX * channelNum);
	/* read result of A/D conversion */
	if ( regVal & ADC_DONE )
	{
	  break;
	}
  }	
        
  LPC_ADC->CR &= 0xF8FFFFFF;	/* stop ADC now */    
  if ( regVal & ADC_OVERRUN )	/* save data when it's not overrun, otherwise, return zero */
  {
	return 0;
  }
  ADC_Data = ( regVal >> 6 ) & 0x3FF;
  return  ADC_Data;

}