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
#define ADC_GRP1_NUM_CHANNELS   1

/* Depth of the conversion buffer, channels are sampled four times each.*/
#define ADC_GRP1_BUF_DEPTH      1

/*
 * ADC samples buffer.
 */
static adcsample_t samples[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC conversion group.
 * Mode:        Linear buffer
 * Channels:    IN0   (41.5 cycles sample time)
 */
static const ADCConversionGroup adcgrpcfg = {
  FALSE,                              // Enables the circular buffer mode for the group.
  ADC_GRP1_NUM_CHANNELS,              // Number of the analog channels belonging to the conversion group.
  NULL,                               // Callback function associated to the group
  NULL,                               // Error callback
  0,                                  // ADC CR1 register initialization data
  0,                                  // ADC CR2 register initialization data
  0,                                  // ADC SMPR1 register initialization data
  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_41P5), // ADC SMPR2 register initialization data
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)
};



void analog_init(void)
{
  /*
   * Initializes the ADC driver 1.
   */
  adcStart(&ADCD1, NULL);
  palSetGroupMode(GPIOA, PAL_PORT_BIT(0), 0, PAL_MODE_INPUT_ANALOG);
}

uint16_t analog_read(uint8_t index)
{
	msg_t result;
	
	result = adcConvert (&ADCD1, &adcgrpcfg, samples, ADC_GRP1_BUF_DEPTH);
	
	//TODO
	return samples[index];
}
