# Use Cases

## UC-01 — Create a Delivery Mission

**Actor:** Authorized hospital staff member.

**Flow:**

1. The user selects a pickup and destination.
2. The system validates the request.
3. The mission is added to the mission queue.
4. The robot receives the mission when available.
5. The dashboard displays the mission state.

**Failure cases:** Invalid destination, robot unavailable, communication failure, or mission cancellation.

## UC-02 — Autonomous Delivery

**Actor:** Robot system.

**Flow:**

1. The robot receives a validated mission.
2. The navigation subsystem plans a route.
3. The robot travels toward the destination.
4. Obstacles are handled according to the navigation and safety policy.
5. The robot reaches the destination and requests delivery verification.
6. The system records the result.

**Failure cases:** Blocked route, localization failure, low battery, or hardware fault.

## UC-03 — Secure Payload Handover

**Actor:** Authorized recipient.

**Flow:**

1. The robot arrives at the destination.
2. The system identifies the mission and required verification method.
3. The recipient completes the configured verification step.
4. The compartment is unlocked only when the approved conditions are met.
5. The system records the handover result.

The actual locking and authentication method remains to be selected.

## UC-04 — Isolation-Area Delivery

**Actor:** Robot system and authorized staff.

**Flow:**

1. The mission is marked as requiring the isolation workflow.
2. The robot follows the configured route and delivery procedure.
3. Delivery status is recorded.
4. The robot proceeds to the designated controlled cleaning workflow if required.
5. The robot returns to service only after the defined clearance step.

This prototype workflow does not establish medical-grade infection prevention.

## UC-05 — Fault and Safe Stop

**Trigger:** E-stop activation, communication timeout, motor fault, or another defined safety fault.

**Flow:**

1. The fault is detected.
2. The embedded safety logic applies the appropriate safe response.
3. Motion is stopped when required.
4. Fault information is reported when communication is available.
5. Restart requires the defined recovery conditions.

## UC-06 — Robot Monitoring

The dashboard displays the available mission state, robot status, battery information, faults, and event history. Data availability depends on implemented sensors and interfaces.
