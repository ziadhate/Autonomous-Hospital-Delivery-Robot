#include "i2c.h"
#define I2C_TIMEOUT 1000000UL
static uint8_t wait_sr1(uint16_t flag)
{
    uint32_t t=I2C_TIMEOUT;
    while ((I2C1->SR1 & flag)==0U) if (--t==0U) return 0U;
    return 1U;
}
static void stop_bus(void) { I2C1->CR1 |= I2C_CR1_STOP; }
static uint8_t start_address(uint8_t addr, uint8_t read)
{
    uint32_t t=I2C_TIMEOUT;
    I2C1->CR1 |= I2C_CR1_START;
    while ((I2C1->SR1 & I2C_SR1_SB)==0U) if (--t==0U) return 0U;
    I2C1->DR=(uint8_t)((addr<<1U)|(read?1U:0U));
    if (!wait_sr1(I2C_SR1_ADDR)) return 0U;
    (void)I2C1->SR1; (void)I2C1->SR2;
    return 1U;
}
void I2C1_Init100kHz(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    GPIOB->MODER=(GPIOB->MODER & ~((3UL<<16)|(3UL<<18)))|(2UL<<16)|(2UL<<18);
    GPIOB->OTYPER |= (1UL<<8)|(1UL<<9);
    GPIOB->OSPEEDR |= (3UL<<16)|(3UL<<18);
    GPIOB->PUPDR=(GPIOB->PUPDR & ~((3UL<<16)|(3UL<<18)))|(1UL<<16)|(1UL<<18);
    GPIOB->AFR[1]=(GPIOB->AFR[1] & ~((15UL<<0)|(15UL<<4)))|(4UL<<0)|(4UL<<4);
    I2C1->CR1=I2C_CR1_SWRST; I2C1->CR1=0U;
    I2C1->CR2=42U; I2C1->CCR=210U; I2C1->TRISE=43U;
    I2C1->CR1=I2C_CR1_PE;
}
uint8_t I2C1_WriteRegister(uint8_t addr,uint8_t reg,uint8_t val)
{
    if(addr>0x7FU) return 0U;
    if(!start_address(addr,0U)){stop_bus();return 0U;}
    I2C1->DR=reg;
    if(!wait_sr1(I2C_SR1_TXE)){stop_bus();return 0U;}
    I2C1->DR=val;
    if(!wait_sr1(I2C_SR1_BTF)){stop_bus();return 0U;}
    stop_bus(); return 1U;
}
uint8_t I2C1_ReadRegister(uint8_t addr,uint8_t reg,uint8_t *value)
{
    if(addr>0x7FU || value==0) return 0U;
    if(!start_address(addr,0U)){stop_bus();return 0U;}
    I2C1->DR=reg;
    if(!wait_sr1(I2C_SR1_BTF)){stop_bus();return 0U;}
    I2C1->CR1 |= I2C_CR1_START;
    if(!wait_sr1(I2C_SR1_SB)){stop_bus();return 0U;}
    I2C1->CR1 &= ~I2C_CR1_ACK;
    I2C1->DR=(uint8_t)((addr<<1U)|1U);
    if(!wait_sr1(I2C_SR1_ADDR)){stop_bus();I2C1->CR1|=I2C_CR1_ACK;return 0U;}
    (void)I2C1->SR1; (void)I2C1->SR2;
    stop_bus();
    if(!wait_sr1(I2C_SR1_RXNE)){I2C1->CR1|=I2C_CR1_ACK;return 0U;}
    *value=(uint8_t)I2C1->DR;
    I2C1->CR1 |= I2C_CR1_ACK;
    return 1U;
}
