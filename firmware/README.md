# Firmware Subsystem

## 1. Purpose

This directory contains the embedded software responsible for low-level robot control, peripheral interfacing, communication, and safety-related functions.

The firmware is planned for the STM32F401RCT6 microcontroller.

## 2. Responsibilities

* Initialize and configure the microcontroller.
* Interface with sensors and actuators.
* Control motors using feedback from wheel encoders.
* Exchange commands and telemetry with the high-level computer.
* Run the custom lightweight RTOS.
* Monitor defined faults and communication timeouts.
* Implement and test low-level safety behavior.

## 3. Planned Structure

* `bootloader/`: Optional bootloader and firmware-update support.
* `stm32/`: STM32 application and hardware-dependent modules.

## 4. Inputs

* Validated motion commands from the high-level computer.
* Encoder feedback and sensor measurements.
* Battery and fault-monitoring signals.
* Configuration parameters.
* RTOS scheduling and timing services.

## 5. Outputs

* Motor-driver control signals.
* Sensor measurements and system status.
* CAN messages containing telemetry and fault information.
* Fault responses and safe-state transitions.
* Diagnostic information for debugging.

## 6. Design Principles

* Separate hardware drivers from application logic.
* Validate incoming commands before execution.
* Avoid blocking operations in time-critical tasks.
* Use bounded buffers and explicit timeout handling.
* Protect shared resources against concurrent access.
* Keep interrupt service routines short and predictable.
* Document timing requirements for real-time tasks.

## 7. Testing

Test drivers individually before integrating them with the RTOS and application. Use a bench setup before testing physical robot movement.

## 8. Current Status

The directory defines the planned firmware responsibilities. Actual implementation and supported peripherals must be documented as they become available.
