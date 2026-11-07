# AI Module: Phase 00 Audit & Requirements

> Status: Draft for team review.
> Items marked (Proposed) are working assumptions pending team confirmation.

## 1. Current State (Audit)

Source: `git ls-files ai`, saved in `docs/ai/current_structure.txt`.

| Path | Status | Notes |
|------|--------|-------|
| ai/README.md | ✅ | Defines subsystem design and responsibilities |
| ai/roadmap.md | ✅ | Phase checklist; not mentioned in README |
| ai/datasets/README.md | ? | |
| ai/models/README.md | ? | |
| ai/object_detection/preprocessing.py | 🟡 | Empty placeholder |
| ai/object_detection/detector.py | 🟡 | Empty placeholder |
| ai/object_detection/postprocessing.py | 🟡 | Empty placeholder |
| ai/inference/inference.py | 🟡 | Empty placeholder |
| ai/inference/detector.py | 🟡 | Empty placeholder |
| ai/training/train.py | 🟡 | Empty placeholder |
| ai/training/evaluate.py | 🟡 | Empty placeholder |
| ai/training/requirements.txt | 🟡 | Empty placeholder |

**Findings:**
- No AI code is implemented yet; only design documents exist.
- Two files are named `detector.py` (`object_detection/` and `inference/`).
  Proposed separation: reusable detection logic vs. inference adapter.
- `ai/roadmap.md` is not described in `ai/README.md`.


## 2. Scope & Responsibilities

### The AI module is responsible for
- Receiving images or frames from an approved source.
- Detecting relevant objects and producing class, confidence, and bounding box.
- QR/barcode detection (Time Plan, Phase 3). Purpose to be confirmed
  (e.g. mission or delivery verification).
- Exposing detections to the ROS 2 perception layer in an agreed format,
  so AI perception can be connected with navigation (Time Plan, Phase 5).
- Supporting FR-04 (obstacle handling) as an additional perception source.
- Providing offline training and evaluation workflows.

### The AI module is NOT responsible for
- Emergency stopping. Safety is handled independently (NFR-01, UC-05).
- Navigation and path planning (Nav2).
- Low-level motor control (STM32).
- Medical diagnosis (the project is a proof of concept, not a medical device).
- Identifying individuals (no face recognition) (Proposed).

### Constraints
- NFR-05: no private or identifiable hospital/patient data may be collected
  without authorization. Dataset images must come from public datasets,
  simulation (Gazebo), or consenting team members.
- AI predictions must never be the only mechanism for stopping the robot.

## 3. Detection Classes

| ID | Class | Source | Status |
|----|-------|--------|--------|
| 0 | person | UC-01, UC-03 (staff, recipients), FR-04 | Proposed |
| 1 | wheelchair | Hospital corridor scenario | Proposed |
| 2 | stretcher | Hospital corridor scenario | Proposed |
| 3 | cart | Hospital corridor scenario | Proposed |
| 4 | door | Navigation landmark | Proposed |

Notes:
- QR/barcode detection is listed separately (Section 2); it is not an object class.
- Class IDs are frozen once dataset labeling starts (Phase 01).
- Final supported classes depend on the selected model and validated dataset.

## 4. Input Sources

| Source | Purpose | Details |
|--------|---------|---------|
| Raspberry Pi Camera Module 3 (CSI) | Primary live camera | Per Expected Expenses (Computer Vision) |
| Wide-angle USB camera | Optional second camera | "If required by the final design" |
| Image files | Testing and evaluation | JPG / PNG |
| Video files | Offline testing and demos | MP4 |
| Gazebo simulation | Test and dataset images | Planned in Time Plan, Phase 2 |

Camera placement: head-mounted (head shell holds the display and camera).
A pan-tilt servo is optional, so the camera frame may move relative to the robot.

Open details (TBD): resolution, FPS, color order (RGB/BGR), mounting height,
fixed vs. pan-tilt, which camera is the primary one for AI.

## 5. Expected Model Outputs

Each detection contains:

