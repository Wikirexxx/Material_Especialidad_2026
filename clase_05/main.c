// ============================ INCLUDES C ============================
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
// ============================ INCLUDES PROPIOS ============================
#include "system_clock_if.h"
#include "usart_if.h"
#include "timer_if.h"

#define PI 3.14159265358979f
float sen_signal = 0;
float s2 = 0;
uint32_t i = 0;

typedef union
{
    float f;
    uint8_t bytes_t[4];
}desc_data_t;


void config_uc(void);
void calc_seno(float amplitud, float freq_s , float fs, float n,float *out_data);
void envio_funciones(void);

int main(void)
{
    config_uc();
    while (1)
    {
    }
}
void config_uc(void)
{
    SYSCLK_STM32.clear_flags();
    SYSCLK_STM32.en_fpu();
    SYSCLK_STM32.init();
    usart3_STM32.init();//Inicialización de USART3 (PB10 Rx - PB11 Tx)
    tim4_STM32.init();
    tim4_STM32.call_back_01(envio_funciones);
}
void calc_seno(float amplitud, float freq_s , float fs, float n,float *out_data)
{
    float t = 0;
    t = (float)n / fs;
    *out_data = amplitud * sinf(2.0f * PI * freq_s * t );
}
void envio_funciones(void)
{
    static uint8_t n = 0;
    static uint8_t m = 25;
    desc_data_t desc_bytes_t;
    calc_seno(10.0f,100.0f, 10000.0f, n, &sen_signal);
    calc_seno(5.0f,100.0f, 10000.0f, m, &s2);

    desc_bytes_t.f = sen_signal;
    usart3_STM32.w_byte('i');
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[3]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[2]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[1]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[0]);
    desc_bytes_t.f = s2;
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[3]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[2]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[1]);
    usart3_STM32.w_byte(desc_bytes_t.bytes_t[0]);
    n++;
    m++;
    if (n >= 100)
    {
        n = 0;
    }
    if (m >= 100)
    {
        m = 0;
    }
}