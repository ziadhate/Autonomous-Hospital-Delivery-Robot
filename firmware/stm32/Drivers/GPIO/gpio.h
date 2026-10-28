#ifndef GPIO_H
#define GPIO_H

#include "stm32f4xx.h"
#include <stdint.h>

typedef enum {
    GPIO_MODE_INPUT = 0U,
    GPIO_MODE_OUTPUT = 1U,
    GPIO_MODE_AF = 2U,
    GPIO_MODE_ANALOG = 3U
} GPIO_Mode_t;

typedef enum {
    GPIO_NO_PULL = 0U,
    GPIO_PULL_UP = 1U,
    GPIO_PULL_DOWN = 2U
} GPIO_Pull_t;

typedef enum {
    GPIO_PUSH_PULL = 0U,
    GPIO_OPEN_DRAIN = 1U
} GPIO_OutputType_t;

typedef enum {
    GPIO_SPEED_LOW = 0U,
    GPIO_SPEED_MEDIUM = 1U,
    GPIO_SPEED_HIGH = 2U,
    GPIO_SPEED_VERY_HIGH = 3U
} GPIO_Speed_t;

void GPIO_InitPin(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode,
                  GPIO_Pull_t pull, GPIO_OutputType_t output_type,
                  GPIO_Speed_t speed);
void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t state);
void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin);
uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin);

#endif
