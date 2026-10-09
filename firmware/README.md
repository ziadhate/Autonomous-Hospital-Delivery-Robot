# Firmware Subsystem

## 1. Overview

The Firmware subsystem implements low-level control and hardware interaction on the robot's STM32 microcontroller.

It is responsible for:

* Executing validated motor commands received from the onboard computer.
* Acquiring local sensor measurements.
* Controlling motor-driver interfaces.
* Reading wheel encoder feedback.
* Managing real-time tasks through the custom RTOS.
* Monitoring communication health and local safety conditions.
* Reporting telemetry, faults, and system status.
* Executing defined local safety behavior when ROS 2, the dashboard, or AI software becomes unavailable.

The firmware is responsible for immediate local control and safety behavior. High-level navigation, SLAM, AI inference, and mission planning normally run on the Linux computer.

### Input

* Validated commands from the onboard computer.
* Sensor measurements and encoder feedback.
* Emergency-stop and other local hardware signals.
* RTOS timing and scheduling events.
* Firmware configuration and hardware status.

### Output

* PWM and direction signals for motor drivers.
* Local sensor measurements.
* Motor speed and encoder information.
* System status and fault reports.
* CAN telemetry.
* Safe-stop or motor-disable requests.

**Important:** This document describes the intended architecture. A documented feature must not be considered implemented until its source code, configuration, and tests exist.

---

## 2. Directory Structure

```text
firmware/
├── README.md
├── bootloader/
│   ├── README.md
│   ├── src/
│   └── config/
└── stm32/
    ├── Inc/
    │   ├── main.h
    │   ├── app_config.h
    │   ├── app_tasks.h
    │   ├── system_status.h
    │   └── error_codes.h
    ├── Src/
    │   ├── main.c
    │   ├── app_tasks.c
    │   ├── system_status.c
    │   └── error_codes.c
    ├── Drivers/
    │   ├── gpio/
    │   ├── clock/
    │   ├── timer/
    │   ├── pwm/
    │   ├── uart/
    │   ├── spi/
    │   ├── i2c/
    │   ├── adc/
    │   ├── can/
    │   ├── encoder/
    │   └── watchdog/
    ├── RTOS/
    │   ├── Inc/
    │   ├── Src/
    │   └── port/
    │       └── cortex_m4/
    ├── CAN/
    │   ├── can_protocol.h
    │   ├── can_protocol.c
    │   ├── can_service.h
    │   └── can_service.c
    ├── Motor_Control/
    │   ├── motor_config.h
    │   ├── motor_control.h
    │   ├── motor_control.c
    │   ├── speed_controller.h
    │   └── speed_controller.c
    ├── Safety/
    │   ├── safety.h
    │   ├── safety.c
    │   ├── fault_manager.h
    │   └── fault_manager.c
    └── Sensors/
        ├── sensor_manager.h
        ├── sensor_manager.c
        ├── imu_driver.h
        └── imu_driver.c
```

This is a proposed logical structure. The actual implementation may use different filenames, additional build files, STM32 HAL, CMSIS, or existing RTOS modules.

Only create the drivers and files required by the selected hardware and actual implementation.

---

## 3. `bootloader/` — Startup and Firmware Update

### 3.1 Purpose

The bootloader is optional software that executes before the main application. It can validate an application image and, if implemented, support firmware updates.

### 3.2 Bootloader source files

The actual source filenames depend on the chosen implementation.

**Input:**

* Processor reset.
* Application image stored in the designated flash region.
* Image metadata or integrity information, if implemented.
* Update requests, if a firmware-update mechanism exists.

**Output:**

* Transfer of execution to a valid application.
* Recovery or error state if the application is invalid.
* Update status, if supported.

**Responsibilities:**

* Initialize the peripherals required by the bootloader.
* Validate the application according to the defined policy.
* Check the application location and required startup information.
* Transfer control to the application using the correct processor startup procedure.
* Provide documented recovery behavior if validation fails.

**Dependencies:**

* Startup code.
* Flash-memory layout.
* Linker configuration.
* Optional communication and flash-programming drivers.

### 3.3 `bootloader/README.md`

**Purpose:** Documents the bootloader design and operating procedure.

**Input:**

* Memory-layout information.
* Bootloader implementation details.
* Update and recovery requirements.

**Output:**

* Instructions for building and testing the bootloader.
* Documented flash regions.
* Update and recovery procedures.

### 3.4 `bootloader/config/`

Contains bootloader-specific configuration if the design requires it.

**Input:** Approved memory layout, image format, and update configuration.

**Output:** Configuration consumed by the bootloader build.

**Important:** Do not assume that secure firmware updates, cryptographic signatures, or rollback protection exist unless they have been implemented and tested.

