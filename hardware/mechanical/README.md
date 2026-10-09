# Mechanical Design

## Purpose

This directory contains the robot's chassis, payload compartment, sensor mounts, wheels, enclosure, docking structure, and fabrication documentation.

## Subdirectories

### `3d-models/`

Contains exported 3D models such as STL or STEP files, depending on the selected CAD workflow.

**Inputs:** Approved CAD parts and assembly models.

**Outputs:** Models for visualization, collision checking, fabrication, and integration.

### `cad/`

Contains editable CAD source files for individual parts and full assemblies.

**Inputs:** Mechanical requirements, component dimensions, payload size, and mounting constraints.

**Outputs:** Editable parts, assemblies, and design revisions.

### `drawings/`

Contains dimensioned technical drawings.

**Inputs:** Reviewed CAD models and manufacturing requirements.

**Outputs:** Dimensions, tolerances where necessary, hole patterns, and assembly views.

### `fabrication/`

Contains fabrication instructions, material lists, cutting files, and manufacturing notes.

**Inputs:** Released drawings, selected materials, and available manufacturing processes.

**Outputs:** Manufacturing-ready files and assembly instructions.

## Main Mechanical Requirements

* Provide stable movement and adequate payload support.
* Protect electronics and battery while allowing maintenance access.
* Mount the LiDAR and other sensors in suitable, unobstructed positions.
* Keep the center of gravity low and account for braking and turning.
* Provide an accessible emergency-stop button.
* Reserve space for wiring, cooling, connectors, and battery replacement.
* Ensure the delivery compartment is accessible and can be secured.
* Treat the head display, voice interface, and decorative arms as optional features until the core robot is validated.

## Inputs

* Component dimensions and masses.
* Payload and compartment requirements.
* Sensor fields of view.
* Wheelbase, motor, and chassis requirements.
* Corridor, doorway, and turning-clearance measurements.

## Outputs

* CAD parts and assemblies.
* Dimensioned drawings.
* Fabrication files.
* Mechanical BOM and assembly instructions.

## Acceptance Criteria

The mechanical design accommodates the confirmed components, payload, wiring, and service access. Dimensions must be verified before fabrication.
