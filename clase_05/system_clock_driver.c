#define STM32F405xx
#include "stm32f4xx.h"
#include "system_clock_driver.h"

void SystemClock_Config(void)
{
    // 1. Activar HSE (High Speed External clock)
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));  // Esperar a que esté listo

    // 2. Configurar FLASH: prefetch + cache + 5 WS (para 168 MHz)
    FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

    // 3. Configurar PLL:
    //    VCO input = HSE / M = 8 / 8 = 1 MHz
    //    VCO output = VCO input * N = 1 * 336 = 336 MHz
    //    PLLCLK = VCO output / P = 336 / 2 = 168 MHz
    //    USB OTG FS clock = 336 / Q = 7 = 48 MHz
    RCC->PLLCFGR = (8 << RCC_PLLCFGR_PLLM_Pos)    // PLLM = 8
                 | (336 << RCC_PLLCFGR_PLLN_Pos)  // PLLN = 336
                 | (0 << RCC_PLLCFGR_PLLP_Pos)    // PLLP = 2
                 | (7 << RCC_PLLCFGR_PLLQ_Pos)    // PLLQ = 7
                 | RCC_PLLCFGR_PLLSRC_HSE;        // Fuente: HSE

    // 4. Activar PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));  // Esperar a que esté listo

    // 5. Configurar prescalers AHB, APB1, APB2
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;    // AHB = 168 MHz
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;   // APB1 = 42 MHz
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // APB2 = 84 MHz

    // 6. Seleccionar PLL como fuente de sistema
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL);  // Esperar cambio

    // 7. Opcional: desactivar HSI si no se necesita
    RCC->CR &= ~RCC_CR_HSION;
}
void FPU_Enable(void)
{
    SCB->CPACR |= (0xF << 20);  // Habilita CP10 y CP11 (FPU)
    __DSB();
    __ISB();
}
void clear_fault_flags(void)
{
    SCB->CFSR = 0xFFFFFFFF;   // limpia UFSR/BFSR/MMFSR
    SCB->HFSR = 0xFFFFFFFF;   // limpia hardfault status (w1c)
    SCB->DFSR = 0xFFFFFFFF;   // opcional
}