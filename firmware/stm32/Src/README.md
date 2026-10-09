# STM32 Source Files

## Purpose

This directory contains the implementation of the STM32 firmware modules.

## Responsibilities

* Implement functions declared in public headers.
* Initialize and coordinate the required modules.
* Implement application state transitions.
* Handle errors and report status to dependent modules.
* Integrate RTOS tasks with peripheral drivers and communication.

## Implementation Guidelines

* Keep each source file focused on a clear responsibility.
* Validate function arguments and external data.
* Avoid long blocking operations in periodic tasks.
* Use documented synchronization mechanisms for shared resources.
* Keep interrupt service routines short.
* Do not access hardware registers through undocumented assumptions.
* Provide clear error handling and diagnostic information.

## Inputs

Public headers, configuration values, hardware interfaces, and module requirements.

## Outputs

Compiled firmware modules and executable behavior on the target MCU.

## Validation

Compile with the project's configured toolchain, enable relevant warnings, and run unit or hardware tests for the implemented functionality.
