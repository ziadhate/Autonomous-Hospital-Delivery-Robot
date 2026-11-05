#ifndef I2C_H
#define I2C_H
#include "stm32f4xx.h"
#include <stdint.h>
/* I2C1: PB8=SCL, PB9=SDA, AF4, 100 kHz. Assumes PCLK1=42 MHz.
   External pull-ups to 3.3 V are required. */
void I2C1_Init100kHz(void);
uint8_t I2C1_WriteRegister(uint8_t address_7bit, uint8_t reg, uint8_t value);
uint8_t I2C1_ReadRegister(uint8_t address_7bit, uint8_t reg, uint8_t *value);
#endif
