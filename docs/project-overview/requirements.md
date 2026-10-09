# System Requirements

## Purpose

This document defines the functional and non-functional requirements of the robot. Requirements must be reviewed and approved by the team before implementation.

## Functional Requirements

* **FR-01 — Mission Creation:** The system shall accept a delivery request from an authorized interface.
* **FR-02 — Mission Validation:** The system shall validate the destination and required mission information.
* **FR-03 — Autonomous Navigation:** The robot shall navigate between configured locations in the supported indoor environment.
* **FR-04 — Obstacle Handling:** The robot shall detect obstacles and respond according to the agreed safety policy.
* **FR-05 — Delivery Tracking:** The system shall record mission state and delivery status.
* **FR-06 — Payload Security:** The delivery compartment shall provide the agreed access-control and verification mechanism.
* **FR-07 — Embedded Control:** The STM32 subsystem shall manage the agreed low-level control functions.
* **FR-08 — Communication:** The high-level computer and STM32 shall exchange defined commands and status messages.
* **FR-09 — Fault Handling:** The system shall detect specified faults and enter an appropriate safe state.
* **FR-10 — Monitoring:** The dashboard shall display mission and robot status.
* **FR-11 — Isolation Workflow:** The system shall demonstrate the agreed isolation-area delivery procedure.
* **FR-12 — Simulation:** The team shall test core workflows in a simulated environment before physical integration.

## Non-Functional Requirements

* **NFR-01 — Safety:** Loss of high-level communication must not leave motor outputs uncontrolled.
* **NFR-02 — Maintainability:** Software shall be divided into documented modules.
* **NFR-03 — Traceability:** Mission events and faults shall be logged where feasible.
* **NFR-04 — Reliability:** Errors and timeouts shall be handled explicitly.
* **NFR-05 — Privacy:** Private or identifiable hospital/patient data shall not be collected without authorization.
* **NFR-06 — Testability:** Major subsystems shall have defined test procedures.

## Requirements Still to Be Determined

* Maximum payload.
* Robot dimensions and turning radius.
* Maximum speed and stopping distance.
* Battery capacity and operating duration.
* Navigation accuracy.
* Sensor ranges and update rates.
* CAN message identifiers and timing.
* Delivery compartment locking method.
* Dashboard user roles and authentication.
* Cleaning workflow and validation method.

## Acceptance Criteria

Each requirement must have an owner, verification method, and pass/fail criterion before it is considered complete.
