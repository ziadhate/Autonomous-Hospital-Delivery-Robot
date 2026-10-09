# Robot Simulation Environment

## 1. Overview

The `simulation/` directory contains resources used to simulate the Autonomous Hospital Delivery Robot before or alongside physical hardware testing.

Simulation supports early development of navigation, localization, perception integration, mission management, and robot visualization.

Simulation results are useful for development but do not by themselves prove that the physical robot will behave identically.

## 2. Directory Structure

```text
simulation/
├── README.md
├── config/
│   └── simulation.yaml
├── gazebo/
│   ├── models/
│   ├── plugins/
│   └── worlds/
├── models/
│   └── robot/
├── rviz/
│   └── robot.rviz
└── worlds/
    └── hospital.world
```

## 3. `config/`

### `config/simulation.yaml`

Stores shared simulation settings.

Depending on the selected simulator and integration, settings may include:

* Simulation time.
* Robot model references.
* Sensor parameters.
* Physics settings.
* Initial robot pose.
* Environment configuration.

**Input:** Simulation requirements and compatible parameter definitions.

**Output:** Configuration values used by the simulation launch workflow.

Only parameters actually supported by the loading code should be included.

## 4. `gazebo/`

Contains Gazebo-related simulation resources.

### `gazebo/models/`

Stores reusable simulation models, including objects, sensors, or environment elements.

**Input:** Model descriptions, geometry, and simulation parameters.

**Output:** Reusable entities that can be placed in simulation worlds.

### `gazebo/plugins/`

Contains custom simulator plugins if the project requires them.

Plugins may provide specialized simulated behavior or interfaces between the simulator and ROS 2.

**Input:** Simulator events and configured plugin parameters.

**Output:** Simulated sensor data, behavior, or interface events as defined by the plugin.

### `gazebo/worlds/`

Contains Gazebo world files.

**Input:** World geometry, models, physics settings, and environmental configuration.

**Output:** A simulated environment.

## 5. `models/robot/`

Contains the robot model resources used by the simulation workflow.

These resources should agree with the physical robot's geometry, wheel configuration, sensor placement, and coordinate frames.

**Input:** Robot CAD or model resources and validated dimensions.

**Output:** Robot model resources used by the selected simulator or ROS 2 integration.

The model may reference files from `ros2/src/robot_description/`; the relationship must be documented to avoid maintaining conflicting robot models.

## 6. `rviz/`

### `rviz/robot.rviz`

Contains RViz visualization settings.

Depending on the configuration, it may display:

* Robot model.
* Coordinate frames.
* Lidar scans.
* Camera data.
* Map and localization estimates.
* Navigation goals and paths.
* Perception results.

**Input:** Available ROS 2 topics, frames, and visualization resources.

**Output:** A configured RViz view for development and debugging.

RViz is a visualization tool; it is not the physics simulator or the robot's motor controller.

## 7. `worlds/`

### `worlds/hospital.world`

Defines the hospital-like environment used by the simulation workflow.

The world may represent corridors, rooms, doors, walls, and obstacles relevant to the prototype.

**Input:** Environment geometry and supported world-format resources.

**Output:** A simulated environment for navigation and mission testing.

The simulated dimensions should be based on documented design assumptions or measured prototype requirements where possible.

## 8. Simulation Workflow

1. Load the robot model.
2. Load the hospital world.
3. Start the selected simulator.
4. Start the required ROS 2 interfaces.
5. Verify sensor data and coordinate frames.
6. Run localization or SLAM.
7. Execute navigation and delivery missions.
8. Record failures, observations, and relevant measurements.

## 9. Validation Scenarios

Suggested scenarios include:

* Robot startup and initialization.
* Navigation through a corridor.
* Goal reaching and mission completion.
* Static obstacle avoidance.
* Person or moving-obstacle scenarios where supported.
* Narrow passages and turning constraints.
* Sensor failure or missing-data handling.
* Communication loss between ROS 2 and firmware interfaces.
* Mission cancellation and recovery.

## 10. Limitations

* Simulated physics may differ from the real robot.
* Sensor models may not reproduce real-world noise.
* Simulated obstacles may not represent all real objects.
* Network timing and hardware failures may differ.
* A successful simulation is not a substitute for controlled physical testing.

## 11. Completion Criteria

The simulation environment is ready for development when the robot model loads correctly, the world starts, sensor and frame interfaces are valid, and documented test scenarios can be executed reproducibly.
