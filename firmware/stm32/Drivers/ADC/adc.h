#ifndef ADC_H
#define ADC_H
#include "stm32f4xx.h"
#include <stdint.h>
/* ADC1 single 12-bit conversion. Channel 0 = PA0. */
void ADC1_Init(void);
uint16_t ADC1_ReadChannel(uint8_t channel);
#endif
