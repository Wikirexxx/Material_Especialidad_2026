#ifndef TIMER_IF_H
#define TIMER_IF_H
#include <stdint.h>
#include "timer_driver.h"

typedef struct 
{
    void (*init)(void);
    void (*call_back_01)(timer4_callback callback_01);
}tim4_f_t;

extern const tim4_f_t tim4_STM32;

#endif