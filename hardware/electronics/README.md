# Electronics Design

## Purpose

This directory contains the electrical design documents needed to connect, power, and integrate the robot's electronic modules.

## Subdirectories

### `pcb/`

Contains PCB source files, libraries, board layouts, Gerber files, drill files, and manufacturing outputs when available.

**Inputs:** Approved schematic, component footprints, board constraints, and electrical requirements.

**Outputs:** Editable PCB design, manufacturing files, and board assembly documentation.

### `pinouts/`

Contains pin mappings for the STM32, sensors, motor drivers, communication interfaces, and other modules.

**Inputs:** Selected MCU, board pinout, peripheral requirements, and datasheets.

**Outputs:** Pin tables showing signal name, MCU pin, peripheral, direction, voltage level, and connected component.

### `schematics/`

Contains circuit diagrams for power distribution, MCU interfaces, communication, motor drivers, sensors, and safety circuits.

**Inputs:** BOM, datasheets, interface requirements, and power budget.

**Outputs:** Reviewed electrical schematics and circuit-level documentation.

### `wiring/`

Contains point-to-point wiring diagrams and connection instructions for prototype assembly.

**Inputs:** Approved schematics, connector definitions, and selected hardware.

**Outputs:** Wiring diagrams, connector tables, cable labels, and assembly instructions.

## Electrical Design Requirements

* Verify logic voltage compatibility and input protection.
* Calculate expected current draw and power-converter ratings.
* Document battery polarity, fuse placement, grounding, and emergency-stop behavior.
* Check motor-driver current and thermal ratings against the selected motors.
* Document CAN wiring, termination, and transceiver requirements.
* Keep all unconfirmed pins, voltages, and connector assignments marked TBD.

## Acceptance Criteria

The schematics, pinouts, wiring diagrams, and BOM must agree. The design must be reviewed before powering the complete system.
