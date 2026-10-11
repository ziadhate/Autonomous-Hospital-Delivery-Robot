# ROS 2 Development Roadmap — Hospital Delivery Robot
## Note:to put Checkmark put X in the bracket
## Phase 00 — Project Audit & Architecture

- [ ] Confirm ROS 2 distribution and Ubuntu version
- [ ] Audit the existing ROS 2 workspace and packages
- [ ] Review package dependencies and interfaces
- [ ] Define ROS 2 node responsibilities
- [ ] Define topic, service, and action interfaces
- [ ] Define coordinate frames and TF tree
- [ ] Define coding standards and testing strategy

**Acceptance Criteria:** All packages and node responsibilities are documented, with no unresolved architectural conflicts.

## Phase 01 — Workspace & Package Build System

- [ ] Verify the workspace structure
- [ ] Configure the root workspace build
- [ ] Verify every package.xml
- [ ] Verify every CMakeLists.txt
- [ ] Declare package dependencies correctly
- [ ] Build all packages using colcon
- [ ] Resolve build and dependency errors

**Acceptance Criteria:** All packages build successfully using `colcon build`.

## Phase 02 — Robot Description & TF

- [ ] Complete the robot URDF/Xacro description
- [ ] Define the robot base, wheels, sensors, head, and fixed arms
- [ ] Add and validate required meshes
- [ ] Define sensor mounting positions
- [ ] Configure robot_description package
- [ ] Configure the TF tree
- [ ] Validate the model in RViz
- [ ] Validate the model in simulation

**Main Location:** `src/robot_description/`

**Acceptance Criteria:** The robot model loads correctly, and all links and transforms are valid.

## Phase 03 — Robot Configuration

- [ ] Define common robot parameters
- [ ] Configure sensor topics and frames
- [ ] Configure Nav2 parameters
- [ ] Configure SLAM parameters
- [ ] Configure localization parameters
- [ ] Validate YAML syntax and parameter names
- [ ] Document every configuration file

**Main Location:** `config/`

**Acceptance Criteria:** Configuration files load successfully, with consistent topic names and frame IDs.

## Phase 04 — Sensor Integration & Perception

- [ ] Define sensor interfaces and topic names
- [ ] Integrate LiDAR data
- [ ] Integrate camera data
- [ ] Integrate IMU data
- [ ] Implement the perception node
- [ ] Implement obstacle detection
- [ ] Implement person detection
- [ ] Validate detection outputs
- [ ] Test perception with recorded or simulated sensor data

**Main Location:** `src/perception/`

**Acceptance Criteria:** Sensor data is received correctly, and perception outputs are published using documented message types.

## Phase 05 — SLAM & Mapping

- [ ] Configure the SLAM package
- [ ] Configure SLAM parameters
- [ ] Create the SLAM launch file
- [ ] Verify sensor topics and TF requirements
- [ ] Test mapping in simulation
- [ ] Generate a test map
- [ ] Save maps in the maps directory
- [ ] Document the mapping procedure

**Main Locations:** `src/slam/`, `config/slam_params.yaml`, `launch/slam.launch.py`, `maps/`

**Acceptance Criteria:** The robot can generate and save a usable map in the supported test environment.

## Phase 06 — Localization

- [ ] Configure the localization package
- [ ] Define the map, odom, and base frame relationships
- [ ] Configure localization parameters
- [ ] Configure initial pose handling
- [ ] Validate localization against a saved map
- [ ] Test recovery from localization loss

**Main Locations:** `src/localization/`, `config/localization_params.yaml`

**Acceptance Criteria:** The robot estimates its pose consistently on a saved map under the tested conditions.

## Phase 07 — Autonomous Navigation

- [ ] Configure the navigation package
- [ ] Integrate Nav2
- [ ] Configure global and local costmaps
- [ ] Configure planner and controller plugins
- [ ] Configure obstacle layers
- [ ] Create the navigation launch file
- [ ] Test goal-based navigation
- [ ] Test obstacle avoidance
- [ ] Test navigation recovery behaviors

**Main Locations:** `src/navigation/`, `config/nav2_params.yaml`, `launch/navigation.launch.py`

**Acceptance Criteria:** The robot can navigate to a target pose in simulation while respecting configured obstacles and safety limits.

## Phase 08 — STM32 CAN Bridge

