# Project Assets

## 1. Overview

The `assets/` directory stores visual and multimedia resources used to explain, document, design, demonstrate, and present the Autonomous Hospital Delivery Robot.

Assets support engineering documentation, team communication, project reviews, demonstrations, and the final graduation project presentation.

This directory is intended for reference materials and presentation resources. Executable source code and authoritative engineering specifications should remain in their respective directories.

## 2. Directory Structure

```text
assets/
├── diagrams/
│   ├── architecture/
│   ├── flowcharts/
│   └── wiring/
├── images/
│   ├── hardware/
│   ├── hospital/
│   ├── progress/
│   └── robot/
├── logos/
└── videos/
```

## 3. Directory Responsibilities

### `diagrams/`

Contains diagrams that explain the system's structure, behavior, and connections.

#### `diagrams/architecture/`

Stores system and software architecture diagrams.

Examples:

* High-level system architecture.
* Hardware/software interaction.
* ROS 2 and firmware communication.
* Subsystem dependency diagrams.

**Input:** Architecture definitions and engineering decisions.

**Output:** Visual representations of system components and their relationships.

The corresponding technical descriptions should also be maintained in `docs/architecture/`.

#### `diagrams/flowcharts/`

Stores process and workflow diagrams.

Examples:

* Delivery mission workflow.
* Robot startup and initialization.
* Mission states and transitions.
* Fault handling and recovery.
* Package authorization workflow.

**Input:** Requirements, state definitions, and process descriptions.

**Output:** Flowcharts that explain system behavior.

#### `diagrams/wiring/`

Stores visual representations of electrical connections.

Examples:

* Power distribution.
* Sensor connections.
* Motor-driver connections.
* Communication interfaces.
* Emergency-stop wiring.

**Input:** Approved electrical designs and pin assignments.

**Output:** Wiring diagrams for implementation and review.

The latest approved electrical drawings must be clearly identified. Images should not replace the authoritative engineering design files.

### `images/`

Contains project-related images organized by subject.

#### `images/hardware/`

Contains photographs of electronic components, development boards, sensors, motors, and hardware assemblies.

#### `images/hospital/`

Contains approved reference images of hospital-like environments, corridors, rooms, and layouts used for planning or presentation.

#### `images/progress/`

Contains dated project progress photographs, prototype milestones, assembly updates, and test-session evidence.

#### `images/robot/`

Contains robot concept images, renderings, prototype photographs, and exterior-design references.

**Input:** Approved photographs, renderings, and reference images.

**Output:** Organized visual documentation for engineering reviews and presentations.

### `logos/`

Contains project branding resources.

Possible assets include:

* Project logo.
* Team logo.
* Approved partner logos.
* Presentation-ready logo variants.

Third-party logos must only be used when permitted. Do not imply sponsorship or partnership without authorization.

### `videos/`

Contains approved videos demonstrating the robot, simulations, subsystem tests, and project progress.

Examples:

* Simulation demonstrations.
* Navigation tests.
* Hardware testing.
* Prototype assembly.
* Final project demonstration.

**Input:** Recorded or rendered video files.

**Output:** Demonstration material for reviews and presentations.

## 4. Naming Conventions

Use descriptive names that identify the subject and purpose.

Examples:

```text
system_architecture_v1.png
motor_driver_wiring_v2.png
robot_prototype_2026-11-10.jpg
navigation_test_corridor_01.mp4
```

Recommended practices:

* Use lowercase names and underscores.
* Include dates for progress photographs when useful.
* Include a version number for revised diagrams.
* Avoid names such as `final_final2.png`.
* Record the source of external reference images where applicable.

## 5. File Management

* Prefer compressed formats for large images and videos.
* Avoid committing unnecessarily large media files.
* Use Git LFS or approved external storage when required.
* Do not store credentials, private data, or unauthorized patient information.
* Do not use images of real patients or confidential hospital areas without appropriate authorization.
* Keep editable source files when they are needed to maintain diagrams or designs.

## 6. Relationship with Other Directories

* `docs/` contains written engineering documentation.
* `hardware/` contains hardware designs and technical specifications.
* `ros2/` and `simulation/` contain software and simulation resources.
* `assets/` contains visual and multimedia resources used by these areas.

## 7. Completion Criteria

Each asset should have a clear purpose, descriptive filename, appropriate format, and any required source or usage information.
