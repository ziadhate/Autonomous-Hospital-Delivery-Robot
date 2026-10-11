# AI Development Roadmap — Hospital Delivery Robot

## Phase 00 — AI Module Audit & Requirements

- [ ] Review the existing AI directory structure
- [ ] Define the AI module scope and responsibilities
- [ ] Identify required detection classes
- [ ] Define the input sources: camera, image, or video
- [ ] Define expected model outputs
- [ ] Define the target hardware and runtime constraints
- [ ] Document the interface between AI and ROS 2

**Acceptance Criteria:** AI requirements, detection classes, input formats, and integration interfaces are documented.

## Phase 01 — Dataset Planning & Collection

- [ ] Define the dataset requirements
- [ ] Identify relevant hospital delivery robot scenarios
- [ ] Define object classes and class IDs
- [ ] Collect or select suitable images
- [ ] Include different lighting conditions and viewpoints
- [ ] Label objects using a consistent annotation format
- [ ] Split the dataset into training, validation, and test sets
- [ ] Check for duplicate images and incorrect labels
- [ ] Document dataset sources and licenses
- [ ] Document dataset preparation instructions

**Main Location:** `datasets/`

**Acceptance Criteria:** The dataset has documented classes, annotations, splits, and provenance. Test data remains separate from training.

## Phase 02 — Preprocessing & Postprocessing

- [ ] Implement image preprocessing
- [ ] Define image resizing and normalization
- [ ] Handle color format and input dimensions consistently
- [ ] Implement model-output decoding
- [ ] Implement confidence thresholding
- [ ] Implement non-maximum suppression if required by the model
- [ ] Convert detections to a consistent output format
- [ ] Validate bounding boxes and class IDs
- [ ] Add tests for valid and invalid inputs

**Main Location:** `object_detection/`

**Files:** `preprocessing.py`, `postprocessing.py`

**Acceptance Criteria:** Preprocessing and postprocessing produce consistent, validated outputs for the selected model.

## Phase 03 — Detector Implementation

- [ ] Select the object detection model
- [ ] Document the model architecture and dependencies
- [ ] Implement the detector interface
- [ ] Load model weights and configuration
- [ ] Implement prediction on a single image
- [ ] Implement prediction on a video frame
- [ ] Return class, confidence, and bounding-box information
- [ ] Handle missing weights and invalid inputs
- [ ] Measure inference time and resource usage

**Main Location:** `object_detection/detector.py`

**Acceptance Criteria:** The detector loads the selected model and returns correctly formatted predictions.

## Phase 04 — Training Environment

- [ ] Review the Python dependencies
- [ ] Complete `training/requirements.txt`
- [ ] Document the supported Python and ML framework versions
- [ ] Create an isolated Python environment
- [ ] Verify that the required ML framework installs correctly
- [ ] Verify dataset paths and annotation formats
- [ ] Add configuration for training parameters
- [ ] Document the training command

**Main Location:** `training/`

**Acceptance Criteria:** A clean environment can install the required dependencies and prepare the dataset for training.

## Phase 05 — Model Training

- [ ] Implement the training pipeline
- [ ] Load the training and validation datasets
- [ ] Configure model and training parameters
- [ ] Set random seeds where supported
- [ ] Save training metrics
- [ ] Save model checkpoints
- [ ] Save the best-performing model
- [ ] Record the training configuration
- [ ] Handle interrupted training where supported

**Main File:** `training/train.py`

**Acceptance Criteria:** Training completes on the documented dataset and produces reproducible configuration records and model checkpoints.

## Phase 06 — Model Evaluation

- [ ] Implement the evaluation pipeline
- [ ] Evaluate the model on validation data
- [ ] Evaluate the final model on the separate test set
- [ ] Calculate appropriate detection metrics
- [ ] Record precision and recall
- [ ] Calculate mAP when applicable
- [ ] Inspect false positives and false negatives
- [ ] Review performance for each class
- [ ] Compare candidate models
- [ ] Document limitations and failure cases

**Main File:** `training/evaluate.py`

**Acceptance Criteria:** Evaluation results are recorded, and model selection is based on documented test criteria rather than training loss alone.

## Phase 07 — Inference Pipeline

- [ ] Implement model loading for inference
- [ ] Connect preprocessing to the detector
- [ ] Connect the detector to postprocessing
- [ ] Implement inference on images
- [ ] Implement inference on video or camera frames
- [ ] Add configurable confidence thresholds
- [ ] Handle camera and model errors
- [ ] Measure end-to-end inference latency
- [ ] Validate output consistency

**Main Location:** `inference/`

**Files:** `detector.py`, `inference.py`

**Acceptance Criteria:** The inference pipeline accepts supported inputs and produces validated detections with measured latency.

## Phase 08 — Model Packaging & Versioning

- [ ] Define the supported model format
- [ ] Store model artifacts in the documented location
- [ ] Document model version and training dataset version
- [ ] Record model configuration and class labels
- [ ] Verify model loading from a clean environment
- [ ] Document model licensing and usage restrictions
- [ ] Avoid committing large model files if repository policy prohibits them
- [ ] Define a process for distributing model artifacts

**Main Location:** `models/`

**Acceptance Criteria:** A selected model can be identified, obtained, and loaded using documented instructions.

## Phase 09 — ROS 2 Integration

- [ ] Agree on detection message types with the ROS 2 team
- [ ] Define input camera topics and expected image encoding
- [ ] Define output topic names and detection fields
- [ ] Integrate the inference pipeline with the perception node
- [ ] Publish detections using the agreed interface
- [ ] Handle missing or delayed camera frames
- [ ] Configure inference parameters
- [ ] Test with recorded data and live or simulated camera input
- [ ] Measure end-to-end latency on target hardware

**Acceptance Criteria:** AI detections reach the ROS 2 perception stack using agreed interfaces and documented performance limits.

## Phase 10 — Testing, Optimization & Release

- [ ] Add unit tests for preprocessing and postprocessing
- [ ] Add detector and inference tests
- [ ] Test missing, corrupt, and unsupported inputs
- [ ] Test low-light and difficult viewpoints
- [ ] Measure precision, recall, and inference latency
- [ ] Profile memory and CPU/GPU usage
- [ ] Optimize model size or runtime if necessary
- [ ] Verify behavior on the target computer
- [ ] Document known limitations
- [ ] Publish a versioned AI release

**Acceptance Criteria:** The AI module passes its documented tests and meets agreed accuracy and latency targets on the intended hardware.

---

## Global Development Rules

- [ ] Keep training, evaluation, and inference code separated
- [ ] Keep test data separate from training
- [ ] Avoid hard-coded machine-specific paths
- [ ] Keep class names and class IDs consistent across all modules
- [ ] Record model versions and configuration changes
- [ ] Validate inputs and handle errors explicitly
- [ ] Do not treat object detection as proof of identity or authorization
- [ ] Do not rely on AI detection as the only safety mechanism for robot movement
- [ ] Update this roadmap as tasks are completed
