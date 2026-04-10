#ifndef SYSTEM_CLOCK_DRIVER_H
#define SYSTEM_CLOCK_DRIVER_H
#include <stdint.h>

void SystemClock_Config(void);
void FPU_Enable(void);
void clear_fault_flags(void);

#endif