---

## 4. `stm32/Inc/` — Application Header Files

Header files define interfaces, data types, constants, and function prototypes shared by the firmware modules.

### 4.1 `main.h`

**Purpose:** Defines declarations required by the application entry point.

**Input:**

* Shared application declarations.
* Required initialization interfaces.
* Common platform definitions.

**Output:**

* Function prototypes and types consumed by `main.c`.

**Responsibilities:**

* Declare shared initialization functions.
* Include common definitions when needed.
* Avoid duplicating peripheral implementations.

**Dependencies:** Application and platform headers.

### 4.2 `app_config.h`

**Purpose:** Centralizes application-level configuration.

**Input:**

* Approved timing requirements.
* Communication timeout requirements.
* Motor-control limits.
* Application feature configuration.

**Output:**

* Compile-time constants used by application modules.

**Responsibilities:**

* Define application timing and configuration values.
* Prevent unexplained numeric values from being scattered across the source code.
* Document the units and purpose of configurable values.

Any numerical examples must be treated as placeholders until validated against system requirements and hardware testing.

### 4.3 `app_tasks.h`

**Purpose:** Declares application RTOS tasks.

**Input:** Application task design and the selected RTOS API.

**Output:** Task function prototypes used by task initialization code.

Possible task interfaces include:

```c
void Communication_Task(void *argument);
void Motor_Control_Task(void *argument);
void Safety_Task(void *argument);
void Sensor_Task(void *argument);
```

These signatures are examples only. They must match the actual RTOS API.

**Responsibilities:**

* Declare task entry points.
* Document each task's purpose and execution requirements.
* Separate declarations from implementations.

### 4.4 `system_status.h`

**Purpose:** Defines shared system states and status interfaces.

**Input:** Approved system-state definitions and operating requirements.

**Output:** State types and function declarations.

Possible states include:

* Initialization.
* Ready.
* Running.
* Stopping.
* Fault.

**Responsibilities:**

* Define permitted state transitions.
* Provide consistent system-status information.
* Prevent the application from reporting that it is ready before required initialization and checks finish.

### 4.5 `error_codes.h`

**Purpose:** Defines standardized firmware error identifiers.

**Input:** Approved error and fault definitions.

**Output:** Common identifiers used by drivers and application modules.

Possible categories include:

* Peripheral initialization failure.
* CAN timeout.
* Invalid command.
* Sensor read failure.
* Motor-control fault.
* Watchdog or processor fault.

**Responsibilities:**

* Assign consistent identifiers.
* Document error conditions.
* Distinguish recoverable errors from faults that require a safe stop.

---

## 5. `stm32/Src/` — Application Source Files

### 5.1 `main.c`

**Purpose:** Provides the application entry point and startup sequence.

**Input:**

* Reset and startup state.
* Application configuration.
* Peripheral initialization interfaces.
* RTOS initialization and task-creation interfaces.

**Output:**

* Initialized peripherals and modules.
* Created application tasks.
* Started RTOS scheduling, if used.

**Responsibilities:**

1. Perform required platform initialization.
2. Initialize clocks and required peripherals in the correct order.
3. Initialize communication, motor control, sensors, and safety modules.
4. Check initialization results.
5. Enter a defined fault or safe state if required initialization fails.
6. Create application tasks.
7. Start the scheduler if supported by the RTOS.

**Dependencies:** Clock, GPIO, CAN, motor-control, sensor, safety, and RTOS interfaces.

### 5.2 `app_tasks.c`

**Purpose:** Implements application-level tasks and coordinates the firmware modules.

**Input:**

* Received commands.
* Sensor measurements.
* Encoder feedback.
* Safety state.
* RTOS events and services.

**Output:**

* Motor-control requests.
* Periodic sensor processing.
* Status and telemetry updates.
* Fault reports.

**Responsibilities:**

* Implement each task's work.
* Keep periodic work within its timing requirements.
* Avoid blocking critical safety processing with slow operations.
* Protect shared data using supported synchronization mechanisms.
* Handle module errors according to the defined policy.

**Dependencies:** RTOS, CAN, Motor_Control, Safety, Sensors, and system-status interfaces.

### 5.3 `system_status.c`

**Purpose:** Implements system-state management.

**Input:**

* Initialization results.
* Communication status.
* Safety decisions.
* Application events.

**Output:**

* Current system state.
* State-transition results.
* Status information for telemetry.

**Responsibilities:**

* Store and expose system state.
* Validate permitted transitions.
* Prevent inconsistent status reporting.

### 5.4 `error_codes.c`

**Purpose:** Implements error-handling helpers if required.

**Input:** Error identifiers and optional diagnostic information.

