# Firmware

## Overview

This directory contains the low-level firmware responsible for real-time control, hardware interaction, and safety-critical operations.

The firmware runs on the STM32 microcontroller and communicates with the high-level robot software through defined interfaces such as CAN.

## Responsibilities

* Initialize and configure the microcontroller.
* Integrate the custom RTOS.
* Control motors and read encoder feedback.
* Interface with sensors and electronic modules.
* Implement communication protocols.
* Monitor faults and safety conditions.
* Provide a stable interface to the ROS 2 computer.

## Directory Structure

* `bootloader/`: Optional firmware update and boot management.
* `stm32/`: STM32 application, drivers, RTOS, communication, and control modules.

## Execution Model

The firmware is responsible for predictable, time-sensitive tasks. ROS 2 handles high-level navigation and mission planning, while the STM32 handles low-level execution and local safety responses.

## Development Rules

* Keep hardware-dependent code separate from application logic.
* Use clear interfaces between modules.
* Avoid blocking operations in time-critical tasks.
* Document interrupt and shared-data behavior.
* Check return values and handle hardware failures.
* Never assume a command from the onboard computer is always valid.

## Testing

Use host-side unit tests where possible, cross-compilation, static analysis, and hardware tests on the STM32.

## Definition of Done

Firmware changes must compile for the selected target, pass applicable tests, document their interfaces, and preserve safe behavior when communication or hardware fails.
