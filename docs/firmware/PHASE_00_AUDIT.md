
# Phase 00 - Firmware Audit

## 1. Project Target

- Board: NUCLEO-F401RE
- Microcontroller: STM32F401RE
- CPU architecture: ARM Cortex-M4F
- Firmware language: C
- Initial execution model: Bare-metal
- Initial test: On-board LED blinking

## 2. Development Tools

- Cross-compiler: arm-none-eabi-gcc
- Build system: CMake
- Build generator: Ninja
- Build automation: GNU Make
- Debugging and flashing tools: To be verified separately

## 3. Initial Firmware Scope

The first firmware build contains only:

- A custom startup file
- A linker script
- A minimal main application
- Basic system configuration headers
- CMake build configuration

Motor drivers, sensor drivers, CAN communication, and RTOS
must not be considered operational until they are implemented,
compiled, and tested.

## 4. Architecture Plan

- Application: Src/main.c
- Public headers: Inc/
- Peripheral drivers: Drivers/
- Motor control: Motor_Control/
- Safety modules: Safety/
- CAN protocol and messages: CAN/
- RTOS implementation: RTOS/
- Startup code: startup/
- Memory layout: linker/
- Build configuration: CMakeLists.txt and cmake/

## 5. Known Issues and Risks

- Existing source files may contain empty or incomplete implementations.
- Duplicate modules may exist between Src/, Motor_Control/, and Safety/.
- The file NUCLEO-F030R8.PDF refers to a different board than the target.
- The startup vector table must be checked against the STM32F401xE
  interrupt table before enabling peripheral interrupts.
- The initial LED test does not validate motor control, sensors,
  CAN communication, or RTOS functionality.

## 6. Acceptance Criteria

- CMake configuration completes successfully.
- The firmware ELF, HEX, and BIN files are generated.
- The linker reports no memory overflow.
- The ELF file targets ARM Cortex-M4.
- After flashing a compatible board, the on-board LED blinks.
- The actual hardware test result is recorded separately.

## 7. Status

Status: Pending build and hardware validation.
