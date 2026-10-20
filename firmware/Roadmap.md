# STM32 Firmware Development Roadmap
## Autonomous Hospital Delivery Robot

## Note:to put Checkmark put X in the bracket

## Project Overview

This document defines the complete development roadmap for the STM32 firmware of the Autonomous Hospital Delivery Robot.

The firmware is responsible for low-level hardware control, motor control, sensor acquisition, real-time task scheduling, CAN communication, system monitoring, and safety mechanisms.

Development is divided into 11 sequential phases. Each phase defines its objectives, required files, implementation tasks, testing procedures, and acceptance criteria.

---

# Phase 00 — Project Audit & Architecture

## Objective

Review the existing repository, verify the target hardware, identify missing and duplicated components, and establish the firmware architecture.

## Files Involved

- `stm32/CMakeLists.txt`
- `stm32/Makefile`
- `stm32/README.md`
- `stm32/Inc/config.h`
- `stm32/Inc/system_config.h`
- `stm32/Inc/main.h`
- `stm32/Src/main.c`
- `stm32/Drivers/`
- `stm32/RTOS/`
- `stm32/Motor_Control/`
- `stm32/Sensors/`
- `stm32/Safety/`
- `stm32/CAN/`
- `bootloader/`

## Implementation Tasks

- [x] Confirm the exact STM32 MCU and development board.
- [x] Identify the compiler and build environment.
- [x] Determine whether the project uses HAL, CMSIS, LL, or bare-metal drivers.
- [x] Locate startup code, linker scripts, and device-specific dependencies.
- [x] Review all existing source and header files.
- [x] Identify duplicated or overlapping implementations.
- [x] Define module responsibilities and interfaces.
- [x] Document hardware and software dependencies.
- [x] Establish a development and testing plan.

## Testing and Validation

- [x] Verify the repository structure.
- [x] Inspect build configuration and source dependencies.
- [x] Produce a list of missing, incomplete, and duplicated components.

## Acceptance Criteria

- [x] Target hardware is identified.
- [x] Existing architecture is documented.
- [x] Duplicate implementations have a resolution plan.
- [x] Implementation dependencies are understood.

---

# Phase 01 — Build System & Configuration

## Objective

Establish a reproducible firmware build system and verify the target MCU, compiler settings, startup code, and memory configuration.

## Files Involved

- `stm32/CMakeLists.txt`
- `stm32/Makefile`
- `stm32/Inc/config.h`
- `stm32/Inc/system_config.h`
- `stm32/Inc/main.h`
- `stm32/Src/config.c`
- `stm32/Src/system_config.c`
- `stm32/Src/main.c`
- Startup assembly file, if missing.
- Linker script, if missing.
- Required CMSIS and vendor dependencies.

## Implementation Tasks

- [x] Verify the target MCU and compiler toolchain.
- [x] Configure CPU architecture, FPU, ABI, and compiler options.
- [x] Configure include directories and source files.
- [x] Verify startup code and the interrupt vector table.
- [x] Verify the linker script and memory regions.
- [x] Configure clock and system initialization.
- [x] Centralize hardware and system configuration.
- [x] Remove duplicate source entries.
- [x] Enable useful compiler warnings.
- [x] Document clean build and flashing procedures.

## Testing and Validation

- [x] Perform a clean CMake configuration.
- [x] Build from a fresh build directory.
- [x] Resolve compilation and linker errors.
- [x] Inspect ELF sections and memory usage.
- [x] Verify the firmware output format.
- [x] Run a basic startup or heartbeat test on hardware.

## Acceptance Criteria

- [x] A clean build succeeds.
- [x] The correct target MCU is selected.
- [x] Required source files are included exactly once.
- [x] Memory addresses match the linker configuration.
- [x] Build instructions are documented.

---

# Phase 02 — Low-Level Peripheral Drivers

## Objective

Implement and validate the low-level drivers required to access STM32 peripherals.

## Files Involved

