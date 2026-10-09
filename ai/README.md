# AI and Computer Vision Subsystem

## 1. Overview

The `ai/` directory contains the Artificial Intelligence (AI) and Computer Vision components of the Autonomous Hospital Delivery Robot.

The subsystem processes visual input, detects relevant objects, and provides structured perception results to the robot's higher-level software.

Potential applications include person detection, obstacle recognition, and identifying objects relevant to the robot's operating environment. The final supported tasks depend on the selected model and validated dataset.

The AI subsystem supports robot perception. It does not replace the independent safety mechanisms responsible for stopping the robot.

## 2. Directory Structure

```text
ai/
├── README.md
├── datasets/
├── models/
├── object_detection/
│   ├── detector.py
│   ├── preprocessing.py
│   └── postprocessing.py
├── inference/
│   ├── detector.py
│   └── inference.py
└── training/
    ├── train.py
    ├── evaluate.py
    └── requirements.txt
```

## 3. Directory Responsibilities

### `datasets/`

Documents and organizes the datasets used for model development.

Responsibilities:

* Record dataset sources and licenses.
* Define supported object classes.
* Document annotation formats.
* Track training, validation, and test splits.
* Record dataset limitations and versions.

**Input:** Images, annotations, class definitions, and dataset metadata.

**Output:** Organized and documented data suitable for training and evaluation.

### `models/`

Documents trained model artifacts and their deployment requirements.

Responsibilities:

* Track model versions.
* Record model architecture and configuration.
* Document expected input and output formats.
* Record evaluation results and known limitations.
* Explain how model artifacts are obtained.

**Input:** Trained checkpoints, exported models, and experiment metadata.

**Output:** Versioned model artifacts and deployment documentation.

### `object_detection/`

Contains reusable object-detection processing components.

#### `preprocessing.py`

Prepares input images for the selected model.

**Input:** Raw image or frame.

**Output:** Model-compatible image or tensor.

Possible operations include resizing, color conversion, normalization, and tensor formatting. Only operations required by the selected model should be implemented.

#### `detector.py`

Provides the object-detection logic for the selected model.

**Input:** Prepared image or model-compatible tensor, model configuration, and supported inference options.

**Output:** Raw or partially processed model predictions.

The exact interface must be documented in the implementation.

#### `postprocessing.py`

Converts raw predictions into a consistent application-level format.

**Input:** Model predictions, class information, and postprocessing configuration.

**Output:** Structured detections, potentially including class labels, confidence scores, and bounding-box coordinates.

Postprocessing may include confidence filtering, coordinate conversion, and duplicate-detection filtering when required by the model.

### `inference/`

Contains the inference workflow used to execute a trained model.

#### `inference.py`

Acts as the inference entry point or coordinates the inference workflow.

**Input:** Supported image or frame source, model configuration, and runtime options.

**Output:** Prediction results, processing status, and relevant error information.

#### `detector.py`

Provides the detector interface used by the inference workflow.

**Input:** Model-ready image data and detector configuration.

**Output:** Detection results in the format agreed upon by the AI and ROS 2 teams.

The distinction between `object_detection/detector.py` and `inference/detector.py` must remain clear. The former should contain reusable detection logic, while the latter should expose or adapt the detector for the inference workflow, unless the implementation defines a different separation.

### `training/`

Contains the scripts and dependencies required to train and evaluate models.

#### `train.py`

**Input:** Training dataset, model configuration, hyperparameters, and training options.

**Output:** Trained model checkpoints, training logs, and experiment results.

#### `evaluate.py`

**Input:** Trained model, evaluation dataset, and evaluation configuration.

**Output:** Evaluation metrics and reports.

Metrics depend on the selected task and may include precision, recall, and mean Average Precision (mAP) for object detection.

#### `requirements.txt`

Lists the Python packages required by the training scripts.

**Input:** Dependency definitions.

**Output:** A reproducible Python dependency installation specification.

## 4. Overall Data Flow

1. A camera or another approved source provides an image or frame.
2. Preprocessing converts the image into the model's expected input format.
3. The selected model performs inference.
4. Postprocessing converts predictions into structured detections.
5. The result is exposed to the consuming application.
6. The ROS 2 perception layer may use the detections for obstacle or person-awareness tasks.

Training and evaluation are development workflows; they do not need to run on the robot during normal operation.

## 5. Inputs and Outputs

| Component          | Main Input                    | Main Output            |
| ------------------ | ----------------------------- | ---------------------- |
| Datasets           | Images and annotations        | Organized labeled data |
| Training           | Dataset and configuration     | Trained model          |
| Evaluation         | Model and test data           | Metrics and report     |
| Preprocessing      | Raw image                     | Model-ready input      |
| Detection          | Model-ready input             | Predictions            |
| Postprocessing     | Raw predictions               | Structured detections  |
| Inference workflow | Image and model configuration | Final inference result |

## 6. Integration Requirements

* Agree on a common detection-result format.
* Document image dimensions and color-channel conventions.
* Define confidence thresholds and coordinate conventions.
* Record model dependencies and target hardware requirements.
* Avoid assuming a model is real-time capable before measuring its performance.
* Do not use AI predictions as the only mechanism for emergency stopping.

## 7. Testing

The subsystem should be tested for:

* Model loading and invalid model paths.
* Valid and invalid image inputs.
* Correct preprocessing dimensions and format.
* Correct output structure.
* Confidence-threshold behavior.
* Detection quality on a held-out dataset.
* Inference latency and memory consumption.
* Failure handling when the model or runtime is unavailable.

## 8. Completion Criteria

The AI subsystem is ready for integration when the model version, dependencies, input/output format, evaluation results, performance measurements, and known limitations are documented.

Only features implemented and tested in the repository should be described as completed.
