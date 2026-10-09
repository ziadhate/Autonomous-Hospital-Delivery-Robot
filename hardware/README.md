# Hardware Subsystem

## 1. Overview

The Hardware subsystem defines the physical components, electrical architecture, mechanical structure, and power system of the Autonomous AI-Powered Hospital Delivery & Infection-Control Robot.

Its purpose is to provide a stable platform for autonomous indoor navigation, secure delivery, sensor integration, and safe interaction with the environment.

This directory documents hardware requirements and interfaces. It does not necessarily contain the firmware or ROS 2 source code that operates the hardware.

## 2. Directory Structure

```text
hardware/
├── README.md
├── bom/
│   └── bom.csv                 # Proposed component inventory
├── electronics/
│   ├── schematics/             # Proposed circuit diagrams
│   ├── wiring.md               # Proposed wiring documentation
│   ├── pinout.md               # Proposed pin assignments
│   ├── interfaces.md           # Proposed electrical interfaces
│   └── power_budget.md         # Proposed power calculations
└── mechanical/
    ├── cad/                    # Proposed CAD files
    ├── dimensions.md           # Proposed robot dimensions
    ├── assembly.md             # Proposed assembly instructions
    └── materials.md            # Proposed material selection
```

The listed files are suggested organizational choices. Create them only when needed and adapt the structure to the actual repository.

## 3. Main Subdirectories

### 3.1 bom/

Maintains the Bill of Materials (BOM).

**Purpose:**

* Identify every required component.
* Record quantities, suppliers, and prices.
* Compare alternatives.
* Track purchase and availability status.

**Input:**

* Project requirements.
* Datasheets and component specifications.
* Supplier quotations.
* Hardware team decisions.

**Output:**

* Approved component list.
* Estimated project cost.
* Selected part numbers.
* Alternative components and purchasing status.

### 3.2 electronics/

Documents electrical connections and electronic design.

**Purpose:**

* Define power distribution.
* Document signal connections and connectors.
* Record voltage and current requirements.
* Explain interfaces between the STM32, sensors, motors, and onboard computer.

**Input:**

* Selected component datasheets.
* STM32 pin capabilities.
* Motor and sensor electrical specifications.
* Mechanical mounting requirements.

**Output:**

* Schematics.
* Wiring diagrams.
* Pin assignments.
* Power calculations.
* Electrical interface specifications.

### 3.3 mechanical/

Documents the chassis, enclosure, wheels, delivery compartment, sensor mounts, and docking structure.

**Input:**

* Component dimensions.
* Payload requirements.
* Corridor and doorway measurements.
* Wheel and motor specifications.
* Battery and enclosure requirements.

**Output:**

* CAD models.
* Assembly drawings.
* Overall dimensions.
* Mounting interfaces.
* Material and fabrication specifications.

## 4. System Hardware Interfaces

### Onboard Computer

A Raspberry Pi or another selected Linux-capable computer runs ROS 2 and high-level robot software.

Input: Sensor data, mission requests, and operator commands.

Output: Navigation decisions, high-level motion commands, mission status, and system information.

### STM32 Microcontroller

The STM32 executes low-level control and local safety logic.

Input: Validated commands, encoder feedback, local sensors, and safety signals.

Output: Motor-control signals, sensor measurements, fault states, and communication messages.

### Sensors

Sensors provide environmental or internal-state measurements.

Input: Physical conditions such as distance, motion, orientation, or battery state.

Output: Measurements with documented units, timestamps where available, and validity information.

### Motors and Drivers

Motor drivers convert control signals and electrical power into motor actuation.

Input: Validated speed or direction commands and the required motor supply.

Output: Physical movement. Encoder feedback, if available, provides measurements of wheel rotation.

## 5. Required Engineering Documentation

Every selected component should have:

* Manufacturer and part number.
* Operating voltage and current.
* Electrical and communication interfaces.
* Physical dimensions and mounting requirements.
* Datasheet reference.
* Validation status.
* Known limitations.

## 6. Integration Responsibilities

* Hardware and Firmware teams agree on pin assignments, electrical levels, and peripheral interfaces.
* Hardware and ROS 2 teams agree on sensor placement, robot dimensions, and wheel geometry.
* Hardware and Mechanical teams agree on mounting, cable routing, cooling, and service access.
* Hardware and Testing teams define measurable verification procedures.

## 7. Validation

Before full assembly:

1. Verify component compatibility.
2. Check power requirements and protection.
3. Validate individual electronic modules.
4. Check mechanical fit and stability.
5. Confirm all interfaces against the relevant documentation.

## 8. Definition of Done

The hardware subsystem is ready for integration when the selected components are documented, the mechanical and electrical interfaces are agreed upon, critical requirements have been verified, and unresolved issues are recorded.

## 9. Important Note

Do not treat proposed component selections as final until they have been approved by the project team and checked against availability, budget, electrical compatibility, and actual project requirements.
