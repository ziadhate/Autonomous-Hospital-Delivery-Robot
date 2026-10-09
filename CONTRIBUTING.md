# Contributing Guidelines

## Purpose

This document defines how team members should contribute to the Autonomous Hospital Delivery Robot project.

## Before Starting Work

1. Read the root `README.md`.
2. Read the documentation for your assigned subsystem.
3. Review the relevant requirements and architecture.
4. Confirm dependencies and interfaces with connected teams.
5. Agree on the task, owner, reviewer, and acceptance criteria.

## Coding Rules

* Use meaningful file, function, variable, and type names.
* Keep modules focused on one responsibility.
* Document public functions and important assumptions.
* Handle errors and invalid inputs explicitly.
* Avoid unexplained constants; use named configuration values.
* Do not assume that hardware or interfaces are finalized unless documented.

## Interface Rules

Before integrating modules, document:

* Input and output data types.
* Units and valid ranges.
* Message formats and update rates.
* Timeouts and error conditions.
* Ownership of shared resources.
* Safe behavior when communication fails.

## Testing

Each contribution should include suitable tests or a documented manual test procedure. Do not mark a feature as complete until its acceptance criteria have been checked.

## Git Workflow

1. Pull the latest changes from the shared branch.
2. Create a descriptive branch for your task.
3. Make focused commits.
4. Run applicable checks.
5. Push your branch and open a pull request if the team uses code review.
6. Explain what changed and how it was tested.

## Security and Privacy

Never commit passwords, access tokens, private keys, credentials, or identifiable patient information.

## Documentation

Update the relevant README, design documents, and interface documentation whenever behavior or requirements change.
