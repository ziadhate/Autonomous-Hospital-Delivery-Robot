# Bill of Materials (BOM)

## Purpose

This directory documents the components required to build the robot prototype and compares available suppliers.

## Files

### `components.md`

**Purpose:** Master list of proposed and selected hardware components.

**Expected inputs:**

* System requirements.
* Component datasheets.
* Required voltage, current, interface, and performance.
* Quantity estimates and project budget.

**Expected outputs:**

* Component name and role.
* Manufacturer and model.
* Quantity.
* Key specifications.
* Estimated unit and total cost.
* Selection status: Proposed, Under Review, Selected, or Rejected.
* Compatibility notes and known risks.

### `suppliers.md`

**Purpose:** Track potential suppliers and purchase options.

**Expected inputs:**

* Component model or acceptable alternative.
* Supplier quotations, links, availability, and shipping information.

**Expected outputs:**

* Supplier name and contact or product link.
* Price and availability date.
* Delivery estimate, warranty, and relevant purchase conditions.
* Comparison between alternative sources.

## Suggested Component Categories

* High-level computer and storage.
* STM32 development board or custom PCB.
* LiDAR and other sensors.
* Motors, encoders, and motor drivers.
* Battery, BMS, fuses, and DC-DC converters.
* CAN interface and communication components.
* Emergency-stop and safety components.
* Chassis, wheels, compartment, fasteners, and fabrication materials.
* Optional display and accessories.

## Rules

* Do not mark a component as selected until its specifications and compatibility are reviewed.
* Separate confirmed prices from estimates.
* Record alternatives when a component is unavailable.
* Avoid duplicate entries for the same component.

## Acceptance Criteria

Every core component has a defined role, documented specifications, a realistic quantity, and a price estimate or an explicit TBD status.
