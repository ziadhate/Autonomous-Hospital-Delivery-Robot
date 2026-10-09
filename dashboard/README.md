# Robot Dashboard

## 1. Overview

The `dashboard/` directory contains the software for the robot's monitoring and mission-management dashboard.

The dashboard is intended to provide an interface for authorized users to create and monitor delivery missions, inspect robot status, and review mission history.

The dashboard is a supervisory interface. Time-critical motor control and emergency-stop behavior must remain independent of the dashboard and network connection.

## 2. Directory Structure

```text
dashboard/
├── README.md
├── backend/
│   ├── README.md
│   ├── requirements.txt
│   ├── src/
│   └── tests/
├── database/
│   ├── README.md
│   └── schema.sql
└── frontend/
    ├── README.md
    ├── package.json
    ├── public/
    └── src/
```

## 3. Components

### `backend/`

Contains the server-side application.

Responsibilities may include:

* Exposing API endpoints.
* Validating incoming requests.
* Managing missions and mission status.
* Applying authorization rules.
* Communicating with the ROS 2 integration layer.
* Recording events and reporting errors.

**Input:** Frontend API requests, robot-status updates, and mission events.

**Output:** API responses, validated mission commands, status updates, and application logs.

The backend must not assume that a request was executed by the robot simply because the request was accepted.

### `backend/src/`

Contains the backend implementation, organized into modules according to the chosen framework.

Possible responsibilities include:

* API routes.
* Request and response schemas.
* Mission services.
* Authentication and authorization.
* Robot communication adapters.
* Error handling and logging.

The exact file organization should follow the actual implementation.

### `backend/tests/`

Contains automated tests for backend behavior.

**Input:** Test requests, mocked services, and test configuration.

**Output:** Test results showing whether the API and business logic behave as expected.

### `backend/requirements.txt`

Lists Python dependencies required by the backend.

**Input:** Dependency definitions.

**Output:** A reproducible Python dependency installation specification.

### `database/`

Contains the database design and related documentation.

#### `database/schema.sql`

Defines the database schema, such as tables, columns, keys, constraints, and indexes.

Depending on the final design, the database may store:

* Mission records.
* User and role records.
* Mission status history.
* Robot status snapshots.
* Fault and event logs.
* Audit information.

**Input:** SQL schema definitions.

**Output:** Database structures when the script is executed against a compatible database.

The actual database engine, migration process, and access method must be documented before deployment.

### `frontend/`

Contains the user-facing web application.

Responsibilities may include:

* Login and access-controlled views.
* Mission creation and cancellation requests.
* Destination selection.
* Mission status display.
* Battery and connectivity indicators.
* Fault and notification display.
* Mission history.

**Input:** User interactions and backend API responses.

**Output:** API requests and visual information presented to the user.

#### `frontend/src/`

Contains the frontend source code, including components, pages, application state, and API integration.

#### `frontend/public/`

Contains static public resources, such as icons and other assets served by the frontend.

#### `frontend/package.json`

Defines frontend package metadata, dependencies, and available scripts.

The exact development and build commands must be maintained in this file.

## 4. System Data Flow

1. An authorized user submits a mission through the frontend.
2. The frontend sends a request to the backend.
3. The backend validates the request and checks authorization.
4. The backend records or updates the mission according to the defined workflow.
5. The backend forwards the mission to the robot integration layer.
6. The ROS 2 subsystem reports mission progress and robot status.
7. The backend updates the application state and relevant records.
8. The frontend displays the latest known status.

The system must distinguish between a requested, accepted, active, completed, failed, and cancelled mission when these states are supported.

## 5. Inputs and Outputs

| Component     | Input                              | Output                                  |
| ------------- | ---------------------------------- | --------------------------------------- |
| Frontend      | User actions and API responses     | API requests and displayed status       |
| Backend       | API requests and robot events      | Validated responses and mission updates |
| Database      | SQL operations                     | Stored records and query results        |
| ROS 2 adapter | Mission commands and status events | Robot commands and status updates       |

## 6. Reliability and Security

* Validate all API input.
* Protect authenticated endpoints.
* Enforce role-based permissions where required.
* Do not hardcode passwords, API keys, or secret tokens.
* Handle robot disconnection and stale status data.
* Log mission state transitions and relevant faults.
* Do not display stale telemetry as confirmed current status.
* Treat network communication as unreliable.
* Never rely on the dashboard to provide emergency-stop protection.

## 7. Testing

The dashboard should be tested for:

* API request validation.
* Authentication and authorization.
* Mission lifecycle transitions.
* Database operations.
* Invalid or unavailable robot connections.
* Frontend loading, errors, and status updates.
* Unauthorized mission operations.
* Handling of stale or missing telemetry.

## 8. Completion Criteria

The dashboard is ready for integration when the frontend, backend, database, and robot communication interface use documented contracts and the relevant tests pass.