- `stm32/Drivers/GPIO/gpio.c`
- `stm32/Drivers/GPIO/gpio.h`
- `stm32/Drivers/TIM/timer.c`
- `stm32/Drivers/TIM/timer.h`
- `stm32/Drivers/PWM/pwm.c`
- `stm32/Drivers/PWM/pwm.h`
- `stm32/Drivers/UART/uart.c`
- `stm32/Drivers/UART/uart.h`
- `stm32/Drivers/ADC/adc.c`
- `stm32/Drivers/ADC/adc.h`
- `stm32/Drivers/I2C/i2c.c`
- `stm32/Drivers/I2C/i2c.h`
- `stm32/Drivers/SPI/spi.c`
- `stm32/Drivers/SPI/spi.h`

## Implementation Tasks

### GPIO

- [ ] Configure digital inputs and outputs.
- [ ] Implement required read, write, and toggle operations.
- [ ] Define pin ownership and safe output states.

### Timers and PWM

- [ ] Configure timer counters and prescalers.
- [ ] Configure interrupts where required.
- [ ] Implement PWM initialization and duty-cycle control.
- [ ] Verify frequency and duty-cycle limits.

### UART

- [ ] Configure baud rate and frame settings.
- [ ] Implement transmission and reception.
- [ ] Define timeout and error-handling behavior.

### ADC

- [ ] Configure ADC channels.
- [ ] Implement conversion and data retrieval.
- [ ] Validate measurement ranges and scaling.

### I2C and SPI

- [ ] Configure bus timing and operating modes.
- [ ] Implement transfer interfaces.
- [ ] Define timeout and error handling.
- [ ] Verify compatibility with the selected peripherals.

## Testing and Validation

- [ ] Test GPIO using known inputs and outputs.
- [ ] Measure timer and PWM behavior.
- [ ] Test UART communication.
- [ ] Validate ADC measurements.
- [ ] Test I2C and SPI with suitable devices or test fixtures.
- [ ] Verify error-handling behavior.

## Acceptance Criteria

- [ ] Each implemented driver has a documented interface.
- [ ] Drivers compile successfully.
- [ ] Available driver tests pass.
- [ ] Hardware configurations are documented.

---

# Phase 03 — Custom RTOS & Cortex-M4 Port

## Objective

Implement and validate the custom RTOS required for concurrent real-time execution.

## Files Involved

- `stm32/RTOS/kernel.h`
- `stm32/RTOS/task.h`
- `stm32/RTOS/scheduler.h`
- `stm32/RTOS/context_switch.h`
- `stm32/RTOS/critical_section.h`
- `stm32/RTOS/queue.h`
- `stm32/RTOS/semaphore.h`
- `stm32/RTOS/mutex.h`
- `stm32/RTOS/mailbox.h`
- `stm32/RTOS/notification.h`
- `stm32/RTOS/timeout.h`
- `stm32/RTOS/port/cortex_m4/port.c`
- `stm32/RTOS/port/cortex_m4/port.h`
- `stm32/RTOS/port/cortex_m4/port_asm.s`

Additional `.c` implementation files should be created only where the existing kernel architecture requires them.

## Implementation Tasks

- [ ] Verify the Cortex-M4 processor port.
- [ ] Implement and validate task stack initialization.
- [ ] Verify context save and restore.
- [ ] Implement task management and scheduling.
- [ ] Configure the system tick.
- [ ] Define idle-task behavior.
- [ ] Implement critical sections.
- [ ] Implement queues and semaphores.
- [ ] Implement mutexes and mailboxes.
- [ ] Implement notifications and timeouts.
- [ ] Define ISR-safe API rules.
- [ ] Define stack overflow detection where supported.

## Testing and Validation

- [ ] Run a single task.
- [ ] Run multiple tasks.
- [ ] Verify scheduling and context switching.
- [ ] Test synchronization under contention.
- [ ] Test timeout behavior.
- [ ] Validate stack boundaries and interrupt interactions.

## Acceptance Criteria

- [ ] Scheduler operates consistently on the target.
- [ ] Context switching passes the available tests.
- [ ] Synchronization APIs have documented behavior.
- [ ] Stack and timing limitations are recorded.

---

# Phase 04 — Motor Control, Encoders & PID

## Objective

Implement controlled motor operation using encoder feedback and PID control.

## Files Involved

- `stm32/Motor_Control/motor.c`
- `stm32/Motor_Control/motor.h`
- `stm32/Motor_Control/encoder.c`
- `stm32/Motor_Control/encoder.h`
- `stm32/Motor_Control/pid.c`
- `stm32/Motor_Control/pid.h`
- `stm32/Src/motor_control.c`
- `stm32/Src/encoder.c`
- `stm32/Src/pid.c`
- `stm32/Inc/motor_control.h`
- `stm32/Inc/encoder.h`
- `stm32/Inc/pid.h`

