# Bootloader

## 1. Purpose

This directory is reserved for an optional bootloader that can start the application firmware and may support firmware updates.

A bootloader is not required for the first working prototype unless the team decides that field updates or recovery from failed updates are necessary.

## 2. Responsibilities

If implemented, the bootloader may:

* Validate the application image before execution.
* Check image boundaries and integrity.
* Transfer control to a valid application.
* Provide a documented firmware-update mechanism.
* Recover safely from an interrupted update when supported.

## 3. Inputs

* Application firmware image.
* Image metadata and integrity information.
* Boot configuration and update requests, if supported.

## 4. Outputs

* Transfer of control to the application.
* Diagnostic status.
* Update or validation failure information.

## 5. Design Requirements

* Define the flash memory layout before implementation.
* Protect the bootloader and reserved flash regions.
* Validate image length and destination addresses.
* Define behavior when the application image is invalid.
* Document recovery limitations and update procedures.
* Do not claim cryptographic authenticity unless signature verification is implemented.

## 6. Testing

Test valid images, corrupted images, invalid image sizes, interrupted updates, and recovery behavior when those features are implemented.

## 7. Current Status

Bootloader implementation is optional and remains subject to the project schedule and firmware-update requirements.