- [ ] Define the CAN message protocol with the firmware team
- [ ] Document message IDs, payloads, units, and update rates
- [ ] Implement CAN protocol encoding and decoding
- [ ] Implement the CAN bridge node
- [ ] Configure the CAN interface
- [ ] Publish robot status and telemetry to ROS 2
- [ ] Forward supported motion commands to the MCU
- [ ] Handle timeouts and communication failures
- [ ] Test invalid messages and disconnected CAN scenarios

**Main Location:** `src/can_bridge/`

**Acceptance Criteria:** ROS 2 and STM32 exchange validated messages, and communication failures are detected safely.

## Phase 09 — Mission Manager & Delivery Workflow

- [ ] Define mission states and transitions
- [ ] Implement the mission manager node
- [ ] Implement the delivery manager
- [ ] Implement the mission state machine
- [ ] Define pickup and delivery locations
- [ ] Integrate navigation goals with mission execution
- [ ] Handle mission cancellation and failure
- [ ] Handle low battery and emergency-stop states
- [ ] Test successful and failed delivery scenarios

**Main Location:** `src/mission_manager/`

**Acceptance Criteria:** Delivery missions follow documented state transitions and handle failures without continuing unsafely.

## Phase 10 — Dashboard Interface

- [ ] Define dashboard-to-ROS communication requirements
- [ ] Define robot status and telemetry interfaces
- [ ] Implement the dashboard interface node
- [ ] Publish battery, mission, and robot status
- [ ] Receive supported mission commands
- [ ] Validate incoming commands
- [ ] Handle dashboard disconnection
- [ ] Test status updates and command handling

**Main Location:** `src/dashboard_interface/`

**Acceptance Criteria:** The dashboard can monitor robot status and send only supported, validated commands.

## Phase 11 — Elevator Interface

- [ ] Define the elevator integration scope
- [ ] Document the simulated or authorized elevator interface
- [ ] Define elevator request and status messages
- [ ] Implement the elevator interface node
- [ ] Define request, waiting, entry, exit, and failure states
- [ ] Integrate elevator states with the mission manager
- [ ] Test timeout and unavailable-elevator scenarios

**Main Location:** `src/elevator_interface/`

**Acceptance Criteria:** Elevator workflows operate in the simulation or approved test interface, with explicit handling of failures.

## Phase 12 — Bringup & Launch Integration

- [ ] Implement the robot bringup launch file
- [ ] Integrate robot description and TF
- [ ] Integrate sensor drivers or simulation sources
- [ ] Integrate perception, localization, and navigation
- [ ] Integrate CAN bridge and mission manager
- [ ] Add launch arguments and configuration paths
- [ ] Verify startup order and lifecycle behavior where applicable
- [ ] Verify clean shutdown and error reporting

**Main Locations:** `src/robot_bringup/`, `launch/robot_bringup.launch.py`

**Acceptance Criteria:** The required robot stack starts from the documented bringup command without missing dependencies or conflicting nodes.

## Phase 13 — Simulation Integration

- [ ] Configure the simulation launch file
- [ ] Load the robot model into the simulator
- [ ] Verify simulated sensor data
- [ ] Verify simulated motion and odometry
- [ ] Test SLAM and localization
- [ ] Test autonomous navigation
- [ ] Test complete delivery missions
- [ ] Test obstacle, communication, and mission failures

**Main Location:** `launch/simulation.launch.py`

**Acceptance Criteria:** A complete delivery scenario can be demonstrated in simulation with repeatable results.

## Phase 14 — Testing, Documentation & Release

- [ ] Add unit tests for protocol and state-machine logic
- [ ] Add integration tests for critical node interfaces
- [ ] Run ROS 2 package tests
- [ ] Validate launch files and YAML configurations
- [ ] Document topics, services, actions, and frame IDs
- [ ] Document installation and build commands
- [ ] Document simulation and navigation procedures
- [ ] Record known limitations and unresolved issues
- [ ] Tag a tested release

**Acceptance Criteria:** The ROS 2 stack builds, launches, and passes the documented tests in the supported environment.

---

## Global Development Rules

- [ ] Keep package responsibilities clearly separated
- [ ] Document every topic, service, action, and message contract
- [ ] Use consistent ROS naming conventions
- [ ] Validate parameters and external commands
- [ ] Avoid hard-coded machine-specific paths
- [ ] Keep safety-critical motor behavior in the STM32 firmware
- [ ] Treat emergency-stop handling as a safety requirement, not just a navigation feature
- [ ] Update this checklist when implementation status changes