**Output:** Error classification, diagnostic information, or formatted error messages.

**Responsibilities:**

* Map errors to documented categories.
* Support fault reporting.
* Avoid blocking operations in critical execution contexts.

If error codes are only enumerations in a header, a separate `.c` file may not be necessary.

---

## 6. `stm32/Drivers/` — Peripheral and Device Drivers

A driver provides an interface to a hardware peripheral or external device. It should not perform high-level navigation or mission planning.

Each implemented driver must document its hardware, configuration, inputs, outputs, return values, timing behavior, and failure conditions.

### 6.1 GPIO Driver

**Purpose:** Configures and controls digital input/output pins.

**Input:**

* Port and pin.
* Pin mode.
* Output state.
* Input-read request.

**Output:**

* High or low output signal.
* Digital input state.
* Operation status.

**Responsibilities:**

* Configure input and output pins.
* Read digital inputs.
* Control enable and direction signals where assigned to GPIO.
* Configure alternate-function pins for peripherals.
* Apply appropriate electrical configuration and safe startup levels.

**Dependencies:** STM32 GPIO peripheral or HAL.

**Possible uses:** Emergency-stop status input, motor-enable signal, status LED, and peripheral chip-select.

A software GPIO input does not replace a properly designed hardware emergency-stop circuit.

### 6.2 Clock Driver

**Purpose:** Configures the system and peripheral clocks.

**Input:**

* Clock-source selection.
* Divider and multiplier settings.
* Oscillator configuration requirements.

**Output:**

* Configured clock frequencies.
* Clock initialization status.

**Responsibilities:**

* Configure the selected clock source.
* Configure supported clock dividers and multipliers.
* Enable required peripheral clocks.
* Document resulting clock frequencies.

**Dependencies:** STM32 clock-control hardware and startup configuration.

Incorrect clock configuration can affect UART baud rate, CAN timing, PWM frequency, and RTOS timing.

### 6.3 Timer Driver

**Purpose:** Configures and operates hardware timers.

**Input:**

* Timer instance.
* Prescaler and period.
* Timer mode.
* Interrupt, capture, or compare configuration.

**Output:**

* Timer events.
* Counter values.
* Input-capture measurements where configured.
* Operation status.

**Responsibilities:**

* Initialize timer peripherals.
* Configure periodic events.
* Support capture and compare operations where required.
* Provide timing services to dependent modules.

**Dependencies:** STM32 timer peripherals and clock configuration.

The RTOS system tick and application timers must be configured without conflicting with one another.

### 6.4 PWM Driver

**Purpose:** Generates Pulse Width Modulation signals.

**Input:**

* Timer and channel.
* PWM frequency.
* Duty-cycle request.
* Output-enable or disable request.

**Output:**

* PWM waveform.
* Operation status.
* Configured duty cycle, if exposed by the interface.

**Responsibilities:**

* Configure timer channels for PWM.
* Convert duty-cycle requests into timer compare values.
* Enforce configured limits.
* Disable outputs when required.
* Document output behavior during initialization and faults.

**Dependencies:** Timer Driver and STM32 timer hardware.

PWM duty cycle is not identical to motor speed. Speed depends on the motor, load, motor driver, supply voltage, and control algorithm.

### 6.5 UART Driver

**Purpose:** Provides asynchronous serial communication.

**Input:**

* Transmit buffer and length.
* UART configuration.
* Receive requests or incoming serial data.

**Output:**

* Transmitted and received bytes.
* Transmission or reception status.
* Communication error information.

**Responsibilities:**

* Configure baud rate, data bits, parity, and stop bits.
* Transmit and receive data.
* Support interrupt or DMA operation if implemented.
* Report supported communication errors.

**Dependencies:** STM32 USART/UART peripheral.

**Possible uses:** Debug console, optional bootloader communication, or UART-based peripherals.

### 6.6 SPI Driver

**Purpose:** Communicates with SPI peripherals.

**Input:**

* SPI instance and configuration.
* Transmit buffer.
* Receive buffer.
* Transfer length.
* Chip-select configuration where required.

**Output:**

* Received bytes.
* Transfer completion status.
* Communication error information.

**Responsibilities:**

* Configure clock polarity and phase.
* Configure bit order and transfer format.
* Manage chip-select if assigned to the driver.
* Support blocking, interrupt, or DMA transfers as required.
* Report transfer failures.

**Dependencies:** STM32 SPI peripheral and GPIO where required.

**Possible uses:** SPI-based IMUs, external ADCs, or other SPI devices.

### 6.7 I2C Driver

**Purpose:** Communicates with I2C peripherals.

**Input:**

* I2C instance.
* Device address.
* Register address where applicable.
* Transmit or receive buffer.
* Transfer length and timeout.

