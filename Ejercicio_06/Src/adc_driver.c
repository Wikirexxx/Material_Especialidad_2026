#define STM32F405xx
#include "stm32f4xx.h"


void ADC1_Init_3Channels_PA0_PA1_PA2(void)
{
	/* 1) Habilitar clocks */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	(void)RCC->AHB1ENR;
	(void)RCC->APB2ENR;

	/* 2) PA0, PA1, PA2 en modo analógico */
	GPIOA->MODER &= ~(
		(3U << (0U * 2U)) |
		(3U << (1U * 2U)) |
		(3U << (2U * 2U))
	);
	GPIOA->MODER |= (
		(3U << (0U * 2U)) |
		(3U << (1U * 2U)) |
		(3U << (2U * 2U))
	);

	/* Sin pull-up / pull-down */
	GPIOA->PUPDR &= ~(
		(3U << (0U * 2U)) |
		(3U << (1U * 2U)) |
		(3U << (2U * 2U))
	);

	/* 3) Apagar ADC antes de configurar */
	ADC1->CR1 = 0;
	ADC1->CR2 = 0;

	/* 4) Prescaler común del ADC: PCLK2 / 4
		  Si PCLK2 = 84 MHz -> ADCCLK = 21 MHz */
	ADC->CCR &= ~(3U << 16);
	ADC->CCR |=  (1U << 16);   /* ADCPRE = 01 */

	/* 5) Resolución 12 bits, alineación a la derecha */
	ADC1->CR1 &= ~ADC_CR1_RES;
	ADC1->CR2 &= ~ADC_CR2_ALIGN;

	/* 6) Modo scan habilitado */
	ADC1->CR1 |= ADC_CR1_SCAN;

	/* 7) Conversión simple por disparo software
		  (no continua, no trigger externo) */
	ADC1->CR2 &= ~ADC_CR2_CONT;
	ADC1->CR2 &= ~ADC_CR2_EXTEN;

	/* 8) EOC al final de cada conversión
		  Esto permite leer CH0, luego CH1, luego CH2 */
	ADC1->CR2 |= ADC_CR2_EOCS;

	/* 9) Tiempo de muestreo para canales 0,1,2 = 84 ciclos */
	ADC1->SMPR2 &= ~(
		(7U << (0U * 3U)) |
		(7U << (1U * 3U)) |
		(7U << (2U * 3U))
	);
	ADC1->SMPR2 |= (
		(4U << (0U * 3U)) |
		(4U << (1U * 3U)) |
		(4U << (2U * 3U))
	);

	/* 10) Longitud de secuencia regular = 3 conversiones
		   L = N-1 = 2 */
	ADC1->SQR1 &= ~ADC_SQR1_L;
	ADC1->SQR1 |=  (2U << 20);

	/* Limpiar SQR2 por claridad */
	ADC1->SQR2 = 0;

	/* 11) Orden:
		   SQ1 = canal 0
		   SQ2 = canal 1
		   SQ3 = canal 2 */
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= (0U << 0);    /* SQ1 = IN0 */
	ADC1->SQR3 |= (1U << 5);    /* SQ2 = IN1 */
	ADC1->SQR3 |= (2U << 10);   /* SQ3 = IN2 */

	/* 12) Encender ADC */
	ADC1->CR2 |= ADC_CR2_ADON;

	/* Pequeño retardo de estabilización */
	for (volatile uint32_t i = 0; i < 1000U; i++)
	{
		__NOP();
	}
}

void ADC1_Read_3Channels(uint16_t *buffer)
{
    /* Limpiar banderas previas */
    ADC1->SR = 0;

    /* Iniciar secuencia regular por software */
    ADC1->CR2 |= ADC_CR2_SWSTART;

    /* Leer 3 conversiones en orden */
    for (uint8_t i = 0; i < 3; i++)
    {
        while ((ADC1->SR & ADC_SR_EOC) == 0U)
        {
            /* esperar */
        }

        buffer[i] = (uint16_t)ADC1->DR;
    }
}
