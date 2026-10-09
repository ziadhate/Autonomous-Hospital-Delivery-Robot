# Project Releases

## 1. Overview

The `releases/` directory documents stable project milestones and release artifacts for the Autonomous Hospital Delivery Robot.

A release represents a specific, identifiable state of the project. It should be possible to determine which source revision, configuration, and test results correspond to that release.

## 2. Responsibilities

* Document release versions.
* Identify included features and limitations.
* Record important fixes and known issues.
* Link to release artifacts.
* Record build and test information.
* Explain installation or demonstration procedures when applicable.

## 3. Suggested Release Structure

```text
releases/
├── README.md
└── release-notes/
```

The `release-notes/` directory is optional and should be created only when individual release documents are needed.

## 4. Versioning

Use a consistent version format, such as:

```text
MAJOR.MINOR.PATCH
```

A versioning policy may follow these general rules:

* **MAJOR:** A release with significant compatibility or architectural changes.
* **MINOR:** A release that adds backward-compatible functionality.
* **PATCH:** A release containing backward-compatible fixes.

The team should document the policy and apply it consistently.

## 5. Release Contents

Each release should identify, where applicable:

* Version number.
* Release date.
* Source revision or Git tag.
* Summary of changes.
* Added features.
* Bug fixes.
* Known limitations.
* Build environment and dependencies.
* Test results.
* Required hardware.
* Installation or execution instructions.
* Artifact location and checksum when applicable.

## 6. Release Artifacts

Possible artifacts include:

* Firmware binaries.
* ROS 2 package bundles.
* AI model artifacts.
* Simulation resources.
* Test reports.
* Documentation bundles.
* Demonstration packages.

Only artifacts that have actually been generated and verified should be listed as available.

Large artifacts should be stored using an appropriate release or artifact-storage mechanism rather than unnecessarily increasing the Git repository size.

## 7. Relationship with `CHANGELOG.md`

`CHANGELOG.md` records the project's changes over time.

The release documentation identifies the contents and verification status of a particular version.

The release notes should agree with the relevant changelog entries and Git tag.

## 8. Release Verification

Before publishing a release:

1. Confirm the intended source revision.
2. Run the required build checks.
3. Execute the release test plan.
4. Record known issues.
5. Verify the release artifacts.
6. Update the changelog.
7. Create and verify the version tag when the team is ready to release.

## 9. Completion Criteria

A release is ready to publish when its version, source revision, artifacts, test status, installation instructions, and known limitations are documented accurately.