**Output:**

* Received device data.
* Transfer status.
* Error information, such as NACK or timeout where detected.

**Responsibilities:**

* Configure I2C timing.
* Read and write device registers.
* Detect communication failures.
* Apply timeout handling to prevent indefinite blocking.

**Dependencies:** STM32 I2C peripheral.

**Possible uses:** IMU, temperature sensor, or other I2C-compatible devices.

### 6.8 ADC Driver

**Purpose:** Converts analog input voltages into digital measurements.

**Input:**

* ADC instance and channel.
* Sampling configuration.
* Conversion request or trigger.
* Analog input voltage within the supported electrical range.

**Output:**

* Raw ADC value.
* Conversion status.
* Optional converted voltage or engineering-unit value.

**Responsibilities:**

* Configure ADC channels.
* Start and retrieve conversions.
* Report supported conversion errors.
* Apply calibration and scaling in the appropriate software layer.

**Dependencies:** STM32 ADC peripheral and clock configuration.

**Possible uses:** Battery-voltage sensing or analog current and distance sensors.

External circuitry must keep the ADC input within the MCU's electrical limits.

### 6.9 CAN Peripheral Driver

**Purpose:** Provides low-level access to the CAN controller.

**Input:**

* CAN configuration and bit timing.
* Message identifier and frame format.
* Payload bytes and length.
* Received frames and controller status.

**Output:**

* Transmitted CAN frames.
* Received CAN frames.
* Transmission status.
* Controller and bus error information.

**Responsibilities:**

* Configure the CAN peripheral.
* Configure supported message filters.
* Transmit and receive frames.
* Handle receive and transmit events.
* Report controller and bus errors.

**Dependencies:** CAN controller, clock configuration, and a suitable physical CAN transceiver.

**Hardware verification is mandatory:** Confirm that the exact selected STM32 part supports the required CAN peripheral. If it does not, the architecture must use a compatible external CAN controller or a different MCU. A CAN transceiver alone does not replace a missing CAN controller.

### 6.10 Encoder Driver

**Purpose:** Reads wheel encoder signals and exposes position or speed measurements.

**Input:**

* Encoder signals.
* Timer encoder-mode configuration or GPIO/interrupt events.
* Encoder resolution.
* Measurement interval.

**Output:**

* Encoder count or position.
* Count difference over a measurement interval.
* Estimated speed if calculated by the driver.
* Measurement validity or error status.

**Responsibilities:**

* Configure encoder input pins.
* Count pulses or read timer encoder counters.
* Handle counter rollover.
* Define consistent count units.
* Document resolution and measurement timing.

**Dependencies:** Timer, GPIO, and interrupt services where required.

Speed conversion depends on encoder resolution, quadrature decoding, gearbox ratio, wheel circumference, and measurement interval.

### 6.11 Watchdog Driver

**Purpose:** Configures and services the supported hardware watchdog.

**Input:**

* Watchdog configuration.
* Approved watchdog-service request.
* System-health information if checked by the calling module.

**Output:**

* Initialization and service status.
* Hardware reset if the watchdog expires, according to its configuration.

**Responsibilities:**

* Initialize the watchdog.
* Define which health conditions permit servicing.
* Avoid allowing an unhealthy task to keep the watchdog alive indefinitely.
* Document reset and recovery behavior.

**Dependencies:** STM32 watchdog peripheral and its clock requirements.

The watchdog does not replace an emergency-stop circuit. Hardware must be designed so that a reset or loss of control cannot leave the motor outputs unsafe.

### 6.12 Driver Interface Requirements

Every implemented driver must document:

* Supported peripheral or device.
* Initialization requirements.
* Function parameters and units.
* Output values and return codes.
* Blocking behavior and timeout rules.
* Interrupt and DMA usage, if any.
* Shared-resource restrictions.
* Failure behavior.
* Testing procedure.

Not every listed driver is necessarily required. For example, do not create SPI or ADC drivers if the selected hardware does not use those peripherals.

---

## 7. `stm32/RTOS/` — Custom Real-Time Operating System

The RTOS manages application task execution and provides the scheduling and synchronization features implemented by the custom kernel.

### 7.1 `RTOS/Inc/`

**Purpose:** Contains public RTOS headers.

**Input:** Kernel API design and supported features.

**Output:**

* Task types.
* Kernel status codes.
* Configuration declarations.
* Function prototypes.

**Responsibilities:**

* Define the public kernel interface.
* Document supported APIs.
* Keep application modules independent of internal scheduler details.

The exact filenames depend on the existing RTOS implementation.

### 7.2 `RTOS/Src/`

**Purpose:** Implements architecture-independent kernel functionality.

Possible modules include:

