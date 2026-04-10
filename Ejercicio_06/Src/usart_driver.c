#define STM32F405xx
#include "stm32f4xx.h"

void usart_init(void)
{
	RCC->AHB1ENR |= 0x00000002;     // GPIOBEN
	RCC->APB1ENR |= 0x00040000;     // USART3EN

	// PB10 = TX, PB11 = RX
	GPIOB->MODER &= ~0x00F00000;
	GPIOB->MODER |=  0x00A00000;    // AF mode en PB10 y PB11

	GPIOB->AFR[1] &= ~0x0000FF00;
	GPIOB->AFR[1] |=  0x00007700;   // AF7 = USART3

	GPIOB->OTYPER &= ~0x00000C00;   // push-pull
	GPIOB->OSPEEDR |= 0x00F00000;   // alta velocidad

	GPIOB->PUPDR &= ~0x00F00000;
	GPIOB->PUPDR |=  0x00400000;    // pull-up en PB11(RX)

	USART3->CR1 = 0x00000000;
	USART3->CR2 = 0x00000000;
	USART3->CR3 = 0x00000000;

	USART3->BRR = (42000000 + (115200 / 2)) / 115200;

	USART3->CR1 |= 0x0000000C;      // TE + RE
	USART3->CR1 |= 0x00000020;      // RXNEIE = interrupción al recibir dato
	USART3->CR1 |= 0x00002000;      // UE = USART enable

	NVIC_EnableIRQ(USART3_IRQn);    // habilitar USART3 en NVIC
}
void write_byte(uint8_t d)
{
    USART3->DR = d;
    while(!(USART3->SR & 0x00000040)){}
}
uint8_t read_byte(void)
{
    uint8_t d = 0;
    while(!(USART3->SR & 0x00000020)){}
    d = USART3->DR;
    return d;
}
