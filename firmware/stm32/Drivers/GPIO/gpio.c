#include "gpio.h"

static void GPIO_EnableClock(GPIO_TypeDef *port)
{
    if (port == GPIOA) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    else if (port == GPIOB) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    else if (port == GPIOC) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    else if (port == GPIOD) RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    else if (port == GPIOE) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    else if (port == GPIOH) RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    (void)RCC->AHB1ENR;
}

void GPIO_InitPin(GPIO_TypeDef *port, uint8_t pin, GPIO_Mode_t mode,
                  GPIO_Pull_t pull, GPIO_OutputType_t output_type,
                  GPIO_Speed_t speed)
{
    uint32_t shift;
    if (port == 0 || pin > 15U) return;
    GPIO_EnableClock(port);
    shift = (uint32_t)pin * 2U;
    port->MODER = (port->MODER & ~(3UL << shift)) | (((uint32_t)mode & 3UL) << shift);
    port->PUPDR = (port->PUPDR & ~(3UL << shift)) | (((uint32_t)pull & 3UL) << shift);
    if (mode == GPIO_MODE_OUTPUT) {
        if (output_type == GPIO_OPEN_DRAIN) port->OTYPER |= (1UL << pin);
        else port->OTYPER &= ~(1UL << pin);
        port->OSPEEDR = (port->OSPEEDR & ~(3UL << shift)) | (((uint32_t)speed & 3UL) << shift);
    }
}

void GPIO_WritePin(GPIO_TypeDef *port, uint8_t pin, uint8_t state)
{
    if (port == 0 || pin > 15U) return;
    port->BSRR = (state != 0U) ? (1UL << pin) : (1UL << (pin + 16U));
}

void GPIO_TogglePin(GPIO_TypeDef *port, uint8_t pin)
{
    if (port == 0 || pin > 15U) return;
    port->ODR ^= (1UL << pin);
}

uint8_t GPIO_ReadPin(GPIO_TypeDef *port, uint8_t pin)
{
    if (port == 0 || pin > 15U) return 0U;
    return (uint8_t)((port->IDR >> pin) & 1UL);
}
