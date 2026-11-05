#include "spi.h"

#define SPI_TIMEOUT 1000000UL

static uint8_t wait_sr(uint16_t flag)
{
    uint32_t t = SPI_TIMEOUT;
    while ((SPI1->SR & flag) == 0U) if (--t == 0U) return 0U;
    return 1U;
}

static inline void cs_select(void)   { GPIOA->BSRR = (1UL << 20); } // PA4 Low
static inline void cs_deselect(void) { GPIOA->BSRR = (1UL << 4);  } // PA4 High

void SPI1_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // PA5 (SCK), PA6 (MISO), PA7 (MOSI) -> Alternate Function (AF5)
    GPIOA->MODER = (GPIOA->MODER & ~((3UL << 10) | (3UL << 12) | (3UL << 14))) |
                   (2UL << 10) | (2UL << 12) | (2UL << 14);
    GPIOA->OSPEEDR |= (3UL << 10) | (3UL << 12) | (3UL << 14);
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~((15UL << 20) | (15UL << 24) | (15UL << 28))) |
                    (5UL << 20) | (5UL << 24) | (5UL << 28);

    // PA4 (CS) -> Output General Purpose, Push-Pull, High
    GPIOA->MODER = (GPIOA->MODER & ~(3UL << 8)) | (1UL << 8);
    cs_deselect();

    // SPI Configuration: Master Mode, Baud rate f_PCLK/16, Software slave management (SSM/SSI)
    SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | (3UL << 3);
    SPI1->CR1 |= SPI_CR1_SPE;
}

uint8_t SPI1_Transmit(uint8_t *data, uint16_t size)
{
    if (data == 0 || size == 0) return 0U;
    cs_select();
    for (uint16_t i = 0; i < size; i++) {
        if (!wait_sr(SPI_SR_TXE)) { cs_deselect(); return 0U; }
        SPI1->DR = data[i];
        if (!wait_sr(SPI_SR_RXNE)) { cs_deselect(); return 0U; }
        (void)SPI1->DR; // Clear RXNE flag by reading DR
    }
    while (SPI1->SR & SPI_SR_BSY);
    cs_deselect();
    return 1U;
}

uint8_t SPI1_Receive(uint8_t *data, uint16_t size)
{
    if (data == 0 || size == 0) return 0U;
    cs_select();
    for (uint16_t i = 0; i < size; i++) {
        if (!wait_sr(SPI_SR_TXE)) { cs_deselect(); return 0U; }
        SPI1->DR = 0xFFU; // Dummy byte to generate clock
        if (!wait_sr(SPI_SR_RXNE)) { cs_deselect(); return 0U; }
        data[i] = (uint8_t)SPI1->DR;
    }
    while (SPI1->SR & SPI_SR_BSY);
    cs_deselect();
    return 1U;
}

uint8_t SPI1_TransmitReceive(uint8_t *tx_data, uint8_t *rx_data, uint16_t size)
{
    if (tx_data == 0 || rx_data == 0 || size == 0) return 0U;
    cs_select();
    for (uint16_t i = 0; i < size; i++) {
        if (!wait_sr(SPI_SR_TXE)) { cs_deselect(); return 0U; }
        SPI1->DR = tx_data[i];
        if (!wait_sr(SPI_SR_RXNE)) { cs_deselect(); return 0U; }
        rx_data[i] = (uint8_t)SPI1->DR;
    }
    while (SPI1->SR & SPI_SR_BSY);
    cs_deselect();
    return 1U;
}
