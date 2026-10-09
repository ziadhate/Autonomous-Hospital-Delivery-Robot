# AI and Computer Vision Subsystem

## 1. Overview

The AI subsystem processes supported visual or other model inputs and produces structured results for the robot's higher-level software.

Depending on the selected requirements, this subsystem may support object detection or other perception features. It must not be treated as the sole mechanism for immediate motor safety.

## 2. Responsibilities

* Manage dataset documentation.
* Define data preprocessing.
* Train and evaluate selected models.
* Export and version model artifacts.
* Run inference on the target computer.
* Convert model outputs into documented application data.
* Report inference errors and performance limitations.

## 3. Suggested Directory Structure

```text
ai/
├── README.md
├── datasets/
│   └── README.md
├── models/
│   └── README.md
├── training/
│   └── README.md
└── inference/
    ├── README.md
    ├── inference.py
    └── detector.py
```

This structure is proposed. Match it to the files actually present in the repository.

## 4. `datasets/`

**Purpose:** Documents the datasets used to develop and evaluate AI models.

**Input:**

* Approved images or other data.
* Labels and annotations.
* Dataset source and license information.

**Output:**

* Documented dataset organization.
* Label definitions.
* Training, validation, and test split information.

The dataset documentation must identify data provenance, permitted usage, annotation format, and known limitations. Do not commit large or restricted datasets without confirming licensing and repository policy.

## 5. `models/`

**Purpose:** Documents trained models and their deployment requirements.

**Input:**

* Training configuration.
* Dataset version.
* Model architecture.
* Training and evaluation results.

**Output:**

* Model artifacts or references to their storage.
* Model version information.
* Input/output specifications.
* Deployment requirements.

Each model must document its expected input shape, color format, normalization, supported classes, output format, and known limitations.

## 6. `training/`

**Purpose:** Contains training and evaluation code where training is part of the project.

**Input:**

* Dataset and annotation paths.
* Training configuration.
* Model architecture.
* Training parameters.

**Output:**

* Trained model checkpoints.
* Training metrics.
* Evaluation results.
* Exported deployment artifacts where supported.

Training and evaluation must use documented dataset splits to reduce the risk of misleading results.

## 7. `inference/inference.py`

**Purpose:** Provides an inference entry point or coordinates the inference workflow.

**Input:**

* Image, video frame, or camera input.
* Model path.
* Inference configuration.

**Output:**

* Inference results in the documented format.
* Processing status and error information.
* Optional performance measurements.

The exact interface must be defined by the implementation.

## 8. `inference/detector.py`

**Purpose:** Provides the object-detection interface if object detection is selected.

**Input:**

* Image or frame in the documented format.
* Model or inference-engine reference.
* Confidence and detection configuration.

**Output:**

* Detected class labels.
* Confidence scores.
* Bounding boxes or other model outputs.
* Empty detection results when no valid detections are produced.
* Error status when inference fails.

The detector must document coordinate conventions, image dimensions, confidence interpretation, and any postprocessing performed.

## 9. AI-to-Robot Interface

The AI subsystem should return structured perception results. The ROS 2 or application layer determines how those results are used.

AI results must not directly bypass firmware command validation, motion limits, or the robot's defined safety mechanisms.

## 10. Testing and Evaluation

Tests should document:

* Model version.
* Dataset version.
* Supported classes.
* Precision and recall where applicable.
* False-positive and false-negative behavior.
* Inference latency on the target computer.
* Memory and compute requirements.
* Behavior under poor lighting or unfamiliar scenes.

A model is ready for integration only when its output format, performance limits, and failure behavior are documented.
