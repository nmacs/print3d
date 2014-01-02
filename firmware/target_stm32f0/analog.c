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

/* Total number of channels to be sampled by a single ADC operation.*/
#define ADC_GRP1_NUM_CHANNELS   2

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      1

/*
 * ADC samples buffer.
 */
static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];


/*
 * ADC conversion group.
 * Mode:        Linear buffer
 * Channels:    IN10   (41.5 cycles sample time)
 *              Sensor (239.5 cycles sample time)
 */
static const ADCConversionGroup adcgrpcfg = {
  FALSE,
  ADC_GRP1_NUM_CHANNELS,
  NULL, // adccb,  // callback
  NULL
#if 0
  ,
  /* HW dependent part.*/
  0,
  ADC_CR2_TSVREFE,
  ADC_SMPR1_SMP_AN10(ADC_SAMPLE_41P5) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_239P5),
  0,
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN10) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)
#endif

//STM32F0xx
	,ADC_CFGR1_RES_10BIT  	// ADC CFGR1 
	,0						// ADC TR 
	,ADC_SMPR_SMP_28P5  	// ADC SMPR
	,(1<<1) | (1<<2)		// ADC CHSELR
	
};



void analog_init(void)
{
	// A1, A2


  /*
   * Initializes the ADC driver 1.
   * 
   */
  adcStart(&ADCD1, NULL);
  palSetGroupMode(GPIOA, PAL_PORT_BIT(1) | PAL_PORT_BIT(2), 0, PAL_MODE_INPUT_ANALOG);
	
}

uint16_t	analog_read(uint8_t index)
{
	msg_t result;
	
	result = adcConvert (&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH); 
	
	//TODO
	return samples[1-index];
}