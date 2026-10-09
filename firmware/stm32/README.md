# STM32 Firmware

## 1. Purpose

This directory contains the application firmware for the STM32 low-level controller.

The STM32 is intended to handle motor control, sensor interfacing, communication, and defined safety-related functions independently of the high-level Linux computer.

## 2. Planned Modules

* `Inc/`: Public headers and shared declarations.
* `Src/`: Application and module implementation.
* `Drivers/`: Peripheral and external-device drivers.
* `RTOS/`: Custom lightweight RTOS.
* `CAN/`: CAN message handling and communication.
* `Motor_Control/`: Motor commands, encoder feedback, and PID control.
* `Safety/`: Fault monitoring and safe-state behavior.
* `Sensors/`: Sensor interfaces and measurement processing.

## 3. Inputs

* Motion commands received over CAN.
* Encoder and sensor data.
* Configuration parameters.
* Timer and interrupt events.

## 4. Outputs

* Motor PWM and direction signals.
* Encoder measurements and controller feedback.
* CAN telemetry and fault reports.
* RTOS task execution and synchronization.
* Defined safe responses to faults.

## 5. Startup Sequence

The intended startup sequence is:

1. Reset and MCU initialization.
2. Clock and required peripheral initialization.
3. GPIO and communication initialization.
4. RTOS initialization, if enabled.
5. Creation of required tasks and synchronization objects.
6. Validation of critical hardware and communication states.
7. Transition to the operational state when startup conditions are satisfied.

The exact sequence must follow the implemented startup code and hardware configuration.

## 6. Coding Rules

* Use consistent naming conventions.
* Keep public declarations in appropriate headers.
* Avoid duplicated peripheral ownership.
* Document interrupt and task-context restrictions.
* Check return values from critical operations.
* Avoid dynamic memory allocation in time-critical paths unless explicitly justified.
* Keep hardware-dependent assumptions documented.

## 7. Validation

Verify startup, task scheduling, motor-control behavior, CAN communication, fault handling, and recovery procedures independently before full integration.