* Task management.
* Scheduler and task-state handling.
* Delay and timeout handling.
* Synchronization primitives, if implemented.
* Critical sections.
* Kernel initialization.

**Input:**

* Task creation requests.
* Scheduling events.
* Tick updates.
* Synchronization operations.
* Task-state changes.

**Output:**

* Selected next task.
* Task-state transitions.
* Timeout and synchronization results.
* Kernel status.

Only features actually implemented in the custom kernel may be used by application code.

### 7.3 `RTOS/port/`

**Purpose:** Defines the interface between the generic kernel and architecture-specific code.

**Input:** Kernel requests for context switching and processor-specific operations.

**Output:** Architecture-specific operations required by the kernel.

**Responsibilities:**

* Separate generic scheduling logic from processor-specific implementation.
* Document the supported architecture and compiler assumptions.

### 7.4 `RTOS/port/cortex_m4/`

**Purpose:** Implements Cortex-M4-specific context management and exception handling.

Possible responsibilities include:

* Initial task-stack construction.
* Context save and restore.
* PendSV-based switching where used.
* SysTick integration where used.
* SVC integration where used.
* Interrupt-priority configuration.

**Input:**

* CPU context.
* Task stack pointers.
* Scheduler-selected task.
* Processor exceptions and interrupt events.

**Output:**

* Restored task context.
* Processor-state transitions.
* Control transfer to the selected task.

**Dependencies:** Cortex-M4 architecture, compiler ABI, startup code, and the kernel scheduler.

Floating-point context handling must match the target configuration and task requirements.

### 7.5 RTOS Integration Rules

* Verify that every RTOS API used by the application actually exists.
* Document task priorities and timing requirements.
* Verify synchronization and interrupt-safety guarantees.
* Avoid calling blocking functions from interrupt handlers unless explicitly supported.
* Test stack usage and context switching on the selected target.

---

## 8. `stm32/CAN/` — Communication Protocol and Service

This module connects the low-level CAN driver to the application protocol.

### 8.1 `can_protocol.h`

**Purpose:** Defines protocol constants, message types, and encoding/decoding interfaces.

**Input:** The agreed protocol between the STM32 and onboard computer.

**Output:** Message identifiers, data structures, units, and function declarations.

**Responsibilities:**

* Define message identifiers.
* Document payload layouts.
* Define units, scaling, and valid ranges.
* Document message versions where required.

### 8.2 `can_protocol.c`

**Purpose:** Converts structured application data into CAN payloads and decodes received payloads.

**Input:**

* Structured command or telemetry data.
* Received message identifier and payload.

**Output:**

* Encoded payload bytes.
* Decoded message structures.
* Validation result.

**Responsibilities:**

* Encode and decode fields.
* Validate expected payload lengths.
* Reject unsupported values.
* Handle byte order and signedness explicitly.

### 8.3 `can_service.h`

**Purpose:** Defines the application-facing CAN service interface.

**Input:** Requests to transmit messages and query communication status.

**Output:** Function declarations for transmitting telemetry, receiving commands, and checking link health.

### 8.4 `can_service.c`

**Purpose:** Coordinates CAN reception, transmission, and message dispatch.

**Input:**

* Received CAN frames.
* Protocol definitions.
* Application telemetry.
* Transmission requests.

**Output:**

* Decoded commands.
* Outgoing telemetry and fault messages.
* Communication-health status.
* Communication error reports.

**Responsibilities:**

* Receive and dispatch messages.
* Reject invalid or unsupported commands.
* Track the last valid heartbeat when required.
* Detect stale communication according to the agreed timeout.
* Notify the Safety module when communication is lost.

**Dependencies:** CAN peripheral driver, protocol implementation, and application-status interfaces.

### 8.5 CAN Protocol Contract

Firmware and ROS 2 developers must agree on:

* Message identifiers.
* Payload layout and length.
* Byte order and signedness.
* Units and scaling.
* Valid command ranges.
* Heartbeat interval and timeout.
* Stale-command behavior.
* Telemetry frequency.
* Fault identifiers and acknowledgment rules.

No message identifier or timeout is final until both teams agree on the protocol.

---

## 9. `stm32/Motor_Control/` — Low-Level Motor Control

### 9.1 `motor_config.h`

**Purpose:** Stores motor-control configuration.

**Input:** Approved motor specifications, encoder specifications, and hardware limits.

**Output:** Configuration constants used by motor-control modules.

**Responsibilities:**

* Define motor count and channel mapping.
* Define permitted command ranges.
* Define encoder scaling.
* Define control-loop timing and tuning parameters.
* Document configuration units.

### 9.2 `motor_control.h`

**Purpose:** Defines the public motor-control interface.

