# System Specifications

## Purpose

This document records confirmed and proposed system specifications. Unknown values must remain marked as TBD until measured, calculated, or selected.

## Preliminary Hardware

| Component           | Proposed Selection                       | Status   |
| ------------------- | ---------------------------------------- | -------- |
| High-level computer | Raspberry Pi 4                           | Proposed |
| Embedded controller | STM32F401RCT6                            | Proposed |
| Main communication  | CAN Bus                                  | Proposed |
| Navigation sensor   | RPLIDAR A1M8                             | Proposed |
| Camera              | To be selected                           | TBD      |
| IMU                 | To be selected                           | TBD      |
| Wheel encoders      | Based on selected motors                 | TBD      |
| Motor driver        | Based on motor voltage/current           | TBD      |
| Battery and BMS     | Based on power budget                    | TBD      |
| Display             | Optional HDMI touchscreen                | TBD      |
| Voice output/input  | Speaker and microphone selection pending | TBD      |

## Preliminary Software

* Linux on the high-level computer.
* ROS 2 for robotics middleware and application nodes.
* Nav2 for navigation.
* A suitable SLAM/localization solution.
* STM32 firmware written primarily in C.
* Custom lightweight RTOS for the embedded subsystem.
* C++ for applicable ROS 2 nodes.
* Python for AI development and supporting tools.
* Dashboard technology to be selected.

## Specifications to Finalize

* Robot dimensions and mass.
* Payload capacity.
* Motor torque and speed.
* Wheel diameter and encoder resolution.
* Battery voltage, capacity, and peak current.
* Power consumption and expected runtime.
* Sensor placement and coordinate frames.
* CAN bitrate, identifiers, message formats, and timing.
* Control-loop rates and RTOS priorities.
* Navigation performance targets.
* Display dimensions and mounting.
* Mechanical material and fabrication method.

## Change Control

Every finalized specification must include its source or calculation, responsible owner, date, and revision. Hardware-dependent software must not assume unconfirmed component specifications.