The team must select one authoritative implementation for each module and avoid compiling duplicate implementations.

## Implementation Tasks

- [x] Define the motor driver interface.
- [x] Configure motor direction and PWM control.
- [x] Define motor enable, disable, and stop behavior.
- [x] Implement encoder counting.
- [x] Define encoder resolution and conversion factors.
- [x] Calculate speed or position from encoder feedback.
- [ ] Implement the PID controller.
- [ ] Define PID sample time and output limits.
- [ ] Implement integral anti-windup where required.
- [ ] Define behavior for invalid feedback and stop requests.

## Testing and Validation

- [ ] Test motor direction at low power with the drivetrain secured.
- [ ] Verify encoder counts against known movement.
- [ ] Test speed calculation.
- [ ] Evaluate PID response using recorded measurements.
- [ ] Test saturation, reversal, and stop behavior.
- [ ] Verify that faults prevent unsafe motor operation.

## Acceptance Criteria

- [ ] Motor interfaces are documented.
- [ ] Encoder scaling is verified.
- [ ] PID behavior is tested.
- [ ] Safe initialization and stop behavior are validated.

---

# Phase 05 — Sensors & Battery Monitoring

## Objective

Acquire and validate sensor and battery data for use by the robot application.

## Files Involved

- `stm32/Inc/battery.h`
- `stm32/Src/battery.c`
- `stm32/Inc/imu.h`
- `stm32/Src/imu.c`
- `stm32/Inc/sensor_manager.h`
- `stm32/Src/sensor_manager.c`
- `stm32/Inc/robot_state.h`
- `stm32/Src/robot_state.c`
- Relevant ADC, I2C, and SPI drivers.

## Implementation Tasks

- [x] Confirm sensor models and communication interfaces.
- [x] Document measurement units and operating ranges.
- [x] Implement IMU initialization and data acquisition.
- [x] Implement battery measurement and scaling.
- [x] Define sensor update rates.
- [ ] Track measurement validity and freshness.
- [ ] Detect stale, unavailable, or out-of-range readings.
- [ ] Integrate validated data with the robot state.

## Testing and Validation

- [ ] Test each sensor independently.
- [ ] Validate measurement scaling.
- [ ] Test disconnected sensors and communication timeouts.
- [ ] Test invalid measurement handling.
- [ ] Verify that stale data is identified correctly.

## Acceptance Criteria

- [ ] Sensor interfaces and units are documented.
- [ ] Invalid measurements are detected.
- [ ] Battery thresholds match the actual battery and BMS specifications.
- [ ] Sensor tests pass or limitations are recorded.

---

# Phase 06 — Safety & Fault Management

## Objective

Define and implement safe system behavior during emergency stops, communication failures, and hardware or software faults.

## Files Involved

- `stm32/Safety/emergency_stop.c`
- `stm32/Safety/emergency_stop.h`
- `stm32/Safety/fault_manager.c`
- `stm32/Safety/fault_manager.h`
- `stm32/Safety/safety_manager.c`
- `stm32/Safety/safety_manager.h`
- `stm32/Src/emergency_stop.c`
- `stm32/Src/fault_manager.c`
- `stm32/Src/safety.c`
- `stm32/Src/watchdog.c`
- `stm32/Inc/emergency_stop.h`
- `stm32/Inc/fault_manager.h`
- `stm32/Inc/safety.h`
- `stm32/Inc/watchdog.h`

Resolve duplicate implementations before integrating these modules.

## Implementation Tasks

- [ ] Define fault codes and severity levels.
- [ ] Define fault logging and recovery behavior.
- [ ] Implement emergency-stop monitoring.
- [ ] Define safe motor outputs during startup and faults.
- [ ] Handle communication loss and sensor failures.
- [ ] Implement watchdog configuration and monitoring.
- [ ] Define fault latching and clearing rules.
- [ ] Define which faults require manual acknowledgement.
- [ ] Ensure critical stopping behavior does not rely solely on a potentially blocked RTOS task.

## Testing and Validation

