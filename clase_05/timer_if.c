#include "timer_if.h"
#include "timer_driver.h"

const tim4_f_t tim4_STM32 ={
    .call_back_01 = register_timer4_callback1,
    .init = timer4_init
};
