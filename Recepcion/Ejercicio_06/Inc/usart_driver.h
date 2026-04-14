#ifndef USART_DRIVER_H
#define USART_DRIVER_H
#include <stdint.h>

void usart_init(void);
void write_byte(uint8_t d);
uint8_t read_byte(void);

#endif