- [ ] Test the physical emergency-stop path.
- [ ] Test communication timeout behavior.
- [ ] Test simulated sensor failures.
- [ ] Test watchdog reset behavior on hardware.
- [ ] Verify fault recovery and latching.
- [ ] Verify that faults override movement commands.

## Acceptance Criteria

- [ ] Safety requirements and fault responses are documented.
- [ ] Emergency-stop behavior is tested on hardware.
- [ ] Watchdog behavior is verified.
- [ ] Known safety limitations are recorded.

---

# Phase 07 — CAN Communication

## Objective

Implement reliable CAN communication and establish a documented message protocol between firmware components and other robot controllers.

## Files Involved

- `stm32/CAN/can_messages.c`
- `stm32/CAN/can_messages.h`
- `stm32/CAN/can_protocol.c`
- `stm32/CAN/can_protocol.h`
- `stm32/Inc/can.h`
- `stm32/Src/can.c`
- `stm32/Inc/communication_manager.h`
- `stm32/Src/communication_manager.c`

## Implementation Tasks

- [ ] Confirm CAN peripheral and transceiver requirements.
- [ ] Define bitrate and identifier format.
- [ ] Define message IDs and payload layouts.
- [ ] Document byte order, scaling, units, and update rates.
- [ ] Implement message encoding and decoding.
- [ ] Validate received identifiers, payload lengths, and data ranges.
- [ ] Detect stale messages and communication timeouts.
- [ ] Define error and bus-off recovery behavior.
- [ ] Separate low-level CAN handling from application-level messages.

## Testing and Validation

- [ ] Test transmission and reception with suitable CAN hardware.
- [ ] Verify message IDs and payload encoding.
- [ ] Test malformed and stale messages.
- [ ] Test timeout and bus-error behavior.
- [ ] Verify safe behavior when communication is lost.

## Acceptance Criteria

- [ ] CAN protocol is documented.
- [ ] Message encoding and decoding are tested.
- [ ] Error-handling behavior is defined.
- [ ] Communication-loss handling is verified.

---

# Phase 08 — System Integration

## Objective

Integrate the RTOS, drivers, motor control, sensors, safety modules, and communication layer into a coherent firmware application.

## Files Involved

- `stm32/Src/main.c`
- `stm32/Inc/main.h`
- `stm32/Src/robot_state.c`
- `stm32/Inc/robot_state.h`
- `stm32/Src/system_config.c`
- `stm32/Inc/system_config.h`
- `stm32/Src/communication_manager.c`
- `stm32/Inc/communication_manager.h`
- All approved module interfaces.
- `stm32/RTOS/`

## Implementation Tasks

- [ ] Define the system initialization sequence.
- [ ] Define RTOS tasks and their responsibilities.
- [ ] Assign task priorities, periods, and stack sizes.
- [ ] Integrate sensor acquisition with robot state.
- [ ] Integrate motor control with encoder feedback.
- [ ] Integrate CAN communication with application commands.
- [ ] Integrate safety checks with motion control.
- [ ] Define ownership of shared data.
- [ ] Prevent motion until required health checks pass.
- [ ] Document module dependencies and data flow.

## Testing and Validation

- [ ] Test startup and initialization.
- [ ] Verify task interactions and timing.
- [ ] Verify sensor-to-state data flow.
- [ ] Verify command-to-motor data flow.
- [ ] Test communication loss during operation.
- [ ] Test sensor failures during operation.
- [ ] Verify emergency-stop priority over movement commands.

## Acceptance Criteria

- [ ] The integrated firmware builds successfully.
- [ ] Module interfaces are documented.
- [ ] Critical fault scenarios are tested.
- [ ] Safety interlocks remain active during integration.

---

# Phase 09 — Testing, Validation & Release

## Objective

Validate firmware functionality, document test evidence, and prepare a reproducible release.

## Files Involved

- `stm32/README.md`
- `tests/`, or the existing test directory.
- Module-specific test files.
- `CHANGELOG.md`
- Release documentation.
- `.github/workflows/firmware-ci.yml`, if CI is adopted.

## Implementation Tasks

- [ ] Define a test strategy and test matrix.
- [ ] Create unit tests for logic that can be tested independently.
- [ ] Define hardware tests for peripherals and safety behavior.
- [ ] Run integration and regression tests.
- [ ] Record compiler and toolchain versions.
- [ ] Record board revision and test setup.
- [ ] Review compiler warnings and static-analysis findings.
- [ ] Record memory usage and timing measurements.
- [ ] Document known issues and limitations.
- [ ] Update release notes and version information.

