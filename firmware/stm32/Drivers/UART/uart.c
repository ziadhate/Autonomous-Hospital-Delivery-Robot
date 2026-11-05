#include "uart.h"
void UART2_Init(uint32_t baud_rate)
{
    if (baud_rate == 0U) return;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    /* PA2/PA3 alternate function AF7 */
    GPIOA->MODER = (GPIOA->MODER & ~((3UL<<4)|(3UL<<6))) | (2UL<<4) | (2UL<<6);
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~((15UL<<8)|(15UL<<12))) | (7UL<<8) | (7UL<<12);
    GPIOA->OTYPER &= ~((1UL<<2)|(1UL<<3));
    GPIOA->PUPDR = (GPIOA->PUPDR & ~((3UL<<4)|(3UL<<6))) | (1UL<<4) | (1UL<<6);
    USART2->CR1 = 0U; USART2->CR2 = 0U; USART2->CR3 = 0U;
    USART2->BRR = (42000000UL + baud_rate/2U) / baud_rate;
    USART2->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}
void UART2_WriteByte(uint8_t data)
{
    while ((USART2->SR & USART_SR_TXE) == 0U) {}
    USART2->DR = data;
}
uint8_t UART2_ReadByte(void)
{
    while ((USART2->SR & USART_SR_RXNE) == 0U) {}
    return (uint8_t)USART2->DR;
}
void UART2_WriteString(const char *s)
{
    if (s == 0) return;
    while (*s) UART2_WriteByte((uint8_t)*s++);
}
uint8_t UART2_BytesAvailable(void)
{
    return (USART2->SR & USART_SR_RXNE) ? 1U : 0U;
}
