#ifndef USART_IF_H
#define USART_IF_H
#include <stdint.h>

typedef struct 
{
    void(*init)(void);
    void(*w_byte)(uint8_t dato);
    uint8_t(*r_byte)(void);
}usart3_f_t;

extern const usart3_f_t usart3_STM32;

#endif