## Testing and Validation

- [ ] Perform a clean build from a fresh checkout.
- [ ] Run all available automated tests.
- [ ] Run required hardware validation tests.
- [ ] Review test results and unresolved failures.
- [ ] Verify documentation matches the released code.
- [ ] Confirm release artifacts are generated correctly.

## Acceptance Criteria

- [ ] Build procedure is reproducible.
- [ ] Test results are documented.
- [ ] Critical known issues are explicitly reported.
- [ ] Release version and changelog are consistent.
- [ ] Release approval is recorded.

---

# Phase 10 — Bootloader

## Objective

Implement a bootloader if firmware updates, recovery, or application image validation are required by the project.

## Files Involved

Existing directory:

- `bootloader/README.md`
- `bootloader/Inc/`
- `bootloader/Src/`

Potential files, depending on the design:

- `bootloader/Inc/bootloader.h`
- `bootloader/Inc/boot_config.h`
- `bootloader/Inc/image_validation.h`
- `bootloader/Inc/update_transport.h`
- `bootloader/Src/bootloader.c`
- `bootloader/Src/boot_config.c`
- `bootloader/Src/image_validation.c`
- `bootloader/Src/update_transport.c`
- Bootloader and application linker scripts.

## Implementation Tasks

- [ ] Confirm the need for firmware updates.
- [ ] Define the update transport.
- [ ] Define Flash memory partitioning.
- [ ] Define the application start address.
- [ ] Configure separate bootloader and application builds.
- [ ] Validate firmware images before execution.
- [ ] Define behavior for interrupted or invalid updates.
- [ ] Define boot entry and recovery procedures.
- [ ] Document integrity and authenticity requirements.

## Testing and Validation

- [ ] Test booting a valid application image.
- [ ] Test rejection of invalid images.
- [ ] Test interrupted update recovery.
- [ ] Verify application vector-table handoff.
- [ ] Verify memory layout on the actual MCU.
- [ ] Test the documented recovery procedure.

## Acceptance Criteria

- [ ] Bootloader and application memory layouts are consistent.
- [ ] Invalid or incomplete images are not executed.
- [ ] Recovery behavior is documented and tested.
- [ ] Bootloader implementation matches the agreed project requirements.

---

# Global Development Rules

## Code Quality

- Maintain one authoritative implementation for each module.
- Use consistent naming conventions.
- Document public APIs, parameters, return values, and error behavior.
- Avoid unnecessary source-file duplication.
- Keep hardware configuration documented.
- Review changes before merging.

## Safety

- Define safe output states during initialization.
- Do not rely exclusively on software task scheduling for emergency stopping.
- Test safety-critical behavior on hardware.
- Document residual risks and limitations.
- Do not perform uncontrolled movement tests.

## Git Workflow

- [ ] Use feature branches for implementation work.
- [ ] Keep commits focused on a single change.
- [ ] Run relevant builds and tests before opening a pull request.
- [ ] Review changes before merging.
- [ ] Update documentation alongside implementation changes.

## Global Definition of Done

A phase may be marked complete only when:

- [ ] Its implementation tasks are complete.
- [ ] Its acceptance criteria are satisfied.
- [ ] Relevant tests have passed or limitations are documented.
- [ ] Documentation is updated.
- [ ] Code review is complete.
- [ ] Remaining issues are recorded.

---

# Overall Project Status

| Phase | Name | Status |
|---|---|---|
| 00 | Project Audit & Architecture | Not Started |
| 01 | Build System & Configuration | Not Started |
| 02 | Low-Level Drivers | Not Started |
| 03 | Custom RTOS | Not Started |
| 04 | Motor Control & Encoders | Not Started |
| 05 | Sensors & Battery Monitoring | Not Started |
| 06 | Safety & Fault Management | Not Started |
| 07 | CAN Communication | Not Started |
| 08 | System Integration | Not Started |
| 09 | Testing & Release | Not Started |
| 10 | Bootloader | Not Started |

**Note:** Phase 10 may be deferred if a bootloader is not required for the initial prototype. Hardware-specific implementation details must be confirmed before work begins.
