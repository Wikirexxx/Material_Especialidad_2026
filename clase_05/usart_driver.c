#define STM32F405xx
#include "stm32f4xx.h"

void usart_init(void)
{
    RCC->AHB1ENR |= 0x00000002;
    RCC->APB1ENR |= 0x00040000;

    // Configuración PB10 y PB11
    GPIOB->MODER &= ~0x00F00000;
    GPIOB->MODER |= 0x00A00000;     // A = 1010

    GPIOB->AFR[1] &= ~0x0000FF00;
    GPIOB->AFR[1] |= 0x00007700;

    GPIOB->OTYPER &= ~0x00000C00;

    GPIOB->OSPEEDR |= 0x00F00000;

    GPIOB->PUPDR &= ~0x00F00000; 
    GPIOB->PUPDR |= 0x00400000;

    USART3->CR1 = 0;
    USART3->CR2 = 0;
    USART3->CR3 = 0;

    USART3->BRR = (42000000 + (115200 /2)) / 115200;   //f + (budios / 2) / baudios
    USART3->CR1 |= 0x0000000C;
    USART3->CR1 |= 0x00002000;
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