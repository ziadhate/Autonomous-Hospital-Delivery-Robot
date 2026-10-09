
# Autonomous AI-Powered Hospital Delivery & Infection-Control Robot
بسم الله الرحمن الرحيم

## 1. Project Overview

This project aims to develop an autonomous mobile robot that transports authorized items between hospital departments, rooms, and designated locations.

The robot is designed to reduce repetitive transportation tasks and unnecessary staff movement, especially during deliveries to designated isolation areas.

The system combines robotics, embedded systems, artificial intelligence, computer vision, and a monitoring dashboard.

**Project Status:** Planning and Requirements Definition

## 2. Main Objectives

* Develop autonomous indoor navigation.
* Build maps of the operating environment using SLAM.
* Detect and avoid obstacles.
* Transport authorized items securely.
* Monitor and track delivery missions.
* Develop a custom lightweight RTOS for the STM32 low-level control subsystem.
* Integrate ROS 2 with the embedded controller through CAN communication.
* Demonstrate an isolation-area delivery and controlled cleaning workflow.
* Develop a simulated multi-floor operation using an elevator prototype or simulation.

## 3. System Architecture

### High-Level Control

**Main Computer:** Raspberry Pi 4 (planned)

Responsibilities:

* Linux operating system.
* ROS 2 middleware.
* SLAM and localization.
* Navigation and path planning.
* AI-based perception.
* Mission management.
* Dashboard communication.

### Low-Level Control

**Microcontroller:** STM32F401RCT6 (planned)

Responsibilities:

* Motor control and PID.
* Wheel encoder processing.
* Sensor interfacing.
* Battery monitoring.
* CAN communication.
* Custom RTOS task scheduling.
* Watchdog and fault handling.
* Emergency-stop monitoring and safety-related control.

### Communication

CAN Bus is the planned communication interface between the Raspberry Pi subsystem and the STM32 controller. The protocol, message identifiers, data formats, and update rates must be defined and tested before integration.

## 4. Planned Technologies

* C and Embedded C
* C++
* Python
* STM32
* Custom lightweight RTOS
* Linux
* ROS 2
* Nav2
* SLAM
* Computer Vision
* CAN Bus
* Simulation tools
* Web dashboard and database

The final versions and dependencies will be selected during the design phase.

## 5. Main Features

* Autonomous indoor navigation.
* Obstacle detection and avoidance.
* Secure delivery compartment.
* Delivery verification and tracking.
* Mission management dashboard.
* Robot status and battery monitoring.
* Isolation-area delivery workflow.
* Controlled cleaning workflow.
* Elevator prototype or simulation.
* Fault detection and safe-stop behavior.
* Charging dock concept.

Features will be considered complete only after implementation and testing.

## 6. Repository Structure

* `docs/`: Requirements, architecture, research, design, and testing documentation.
* `hardware/`: Mechanical design, electronics, wiring, and bill of materials.
* `firmware/`: STM32 application, drivers, custom RTOS, and safety modules.
* `ros2/`: ROS 2 packages, navigation, SLAM, mission management, and communication.
* `ai/`: Dataset documentation, model training, and inference.
* `dashboard/`: Frontend, backend, and database.
* `simulation/`: Simulated robot and hospital environment.
* `tests/`: Unit, integration, hardware, simulation, and system tests.
* `assets/`: Project images, diagrams, and visual materials.
* `releases/`: Release documentation and test evidence.

## 7. Development Workflow

1. Research existing solutions.
2. Collect environmental and operational requirements.
3. Define system interfaces and architecture.
4. Finalize preliminary mechanical and electrical designs.
5. Develop and test software modules.
6. Build the simulation environment.
7. Integrate the hardware and software subsystems.
8. Validate the complete prototype.

## 8. Scope and Limitations

The initial system is a controlled-environment prototype, not a certified medical device. It will not diagnose patients or make clinical decisions. Elevator integration will use a simulation or prototype unless an authorized interface is available. Cleaning demonstrations do not establish medical-grade disinfection.

## 9. Team Collaboration

Each subsystem must have a responsible owner. Teams must agree on interfaces, units, message formats, dependencies, and testing criteria before cross-team integration.

## 10. Current Status

The repository currently provides a planned structure for development. The existence of a source file or configuration file does not mean that the associated functionality has been implemented or validated.

## 11. Documentation Rules

* Update documentation when interfaces or requirements change.
* Record assumptions and unresolved decisions.
* Document code inputs, outputs, dependencies, and error handling.
* Do not commit credentials or private hospital/patient information.
* Do not claim test results without recorded evidence.

## 12. License

The project license and rules for external contributions must be confirmed by the project team before public redistribution.
