#ifndef ADC_IF_H_
#define ADC_IF_H_
#include <stdint.h>

typedef struct{
	void (*config)(void);
	void (*read)(uint16_t *buffer);
}adc_f_t;

extern const adc_f_t adc_STM32;

#endif
