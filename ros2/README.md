# ROS 2 Robot Software

## 1. Overview

The `ros2/` directory contains the Robot Operating System 2 (ROS 2) software responsible for high-level robot operation.

The ROS 2 subsystem coordinates navigation, localization, perception, delivery missions, robot description, and communication with the STM32 firmware and dashboard.

ROS 2 operates on the robot's high-level computer. The STM32 firmware remains responsible for low-level control and the safety functions assigned to the microcontroller.

## 2. Directory Structure

```text
ros2/
├── README.md
├── config/
├── launch/
├── maps/
└── src/
    ├── can_bridge/
    ├── dashboard_interface/
    ├── elevator_interface/
    ├── localization/
    ├── mission_manager/
    ├── navigation/
    ├── perception/
    ├── robot_bringup/
    ├── robot_description/
    └── slam/
```

## 3. `config/`

Contains shared ROS 2 configuration files.

* `localization_params.yaml`: Parameters for the selected localization implementation.
* `nav2_params.yaml`: Parameters for Nav2 navigation components.
* `robot_params.yaml`: Shared robot configuration, where defined.
* `sensors.yaml`: Sensor-related configuration.
* `slam_params.yaml`: Parameters for the selected SLAM implementation.

**Input:** Robot geometry, sensor specifications, environment assumptions, and selected ROS 2 packages.

**Output:** Configuration values loaded by supported nodes and launch files.

Parameter names must match the actual nodes and versions being used.

## 4. `launch/`

Contains launch files that start and configure multiple ROS 2 components.

* `robot_bringup.launch.py`: Starts the configured robot subsystems.
* `navigation.launch.py`: Starts the navigation workflow.
* `slam.launch.py`: Starts the SLAM workflow.
* `simulation.launch.py`: Starts the configured simulation integration.

**Input:** Launch arguments, YAML configuration, and available ROS 2 packages.

**Output:** A running collection of configured nodes and related processes.

A launch file must not be described as operational until its referenced packages and configuration files have been tested together.

## 5. `maps/`

Stores generated or prepared maps for supported environments.

Depending on the mapping workflow, map resources may include occupancy-grid data and associated metadata.

**Input:** Mapping results or approved map files.

**Output:** Maps consumed by localization and navigation components.

Maps should identify their environment, origin, resolution, and revision when this information is available.

## 6. `src/` — ROS 2 Packages

### `can_bridge/`

Connects the ROS 2 application to the firmware communication interface using the agreed CAN protocol.

* `can_bridge_node.cpp`: ROS 2 node for the bridge workflow.
* `can_protocol.cpp`: Protocol encoding or decoding logic.

**Input:** ROS 2 commands and received communication frames.

**Output:** Encoded messages for the firmware and decoded status for ROS 2.

The bridge protocol must match the message identifiers, payload formats, and timing assumptions documented in the firmware.

### `dashboard_interface/`

Connects dashboard mission requests and status reporting to the ROS 2 system.

* `dashboard_node.cpp`: Implements the node interface.

**Input:** Validated mission requests and application events.

**Output:** ROS 2 commands, mission status, or telemetry updates according to the defined interface.

The transport mechanism and API contract must be documented explicitly.

### `elevator_interface/`

Provides an interface for an elevator workflow if the prototype supports or simulates one.

**Input:** Authorized elevator requests and relevant robot state.

**Output:** Elevator workflow status and interface events.

This package does not imply that the robot can control a real hospital elevator without an approved external interface.

### `localization/`

Contains localization-related configuration and package resources.

**Input:** Supported sensor measurements, map data, and localization parameters.

**Output:** The robot's estimated pose and localization status, depending on the selected implementation.

### `mission_manager/`

Coordinates delivery mission execution.

* `mission_manager.cpp`: Main mission-management logic.
* `delivery_manager.cpp`: Delivery-specific workflow.
* `mission_state_machine.cpp`: Mission state transitions.

**Input:** Mission requests, robot state, destination information, and navigation feedback.

**Output:** Mission actions, state updates, success or failure status, and related events.

The state machine should define valid transitions and behavior when a mission fails, is cancelled, or loses required resources.

### `navigation/`

Contains navigation package resources and configuration.

**Input:** A goal pose, map/localization data, and obstacle information.

**Output:** Navigation actions, feedback, and motion commands through the configured navigation stack.

The selected Nav2 configuration and robot controller must be validated against the robot's actual geometry and motion capabilities.

### `perception/`

Contains perception nodes and their configuration.

* `perception_node.cpp`: Coordinates the perception workflow.
* `obstacle_detector.cpp`: Implements or integrates obstacle-detection logic.
* `person_detector.cpp`: Implements or integrates person-detection logic.

**Input:** Supported camera, lidar, or other sensor data.

**Output:** Detection results or obstacle information in the agreed ROS 2 message format.

If AI inference runs in Python outside these C++ nodes, document the interface used to transfer detection results between processes.

### `robot_bringup/`

Provides resources for starting the robot's required ROS 2 nodes.

**Input:** Launch configuration and subsystem parameters.

**Output:** A coordinated robot startup workflow.

### `robot_description/`

Contains the robot's description resources.

* `urdf/`: Robot description files.
* `meshes/`: Visual or collision mesh resources.
* `rviz/`: RViz configuration files.

**Input:** Robot geometry, joints, sensors, frames, and dimensions.

**Output:** A robot model for visualization and integration with supported ROS 2 tools.

The robot description must agree with the physical prototype.

### `slam/`

Contains configuration and launch resources for Simultaneous Localization and Mapping.

**Input:** Supported sensor data and SLAM parameters.

**Output:** Mapping and localization-related outputs, depending on the selected SLAM implementation.

## 7. Typical System Data Flow

1. Sensors provide measurements to the ROS 2 subsystem.
2. Localization estimates the robot's pose.
3. Perception provides supported obstacle or person-detection information.
4. Mission management selects or updates the current delivery goal.
5. Navigation calculates motion commands.
6. The firmware interface sends appropriate commands to the microcontroller.
7. Firmware status and faults are reported back to ROS 2.
8. The dashboard interface exposes mission progress and robot status.

The exact topics, services, actions, message types, and coordinate frames must be documented as the packages are implemented.

## 8. Integration Requirements

* Use consistent frame names and timestamps.
* Document topic names and message types.
* Define command limits and timeout behavior.
* Handle missing sensors and communication failures.
* Keep emergency-stop behavior independent of ordinary navigation commands.
* Verify the ROS 2 distribution and package dependencies.
* Ensure configuration files match the installed package versions.

## 9. Testing

Test individual nodes, package interfaces, launch files, navigation behavior, localization, mission transitions, and firmware communication. Simulation should be used before hardware testing wherever practical.

## 10. Completion Criteria

The ROS 2 subsystem is ready for integration when packages build, launch configurations work, interfaces are documented, and the mission workflow has passed the defined simulation and hardware tests.
