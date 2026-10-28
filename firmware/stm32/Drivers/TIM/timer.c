#include "timer.h"

void Timer2_Init1MHz(void)
{
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->CR1 = 0U;
    TIM2->PSC = 84U - 1U;       /* 84 MHz / 84 = 1 MHz, 1 tick = 1 us */
    TIM2->ARR = 0xFFFFFFFFUL;   /* TIM2 is a 32-bit timer */
    TIM2->CNT = 0U;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR = 0U;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void Timer2_DelayUs(uint32_t microseconds)
{
    while (microseconds != 0U) {
        uint32_t chunk = (microseconds > 4000000000UL) ? 4000000000UL : microseconds;
        uint32_t start = TIM2->CNT;
        while ((uint32_t)(TIM2->CNT - start) < chunk) {
            /* wait */
        }
        microseconds -= chunk;
    }
}

void Timer2_DelayMs(uint32_t milliseconds)
{
    while (milliseconds != 0U) {
        Timer2_DelayUs(1000U);
        --milliseconds;
    }
}
