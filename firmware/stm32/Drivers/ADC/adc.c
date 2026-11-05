#include "adc.h"
#define ADC_TIMEOUT 1000000UL
void ADC1_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    ADC->CCR = (ADC->CCR & ~(3UL<<16U)) | (1UL<<16U); /* PCLK2 / 4 */
    ADC1->CR1=0U; ADC1->CR2=0U;
    /* 84-cycle sample time for channels 0..9; 144 cycles for 10..15. */
    ADC1->SMPR2=0x24924924UL;
    ADC1->SMPR1=0x002DB6DBUL;
    ADC1->CR2 |= ADC_CR2_ADON;
}
uint16_t ADC1_ReadChannel(uint8_t ch)
{
    uint32_t t;
    GPIO_TypeDef *port;
    uint8_t pin;
    if(ch>15U) return 0U;
    if(ch<=7U){port=GPIOA;pin=ch;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;}
    else if(ch<=9U){port=GPIOB;pin=(uint8_t)(ch-8U);RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;}
    else {port=GPIOC;pin=(uint8_t)(ch-10U);RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;}
    port->MODER |= 3UL<<((uint32_t)pin*2U);
    port->PUPDR &= ~(3UL<<((uint32_t)pin*2U));
    ADC1->SQR1=0U; ADC1->SQR2=0U; ADC1->SQR3=(uint32_t)ch;
    ADC1->SR=0U; ADC1->CR2 |= ADC_CR2_SWSTART;
    t=ADC_TIMEOUT;
    while((ADC1->SR & ADC_SR_EOC)==0U) if(--t==0U) return 0U;
    return (uint16_t)(ADC1->DR & 0x0FFFU);
}
