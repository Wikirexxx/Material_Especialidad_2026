#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H
#include <stdint.h>

typedef void(*timer4_callback)(void); 

void timer4_init(void);
void register_timer4_callback1(timer4_callback c);

#endif