| Field | Type | Description |
|-------|------|-------------|
| class_id | int | ID from Section 3 |
| class_name | string | Human-readable label |
| confidence | float (0 to 1) | Model confidence |
| bbox | 4 values | Bounding box |

Conventions (Proposed):
- Bounding box in pixels: x_min, y_min, x_max, y_max.
- Origin at the top-left corner of the original input image.
- Initial confidence threshold: 0.5, to be tuned on validation data.
- Duplicate detections filtered with non-maximum suppression (NMS).
- Each result keeps the timestamp of the source image.

## 6. Target Hardware & Runtime Constraints

| Item | Value | Source | Status |
|------|-------|--------|--------|
| Onboard computer | Raspberry Pi 4 Model B, 8GB RAM | Expected Expenses | Proposed |
| Storage | 128GB microSD | Expected Expenses | Proposed |
| Accelerator | None listed; assume CPU-only | Expected Expenses | TBD |
| Camera | Raspberry Pi Camera Module 3 (CSI) | Expected Expenses | Proposed |
| OS / middleware | Linux, ROS 2 (distro: TBD), Nav2, SLAM | system-specifications.md | Preliminary |
| AI language | Python | system-specifications.md | Preliminary |
| Shared load | Pi also runs ROS 2, Nav2, SLAM, mission software | Expected Expenses, system-specifications.md | Preliminary |
| Cooling | Fan and heatsink planned | Expected Expenses | Proposed |
| Min FPS / max latency | TBD, derived from max robot speed after measurement | not defined | TBD |
| STM32 | Low-level control and safety only; not used for AI | FR-07, UC-05 | Proposed |

Rules:
- The proposal states AI inference runs on the Pi "where feasible".
  The model is not assumed real-time capable until benchmarked on the Pi 4.
- Sources: Graduation Project Proposal (Time Plan, Expected Expenses) and
  docs/project-overview/system-specifications.md.

## 7. AI <-> ROS 2 Interface (Proposed)

| Direction | Topic | Message type | Notes |
|-----------|-------|--------------|-------|
| Input | /camera/image_raw | sensor_msgs/msg/Image | Name and encoding TBD |
| Output | /ai/detections | vision_msgs/msg/Detection2DArray | Class, confidence, bbox |
| Output (optional) | /ai/status | status message | Model loaded, errors |

Details:
- Detections keep the header (timestamp, frame_id) of the source image.
- Model path, threshold, and input size are ROS 2 parameters, not hard-coded.
- If the model fails, the node publishes an error status (NFR-04).
- No detections does NOT mean the path is clear; consumers must not treat
  an empty result as a safety guarantee.
- How detections are consumed (e.g. Nav2 costmap vs. information only): TBD.
- Time Plan, Phase 5 states AI perception will be connected with navigation.
  How (Nav2 costmap vs. information only): TBD.
- If the camera is mounted on a pan-tilt head, detections need the camera
  frame_id and a TF transform to the robot base frame: TBD with ROS 2 team.
- A CSI camera needs a ROS 2 camera driver compatible with the chosen
  OS and ROS 2 distro: TBD with ROS 2 team.

## 8. Open Questions

| # | Question | Owner | Answer |
|---|----------|-------|--------|
| 1 | Camera resolution and FPS; is Camera Module 3 the primary AI camera, or the USB one? | Hardware | |
| 2 | Camera mounting height; fixed or on a pan-tilt head? | Hardware / Mechanical | |
| 3 | Confirm no AI accelerator will be added (CPU-only on Pi 4, 8GB) | Hardware | |
| 4 | ROS 2 distro, Linux version, and CSI camera driver | ROS 2 | |
| 5 | Camera topic name and image encoding | ROS 2 | |
| 6 | Detections topic name and message type | ROS 2 | |
| 7 | How are detections used by navigation (Nav2 costmap vs. information only)? | ROS 2 | |
| 8 | What is QR/barcode detection used for? | Team | |
| 9 | Final list of object classes | Team | |
| 10 | Maximum robot speed (to derive required FPS and latency) | Team | |

