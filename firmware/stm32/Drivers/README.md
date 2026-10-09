# STM32 Drivers

## Purpose

This directory contains low-level drivers for the microcontroller peripherals and external devices used by the robot.

## Responsibilities

* Configure and access hardware peripherals.
* Provide documented APIs to higher-level firmware modules.
* Convert hardware register operations into clear driver functions.
* Report initialization failures and peripheral errors.
* Keep device-specific behavior separate from application logic.

## Driver Categories

Depending on the selected hardware, drivers may cover:

* GPIO.
* Timers and PWM.
* UART.
* SPI.
* I2C.
* CAN peripheral interface.
* ADC.
* Encoder timers.
* Watchdog.
* External sensors.

Not every category is guaranteed to be implemented.

## Driver Contract

Each driver should document:

* Initialization requirements.
* Public functions.
* Inputs and outputs.
* Valid parameter ranges.
* Return values and error codes.
* Interrupt usage.
* Task-safety and concurrency restrictions.
* Required clocks and peripheral dependencies.

## Testing

Use mocks or host-side tests when practical, then verify peripheral behavior on the actual MCU.

## Current Status

The final driver list depends on the approved STM32 pinout and selected components.

