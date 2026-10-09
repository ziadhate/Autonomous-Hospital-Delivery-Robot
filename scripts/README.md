# Project Automation Scripts

## 1. Overview

The `scripts/` directory contains helper scripts used to automate common development, setup, build, test, and maintenance tasks.

Scripts are intended to make the development workflow more consistent across team members' environments.

A script should document its prerequisites, accepted arguments, generated files, exit behavior, and any changes it makes to the system.

## 2. Directory Structure

```text
scripts/
├── build/
├── setup/
├── test/
└── tools/
```

## 3. `build/`

Contains scripts that build supported project components.

Potential responsibilities:

* Build firmware.
* Build ROS 2 packages.
* Prepare simulation resources.
* Run configured build targets.
* Report build failures.

**Input:** Source code, toolchain configuration, dependencies, and optional build arguments.

**Output:** Build artifacts, build logs, and an exit status.

Build scripts should stop or report clearly when a required command fails.

## 4. `setup/`

Contains scripts that help configure the development environment.

Potential responsibilities:

* Check required tools.
* Install documented development dependencies.
* Create a Python virtual environment.
* Configure environment variables.
* Prepare ROS 2 workspace dependencies.

**Input:** Supported operating system, dependency definitions, and optional configuration.

**Output:** Environment checks, setup actions, and diagnostic messages.

Scripts should not silently overwrite personal configuration or require administrator privileges without explaining why.

## 5. `test/`

Contains helper scripts for running test suites.

Potential responsibilities:

* Run unit tests.
* Execute integration tests.
* Run firmware checks.
* Start ROS 2 tests.
* Collect test results.

**Input:** Test targets, configuration, and available test dependencies.

**Output:** Test reports, logs, and success or failure status.

## 6. `tools/`

Contains general-purpose development utilities that do not fit the build, setup, or test categories.

Potential responsibilities:

* Code formatting checks.
* Documentation validation.
* Repository structure checks.
* Log processing.
* Configuration validation.

**Input:** Source files, documentation, logs, or configuration.

**Output:** Reports, validation results, or explicitly documented generated files.

## 7. Script Documentation Requirements

Every non-trivial script should document:

* Purpose.
* Supported operating systems.
* Required dependencies.
* How to execute it.
* Accepted arguments and environment variables.
* Input files and directories.
* Output files and directories.
* Exit codes or failure behavior.
* Whether it changes files or system configuration.

## 8. Safe Execution

* Review scripts before executing them with elevated privileges.
* Avoid hardcoded credentials and private tokens.
* Avoid destructive default operations.
* Require explicit confirmation for potentially destructive actions.
* Prefer paths relative to the repository when appropriate.
* Report missing dependencies clearly.
* Keep scripts compatible with the environments officially supported by the project.

## 9. Completion Criteria

A script is ready for team use when its purpose and dependencies are documented, its inputs and outputs are clear, and it has been tested on the supported environment.
