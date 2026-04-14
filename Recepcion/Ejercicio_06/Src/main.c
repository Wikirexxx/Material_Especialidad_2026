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
volatile uint8_t key_in[2];
uint8_t punt_key = 0;
uint8_t vec_datos[4];
uint8_t cont = 0;
float dbg_captura = 0;

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
	desc_data_t dato_uart;
    if (USART3->SR & 0x20)          // RXNE
    {
        rx_data = (uint8_t)USART3->DR;   // leer DR limpia RXNE
        if(key_in[0] == 'i' && key_in[1] == 'n')
        {
        	vec_datos[cont] = (uint8_t)(rx_data);
        	cont++;
        	if(cont >= 4)
        	{
        		cont = 0;
        		punt_key = 0;
        		key_in[0] = 0;
        		key_in[1] = 0;
        		dato_uart.bytes_2_send[3] = vec_datos[0];
        		dato_uart.bytes_2_send[2] = vec_datos[1];
        		dato_uart.bytes_2_send[1] = vec_datos[2];
        		dato_uart.bytes_2_send[0] = vec_datos[3];
        		dbg_captura = dato_uart.f;
        	}
        }
        if(rx_data == 'i' && punt_key == 0)
        {
        	key_in[punt_key] = rx_data;
        	punt_key = 1;
        }
        if(key_in[0] == 'i' && rx_data == 'n' && punt_key == 1)
        {
        	key_in[punt_key] = rx_data;
			punt_key = 2;
        }
        else
        {
        	if(punt_key != 2 && key_in[0] != 'i' && key_in[1] != 'n' )
        	{
        		key_in[0] = 0;
        		punt_key = 0;
        	}
        }
    }
}
