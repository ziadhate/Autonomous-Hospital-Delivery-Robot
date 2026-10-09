# STM32 Public Headers

## Purpose

This directory contains header files that declare public interfaces, shared data types, configuration options, and module contracts.

## Responsibilities

* Declare public functions and types.
* Define shared enumerations and status codes.
* Expose only the interfaces needed by other modules.
* Document units, valid ranges, and error conditions.
* Prevent circular dependencies between modules.

## Header Guidelines

* Use include guards or `#pragma once` according to project conventions.
* Include only the dependencies required by the header.
* Use fixed-width integer types where appropriate.
* Avoid defining global variables in headers.
* Use `extern` declarations when a shared global is necessary.
* Document ownership and concurrency rules for shared data.
* Keep implementation details in source files whenever possible.

## Inputs

Module design requirements and dependencies.

## Outputs

Stable declarations used by the firmware implementation and other modules.

## Validation

Check that headers compile independently where practical and that multiple inclusions do not create redefinition errors.
