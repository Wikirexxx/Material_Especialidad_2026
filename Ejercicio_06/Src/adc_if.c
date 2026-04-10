#include "adc_if.h"
#include "adc_driver.h"

const adc_f_t adc_STM32={
	.config = ADC1_Init_3Channels_PA0_PA1_PA2,
	.read = ADC1_Read_3Channels
};
