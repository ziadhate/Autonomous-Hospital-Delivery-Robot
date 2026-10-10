# Hardware Bill of Materials (BOM)

## Autonomous AI-Powered Hospital Delivery & Infection-Control Robot



## 1. Main Electronics and Sensors

| No. | Component | Model / Specification | Estimated Price (EGP) |
|---:|---|---|---:|
| 1 | Main Computer | Raspberry Pi 4 Model B – 8GB RAM | 9,500 |
| 2 | Storage | SanDisk Extreme microSDXC – 128GB | 3,200 |
| 3 | STM32 Development Board | NUCLEO-F401RE | 2,100 |
| 4 | LiDAR Sensor | Slamtec RPLIDAR A1M8 | 8,500 |
| 5 | Main Camera | Raspberry Pi Camera Module 3 | 4,500 |
| 6 | Distance Sensor | VL53L1X Time-of-Flight Sensor | 330 |
| 7 | IMU Sensor | MPU-6050 6-Axis IMU | 175 |
| 8 | RFID Reader | RC522 RFID Module | 120 |
| 9 | CAN Transceiver | SN65HVD230 | 850 |
| 10 | CAN Controller Module | MCP2515 CAN Controller | 400 |

## 2. Motors and Power System

| No. | Component | Model / Specification | Estimated Price (EGP) |
|---:|---|---|---:|
| 11 | Drive Motors | 12V DC Geared Motors with Encoders | TBD |
| 12 | Motor Driver | Cytron MDDS30 | TBD |
| 13 | Battery | 12V LiFePO4 Battery Pack | TBD |
| 14 | Battery Management | Compatible LiFePO4 BMS | TBD |
| 15 | Voltage Converter | 12V-to-5V, 5A DC-DC Buck Converter | TBD |
| 16 | Fuse Protection | Automotive Blade Fuse Holder and Fuses | TBD |
| 17 | Emergency Stop | 22mm Mushroom Emergency Stop Switch | 240 |
| 18 | Electrical Safety | DC-Rated Contactor and Interlock Switch | TBD |
| 19 | Power Distribution | Fused Power Distribution Board | TBD |
| 20 | Cooling | 5V Cooling Fan and Heatsink | TBD |

## 3. Chassis and Mechanical Parts

| No. | Component | Model / Specification | Estimated Price (EGP) |
|---:|---|---|---:|
| 21 | Robot Chassis | 4-Wheel Mobile Robot / Custom Aluminum Chassis | TBD |
| 22 | Wheels | 100mm Rubber Robot Wheels | TBD |
| 23 | Delivery Compartment | Lockable Metal Storage Box | TBD |
| 24 | Fabrication Materials | Aluminum Sheets and 2020 Aluminum Extrusions | TBD |
| 25 | Fasteners | M3/M4 Stainless Steel Screws and Nuts | TBD |
| 26 | Mechanical Assembly | Aluminum Brackets, Hinges, and Mounting Hardware | TBD |
| 27 | Cable Management | Cable Sleeves, Glands, and Connectors | TBD |

## 4. Humanoid Appearance and Interaction

| No. | Component | Model / Specification | Estimated Price (EGP) |
|---:|---|---|---:|
| 28 | Robot Face Display | 7-inch HDMI LCD Display for Animated Expressions | 4,000–8,000 |
| 29 | Head Enclosure | Custom 3D-Printed Robot Head Shell | TBD |
| 30 | Face Camera | Wide-Angle USB Camera | 1,300 |
| 31 | Voice Input | USB Microphone | TBD |
| 32 | Voice Output | Mini Speaker with Audio Amplifier | TBD |
| 33 | Robot Arms | Custom 3D-Printed Arms | TBD |
| 34 | Torso Structure | Custom Robot Torso Enclosure | TBD |
| 35 | Neck Structure | Robot Neck Mounting Bracket | TBD |
| 36 | Head Movement | Metal Gear Servo Motor with Pan-Tilt Bracket | TBD |
| 37 | Display Mount | Custom LCD Mounting Bracket | TBD |

## 5. System Architecture

| Subsystem | Main Responsibility |
|---|---|
| Raspberry Pi 4 | Linux, ROS 2, SLAM, navigation, AI perception, and mission management |
| STM32 | Motor control, encoder feedback, low-level sensors, and real-time safety |
| LiDAR and Camera | Environment perception and navigation support |
| CAN Communication | Communication between the high-level computer and the low-level controller |
| Power System | Battery supply, voltage regulation, fusing, and electrical protection |
| Dashboard | Mission management, robot status, alerts, and delivery tracking |
| Face Display | Animated expressions and user interaction |

## 6. Important Engineering Notes

- **Prices:** All listed prices are preliminary estimates in EGP, not confirmed supplier quotations.
- **TBD:** The price has not yet been determined.
- **CAN compatibility:** The STM32F401RCT6 does not include a built-in CAN controller. An external controller may be required. A CAN transceiver alone is not sufficient.
- **Emergency stop:** The emergency-stop circuit should stop hazardous robot motion independently of the main software.
- **Power sizing:** Select the battery, BMS, motor driver, wiring, fuses, and converters according to the motors' current requirements and the complete system load.
- **Display planning:** Confirm whether the robot face display can also serve as the optional touchscreen to avoid purchasing two displays unnecessarily.
- **Camera planning:** Confirm whether the main camera and face camera have separate functions before purchasing both.
- **Final purchasing:** Verify component specifications, interfaces, availability, and supplier quotations before ordering.

## 7. Purchasing Status

| Status | Meaning |
|---|---|
| Planned | Component is included in the proposed design |
| To Be Confirmed | Compatibility or specification needs verification |
| Price TBD | Supplier price has not been collected |
| Approved | Component has been reviewed and approved for purchase |

**Document Status:** Preliminary BOM — Pending Technical Review and Supplier Quotations.