**Input:** Approved command format and motor-state definitions.

**Output:** Function prototypes and shared motor-control types.

**Responsibilities:**

* Define initialization and update interfaces.
* Define accepted command units and ranges.
* Document reported motor state and return codes.

### 9.3 `motor_control.c`

**Purpose:** Converts validated motion requests into bounded motor-driver operations.

**Input:**

* Validated wheel-speed or direction commands.
* Encoder feedback.
* Safety permission.
* Motor configuration.

**Output:**

* PWM and direction requests.
* Updated motor-control state.
* Measured speed if supported.
* Motor-control error status.

**Responsibilities:**

* Validate commands.
* Enforce configured limits.
* Coordinate PWM, direction, and encoder interfaces.
* Apply the defined stop behavior when motion is prohibited.
* Detect stale commands and control errors.
* Avoid high-level path planning.

**Dependencies:** PWM Driver, GPIO Driver, Encoder Driver, Safety interface, and motor configuration.

### 9.4 `speed_controller.h`

**Purpose:** Defines the speed-control algorithm interface.

**Input:** Target speed, measured speed, and controller configuration.

**Output:** Function declarations and controller data types.

### 9.5 `speed_controller.c`

**Purpose:** Implements the selected speed-control algorithm, such as PI or PID, if closed-loop control is required.

**Input:**

* Target wheel speed.
* Measured wheel speed.
* Controller gains and limits.
* Update interval.

**Output:**

* Bounded control effort or PWM request.
* Optional error and controller-state values.
* Saturation or invalid-measurement status.

**Responsibilities:**

* Calculate speed error.
* Apply the selected control law.
* Limit output.
* Handle saturation and integral behavior where applicable.
* Reject invalid feedback.
* Maintain predictable execution time.

**Dependencies:** Encoder measurements and approved motor configuration.

PID is not mandatory if the prototype uses open-loop control. The selected approach and its limitations must be documented.

### 9.6 Motor-Control Data Flow

1. The CAN service receives a motion command.
2. The protocol layer validates and decodes it.
3. The application checks whether the command is fresh and valid.
4. The Safety module determines whether motion is permitted.
5. The motor-control module generates the requested output.
6. The PWM and GPIO drivers operate the motor-driver interface.
7. The encoder driver measures wheel motion.
8. The controller updates the next output if closed-loop control is implemented.
9. Status and faults are reported through CAN.

---

## 10. `stm32/Safety/` — Local Safety and Fault Handling

### 10.1 `safety.h`

**Purpose:** Defines safety states and protective-action interfaces.

**Input:** Safety requirements and approved fault categories.

**Output:** Function declarations and safety-state types.

**Responsibilities:**

* Define when motor operation is permitted.
* Define protective actions for supported faults.
* Define recovery conditions.

### 10.2 `safety.c`

**Purpose:** Evaluates local safety conditions and determines whether motor operation is permitted.

**Input:**

* Emergency-stop status.
* Communication-health status.
* Command validity and freshness.
* Watchdog and system-fault indicators.
* Sensor and motor-control status.

**Output:**

* Motion-permission state.
* Safe-stop request.
* Fault state.
* Recovery eligibility where supported.

**Responsibilities:**

* Prevent new motion commands when safety conditions are not satisfied.
* Detect communication loss according to the approved timeout.
* Apply the defined safe-stop behavior.
* Require the specified recovery conditions.
* Report safety state through telemetry.

**Dependencies:** GPIO, CAN service, motor-control interfaces, watchdog status, and system-status interfaces.

Software safety does not replace suitable hardware-level protection.

### 10.3 `fault_manager.h`

**Purpose:** Defines interfaces for registering, querying, and clearing supported faults.

**Input:** Fault identifiers and fault metadata.

**Output:** Fault-query declarations and fault-clear results.

### 10.4 `fault_manager.c`

**Purpose:** Maintains the application's fault state.

**Input:**

* Fault events.
* Recovery or acknowledgment requests.
* Fault-clear conditions.

**Output:**

* Active-fault information.
* Fault category or severity.
* Fault history if implemented.
* Fault-clear result.

**Responsibilities:**

* Record faults consistently.
* Distinguish warnings from motion-inhibiting faults.
* Prevent clearing a fault while its triggering condition remains active.
* Report faults through the CAN service.
* Preserve critical fault information according to the designed logging mechanism.

Persistent fault logging requires an explicitly implemented storage mechanism.

### 10.5 Safety Input/Output Summary

