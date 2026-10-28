#ifndef TIMER_H
#define TIMER_H

#include "stm32f4xx.h"
#include <stdint.h>

/*
 * Basic TIM2 time base and blocking delay helpers.
 * Assumes TIM2 input clock is 84 MHz (common STM32F401RE clock setup).
 * Call Timer2_Init1MHz() after system clock configuration.
 */
void Timer2_Init1MHz(void);
void Timer2_DelayUs(uint32_t microseconds);
void Timer2_DelayMs(uint32_t milliseconds);

#endif
