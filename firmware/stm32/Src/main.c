
#include "main.h"
#include "config.h"

/* RCC peripheral base address. */
#define RCC_BASE            0x40023800UL

/* RCC AHB1 peripheral clock enable register. */
#define RCC_AHB1ENR         (*(volatile uint32_t *)(RCC_BASE + 0x30UL))

/* GPIOA peripheral base address. */
#define GPIOA_BASE          0x40020000UL

/* GPIOA mode register: selects input, output, alternate, or analog mode. */
#define GPIOA_MODER         (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))

/* GPIOA output data register: controls the output pin state. */
#define GPIOA_ODR           (*(volatile uint32_t *)(GPIOA_BASE + 0x14UL))

/* Bit 0 enables the GPIOA peripheral clock. */
#define GPIOA_CLOCK_ENABLE  (1UL << 0)

/* The on-board LD2 LED is connected to PA5 on the NUCLEO-F401RE. */
#define LED_PIN             5UL

/* Create a mask containing only the LED pin bit. */
#define LED_PIN_MASK        (1UL << LED_PIN)



/*
 * Perform basic system initialization.
 * The initial firmware keeps the default MCU clock configuration.
 * Clock configuration will be implemented and verified later.
 */
void SystemInit(void)
{
    /* Intentionally empty for the initial LED smoke test. */
}


/*
 * Configure PA5 as a general-purpose output.
 */
static void led_init(void)
{
    /* Enable the GPIOA peripheral clock. */
    RCC_AHB1ENR |= GPIOA_CLOCK_ENABLE;

    /*
     * Read back the register to ensure the clock-enable write
     * has completed before accessing GPIOA.
     */
    (void)RCC_AHB1ENR;

    /*
     * Each GPIO pin uses two MODER bits.
     * Clear both bits for PA5 before selecting output mode.
     */
    GPIOA_MODER &= ~(3UL << (LED_PIN * 2UL));

    /*
     * Set PA5 MODER bits to 01, which selects output mode.
     */
    GPIOA_MODER |= (1UL << (LED_PIN * 2UL));

    /* Start with the LED output low. */
    GPIOA_ODR &= ~LED_PIN_MASK;
}


/*
 * Provide a simple software delay for the initial smoke test.
 * The duration depends on compiler optimization and CPU clock.
 */
static void delay(volatile uint32_t count)
{
    while (count > 0UL)
    {
        count--;
    }
}


/*
 * Application entry point.
 */
int main(void)
{
    /* Configure the on-board LED pin. */
    led_init();

    /* Keep running forever because this is a bare-metal application. */
    while (1)
    {
        /*
         * Toggle PA5:
         * if it is high, make it low; if it is low, make it high.
         */
        GPIOA_ODR ^= LED_PIN_MASK;

        /* Wait before toggling the LED again. */
        delay(1000000UL);
    }
}
