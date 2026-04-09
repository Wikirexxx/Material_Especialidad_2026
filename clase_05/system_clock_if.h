#ifndef SYSTEM_CLOCK_IF_H
#define SYSTEM_CLOCK_IF_H

#include <stdint.h>

/* callback tipo void(void) */
typedef void (*clk_void_fn_t)(void);

typedef struct {
    clk_void_fn_t   init;        // configura reloj del sistema
    clk_void_fn_t   clear_flags;
    clk_void_fn_t   en_fpu;
} system_clock_if_t;

/* ===== ESTA ES LA "INSTANCIA" QUE SE INYECTA ===== */
extern const system_clock_if_t SYSCLK_STM32;

#endif // SYSTEM_CLOCK_IF_H