#define STM32F405xx
#include "stm32f4xx.h"
#include "timer_driver.h"

static timer4_callback cb1 = 0;

void timer4_init(void)
{
    RCC->APB1ENR |= 0x00000004;
    (void)RCC->APB1ENR;

    TIM4->PSC = 83;             // 1 MHz
    TIM4->ARR = 9999;           
    TIM4->EGR |= 0x00000001;    
    TIM4->SR = 0;
    TIM4->DIER |= 0x00000001;
    NVIC_SetPriority(TIM4_IRQn,5);
    NVIC_EnableIRQ(TIM4_IRQn);
    TIM4->CR1 |= 0x00000001;
}
void register_timer4_callback1(timer4_callback c)
{
    cb1 = c;
}
void TIM4_IRQHandler(void)
{
    if(TIM4->SR & 0x00000001)
    {
        TIM4->SR &= ~0x00000001;
        if(cb1 != 0)
        {
            cb1();
        }
    }
}
