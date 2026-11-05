#ifndef SPI_H
#ifndef SPI_H
#define SPI_H

#include "stm32f4xx.h"
#include <stdint.h>

void SPI1_Init(void);
uint8_t SPI1_Transmit(uint8_t *data, uint16_t size);
uint8_t SPI1_Receive(uint8_t *data, uint16_t size);
uint8_t SPI1_TransmitReceive(uint8_t *tx_data, uint8_t *rx_data, uint16_t size);

#endif /* SPI_H */
