// ============================ INCLUDES C ============================
#define STM32F405xx
#include "stm32f4xx.h"

#include <stdint.h>
#include <stdlib.h>
#include <math.h>
// ============================ INCLUDES PROPIOS ============================
#include "system_clock_if.h"
#include "usart_if.h"
#include "adc_if.h"

typedef union{
	float f;
	uint8_t bytes_2_send[4];
}desc_data_t;

uint16_t capturas[3];
uint16_t adc_0 = 0;
uint16_t adc_1 = 0;

float volts_f_0 = 0;
float volts_f_1 = 0;

volatile uint8_t rx_data;

void config_uc(void);

int main(void)
{
	uint32_t i = 0;
	desc_data_t desc_t;
    config_uc();
    while (1)
    {
    	adc_STM32.read(capturas);
    	adc_0 = capturas[0];
    	adc_1 = capturas[1];
    	//convertir a voltaje -> flotante
    	volts_f_0 = (adc_0 * 3.3) / 4095;
    	volts_f_1 = (adc_1 * 3.3) / 4095;
    	//descomponer valor
    	usart3_STM32.w_byte('i');
    	desc_t.f = volts_f_0;
    	usart3_STM32.w_byte(desc_t.bytes_2_send[3]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[2]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[1]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[0]);
    	desc_t.f = volts_f_1;
    	usart3_STM32.w_byte(desc_t.bytes_2_send[3]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[2]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[1]);
    	usart3_STM32.w_byte(desc_t.bytes_2_send[0]);
    	//enviarlo
    	for(i = 0 ; i < 1000000 ; i++)
    	{}
    }
}
void config_uc(void)
{
    SYSCLK_STM32.clear_flags();
    SYSCLK_STM32.en_fpu();
    SYSCLK_STM32.init();
    usart3_STM32.init();//Inicialización de USART3 (PB10 Rx - PB11 Tx)
    adc_STM32.config();
}
void USART3_IRQHandler(void)
{
    if (USART3->SR & 0x20)          // RXNE
    {
        rx_data = (uint8_t)USART3->DR;   // leer DR limpia RXNE
    }
}
