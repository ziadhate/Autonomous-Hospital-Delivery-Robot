#include "pwm.h"

void PWM_TIM2_CH1_PA0_Init(uint32_t frequency_hz)
{
    uint32_t arr;

    if (frequency_hz == 0U) return;

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    /* PA0 alternate function AF1 = TIM2_CH1 */
    GPIOA->MODER = (GPIOA->MODER & ~(3UL << (0U * 2U))) | (2UL << (0U * 2U));
    GPIOA->PUPDR &= ~(3UL << (0U * 2U));
    GPIOA->OTYPER &= ~(1UL << 0U);
    GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~(3UL << (0U * 2U))) | (2UL << (0U * 2U));
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~(0xFUL << 0U)) | (1UL << 0U);

    /* TIM2 counter tick = 1 MHz when TIM2CLK = 84 MHz */
    TIM2->CR1 = 0U;
    TIM2->PSC = 84U - 1U;
    arr = (1000000UL / frequency_hz);
    if (arr == 0U) arr = 1U;
    TIM2->ARR = arr - 1U;
    TIM2->CCR1 = 0U;

    /* PWM mode 1, enable channel 1 output, preload compare register */
    TIM2->CCMR1 = (6UL << 4U) | TIM_CCMR1_OC1PE;
    TIM2->CCER |= TIM_CCER_CC1E;
    TIM2->CR1 |= TIM_CR1_ARPE;
    TIM2->EGR = TIM_EGR_UG;
    TIM2->SR = 0U;
    TIM2->CR1 |= TIM_CR1_CEN;
}

void PWM_TIM2_CH1_SetDuty(uint8_t duty_percent)
{
    uint32_t period_counts;
    if (duty_percent > 100U) duty_percent = 100U;
    period_counts = TIM2->ARR + 1U;
    TIM2->CCR1 = (period_counts * duty_percent) / 100U;
}
