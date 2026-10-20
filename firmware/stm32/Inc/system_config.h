
#ifndef SYSTEM_CONFIG_H
#define SYSTEM_CONFIG_H

#include <stdint.h>

/*
 * Initial assumed system clock in Hz.
 * The current smoke test uses the default internal clock.
 * Update this value when a real clock configuration is implemented.
 */
#define SYSTEM_CPU_HZ 16000000UL

/*
 * Intended operating frequency for a future system tick.
 * This does not configure SysTick by itself.
 */
#define SYSTEM_TICK_HZ 1000UL

/*
 * Feature switches for the initial bare-metal firmware.
 * These macros are configuration flags only.
 */
#define SYSTEM_ENABLE_RTOS       0
#define SYSTEM_ENABLE_CAN        0
#define SYSTEM_ENABLE_WATCHDOG   0

#endif /* SYSTEM_CONFIG_H */
