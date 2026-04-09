#include "system_clock_if.h"
#include "system_clock_driver.h"

/* ===== ESTA ES LA "INSTANCIA" QUE SE INYECTA ===== */
const system_clock_if_t SYSCLK_STM32 = {
    .init       = SystemClock_Config,
    .en_fpu     = FPU_Enable,
    .clear_flags = clear_fault_flags
};