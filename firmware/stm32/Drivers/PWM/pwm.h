#ifndef PWM_H
#define PWM_H

#include "stm32f4xx.h"
#include <stdint.h>

/*
 * PWM output on PA5 using TIM2_CH1 (AF1) is NOT available on STM32F401RE.
 * This driver uses PA0 = TIM2_CH1, AF1.
 * Assumes TIM2 input clock is 84 MHz and prescaler division is configured
 * here to make the timer counter tick at 1 MHz.
 */
void PWM_TIM2_CH1_PA0_Init(uint32_t frequency_hz);
void PWM_TIM2_CH1_SetDuty(uint8_t duty_percent);

#endif