| Input                   | Expected safety decision or output                              |
| ----------------------- | --------------------------------------------------------------- |
| Emergency stop active   | Apply the designed protective stop behavior                     |
| Communication timeout   | Reject stale commands and enter the defined safe state          |
| Invalid motion command  | Reject the command and report the error                         |
| Encoder failure         | Apply the documented response for lost feedback                 |
| Motor-driver fault      | Disable or stop motion according to the hardware design         |
| Watchdog reset          | Follow the documented startup and recovery procedure            |
| Fault condition cleared | Permit recovery only when all required conditions are satisfied |

The exact response for each fault must be defined and tested against the physical motor driver and robot mechanics.

---

## 11. `stm32/Sensors/` — Local Sensor Acquisition

### 11.1 `sensor_manager.h`

**Purpose:** Defines the public interface for local sensor acquisition and sensor status.

**Input:** Sensor configuration and sampling requirements.

**Output:** Sensor data types, validity flags, and acquisition function declarations.

### 11.2 `sensor_manager.c`

**Purpose:** Coordinates the sensors assigned to the STM32.

**Input:**

* Raw data from hardware drivers.
* Sampling requests.
* Sensor initialization results.

**Output:**

* Processed or normalized measurements.
* Validity flags.
* Sensor error status.
* Timestamps or sequence numbers if implemented.

**Responsibilities:**

* Initialize required local sensors.
* Request measurements.
* Validate returned data.
* Detect invalid or stale measurements where supported.
* Provide a consistent interface to other modules.

**Dependencies:** Appropriate peripheral and device drivers.

### 11.3 `imu_driver.h`

**Purpose:** Defines the interface for the selected IMU.

**Input:** Sensor configuration and requested measurement operations.

**Output:** IMU data types and function declarations.

### 11.4 `imu_driver.c`

**Purpose:** Communicates with the selected IMU and obtains supported measurements.

**Input:**

* I2C or SPI transactions.
* Sensor configuration.
* Data-ready events or polling requests.

**Output:**

* Raw accelerometer and gyroscope readings where supported.
* Temperature or other supported measurements.
* Converted physical units if implemented.
* Sensor status and communication errors.

**Responsibilities:**

* Initialize the selected sensor.
* Read device identity or status where supported.
* Retrieve measurement data.
* Apply documented scale factors.
* Report invalid readings and communication failures.

**Dependencies:** I2C or SPI Driver and the selected sensor's datasheet.

Calibration, filtering, coordinate-frame conventions, and sensor fusion must be assigned explicitly. An IMU driver should not claim to provide a fused orientation unless that feature is actually implemented.

### 11.5 Sensor Placement Rules

* Sensors physically connected to the STM32 are handled through the relevant firmware drivers.
* Cameras and LiDAR connected directly to the Linux computer should normally use their Linux/ROS 2 drivers.
* Sensor units, sample rates, coordinate frames, and validity rules must be documented.
* A sensor failure must be reported to any module that depends on that measurement.

---

## 12. Main Data Flow

```text
Raspberry Pi / ROS 2
        |
        | Motion command
        v
CAN Service
        |
        v
Protocol Validation
        |
        v
Safety Permission Check
        |
        v
Motor Control
        |
        +--------> Speed Controller (if implemented)
        |                     ^
        v                     |
PWM / Direction Driver    Encoder Driver
        |                     ^
        v                     |
Motor Driver <------------- Motors

Local Sensors
        |
        v
Sensor Manager
        |
        +--------> Safety Module
        |
        +--------> CAN Telemetry

Communication Health ------> Safety Module
Watchdog Status ------------> Safety Module
Emergency Stop -------------> Hardware Protection + Safety Status
```

This is a logical architecture. Actual data paths depend on the selected hardware and implementation.

---

## 13. Testing

### 13.1 Build and Interface Tests

**Input:** Source files, headers, compiler configuration, and linker configuration.

**Output:** Successful build or documented compilation/linker errors.

Tests should verify:

* All required source files are included in the build.
* Declared functions have matching implementations.
* Header dependencies are correct.
* Configuration values match the selected target.

### 13.2 Driver Tests

**Input:** Driver configuration, test signals, and hardware or test doubles.

**Output:** Measured driver behavior, status codes, and detected errors.

Tests should cover:

* GPIO input and output behavior.
* Timer configuration and PWM frequency.
* UART, SPI, I2C, and ADC only where used.
* CAN transmission and reception.
* Encoder count direction and scaling.
* Watchdog operation under controlled conditions.

### 13.3 RTOS Tests

**Input:** Task definitions, priorities, timing requests, and synchronization operations.

**Output:** Scheduling behavior, task-state transitions, and timing measurements.

Tests should cover:

* Task creation.
* Scheduling and context switching.
* Tick and delay behavior.
* Implemented synchronization APIs.
* Stack usage and timing behavior.

### 13.4 Motor-Control Tests

**Input:** Valid and invalid commands, encoder feedback, and safety state.

