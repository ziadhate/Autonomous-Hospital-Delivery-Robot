#ifndef UART_H
#define UART_H
#include "stm32f4xx.h"
#include <stdint.h>
/* USART2: PA2=TX, PA3=RX, AF7. Assumes PCLK1 = 42 MHz. */
void UART2_Init(uint32_t baud_rate);
void UART2_WriteByte(uint8_t data);
uint8_t UART2_ReadByte(void);
void UART2_WriteString(const char *text);
uint8_t UART2_BytesAvailable(void);
#endif