**Output:** Motor-driver signals, measured wheel speed, and error reports.

Tests should cover:

* Motor direction.
* PWM limits.
* Encoder feedback.
* Command timeout.
* Rejection of motion commands when motion is not permitted.

Initial physical tests must use an approved safe procedure, such as raising the drive wheels or mechanically isolating the drive.

### 13.5 Safety Tests

**Input:** Controlled fault conditions such as communication loss, emergency stop, or invalid feedback.

**Output:** Protective response, fault status, and recovery result.

Tests should cover:

* Emergency-stop behavior.
* Communication-loss response.
* Invalid and stale commands.
* Sensor and driver failures.
* Recovery conditions.
* Motor-driver behavior after reset or loss of control signals.

---

## 14. Definition of Done

A firmware feature is complete when:

* Its responsibility is documented.
* Its inputs, outputs, units, and return codes are defined.
* Its dependencies are identified.
* Its implementation matches the selected hardware.
* It compiles for the selected target.
* Normal and failure behavior are tested.
* Integration interfaces are agreed upon.
* Safety-related behavior has measurable acceptance criteria.

A directory or placeholder file does not prove that a feature has been implemented.

---

## 15. Cross-Team Contract

### Firmware and ROS 2

Must agree on:

* Command units and valid ranges.
* CAN identifiers and payload layouts.
* Heartbeat and timeout behavior.
* Telemetry frequency.
* Fault reporting and acknowledgment.
* Motion-command freshness rules.

### Firmware and Hardware

Must agree on:

* Exact MCU part number and peripheral capabilities.
* Pin assignments.
* Voltage levels and electrical interfaces.
* Motor-driver interface.
* Encoder signal configuration.
* Power limits and emergency-stop circuitry.

### Firmware and RTOS

Must agree on:

* Task priorities.
* Timing requirements.
* Synchronization behavior.
* Interrupt restrictions.
* Stack requirements.
* Supported kernel APIs.

### Firmware and Testing

Must agree on:

* Test inputs and expected outputs.
* Fault-injection scenarios.
* Test equipment.
* Acceptance criteria.
* Safe physical testing procedures.

### Firmware and AI

AI detection results must not bypass command validation or local safety checks. The STM32 should execute only commands supported by the agreed control interface.

---

## 16. File and Driver Input/Output Summary

| File or driver       | Main input                                      | Main output                                   |
| -------------------- | ----------------------------------------------- | --------------------------------------------- |
| `main.c`             | Startup and configuration                       | Initialized application                       |
| `app_tasks.c`        | Commands, sensor data, RTOS events              | Coordinated application behavior              |
| `system_status.c`    | System and module events                        | Current system state                          |
| `error_codes.h`      | Approved error definitions                      | Standard error identifiers                    |
| GPIO Driver          | Pin configuration and read/write requests       | Digital states and operation status           |
| Clock Driver         | Clock configuration                             | Configured clocks and status                  |
| Timer Driver         | Timer settings and events                       | Timing events and counter values              |
| PWM Driver           | Frequency and duty-cycle request                | PWM waveform and status                       |
| UART Driver          | Byte buffers and serial data                    | Transmitted/received bytes and status         |
| SPI Driver           | Transfer configuration and buffers              | Received data and transfer status             |
| I2C Driver           | Device address and transactions                 | Device data and transfer status               |
| ADC Driver           | Analog channel and conversion request           | Raw digital measurements                      |
| CAN Driver           | Frames and controller configuration             | Transmitted/received frames and status        |
| Encoder Driver       | Encoder signals and measurement interval        | Counts, position, or speed                    |
| Watchdog Driver      | Configuration and valid service request         | Watchdog status or reset on expiry            |
| `can_protocol.c`     | Structured data or received payload             | Encoded/decoded messages                      |
| `can_service.c`      | Frames and telemetry requests                   | Commands, telemetry, and link status          |
| `motor_control.c`    | Validated commands and feedback                 | PWM/direction requests and motor state        |
| `speed_controller.c` | Target and measured speed                       | Bounded control effort                        |
| `safety.c`           | Emergency stop, communication, and fault states | Motion permission and protective-stop request |
| `fault_manager.c`    | Fault events and clear requests                 | Active-fault state and clear result           |
| `sensor_manager.c`   | Driver measurements                             | Validated sensor data and status              |
| `imu_driver.c`       | Bus transactions and sensor configuration       | IMU readings and error status                 |
| Bootloader source    | Reset and application image                     | Application handoff or recovery state         |

All function signatures, units, numerical limits, message identifiers, timing values, and hardware assignments must be confirmed against the actual implementation. This README defines the intended design contract, not proof that every listed feature already exists.
