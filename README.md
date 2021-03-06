# Arduino Quadruped Robot

An arduino power quadruped robot sprinter/walker based on the designs by Sebastian Coddington. This version uses a different codebase and has some modifications to the board and battery mounts.

<div style="display: flex;">
<img src="https://github.com/joshgerdes/arduino-quadruped-robot/blob/main/resources/images/robot.jpg?raw=true" height="200px" style="margin: 20px;" alt="Robot" />

<img src="https://github.com/joshgerdes/arduino-quadruped-robot/blob/main/resources/images/robot-top.jpg?raw=true" height="200px" style="margin: 20px;" alt="Robot Top View" />

<img src="https://github.com/joshgerdes/arduino-quadruped-robot/blob/main/resources/images/robot-side.jpg?raw=true" height="200px" style="margin: 20px;" alt="Robot Side View" />
</div>

## Build Instructions

For the original robot, more detailed build and construction information can be found at: https://www.instructables.com/id/GorillaBot-the-3D-Printed-Arduino-Autonomous-Sprin/

## Wiring Diagram

![Fritzing diagram sketch](resources/wiring-diagram_bb.png)

## 3D Models

All new models were created in [Tinkercad](https://www.tinkercad.com/) and exported in STL format.

- [GROUP_BASE_BACK](resources/models/GROUP_BASE_BACK.stl)
- [GROUP_BASE_ELECTRONICS](resources/models/GROUP_BASE_ELECTRONICS.stl)
- [GROUP_BASE_FRONT](resources/models/GROUP_BASE_FRONT.stl)
- [GROUP_CIRCULAR_CLIPS](resources/models/GROUP_CIRCULAR_CLIPS.stl)
- [GROUP_CIRCULAR_PINS](resources/models/GROUP_CIRCULAR_PINS.stl)
- [GROUP_FEET_AND_SQUARE_CLIPS](resources/models/GROUP_FEET_AND_SQUARE_CLIPS.stl)
- [GROUP_LEGS_1](resources/models/GROUP_LEGS_1.stl)
- [GROUP_LEGS_2](resources/models/GROUP_LEGS_2.stl)
- [GROUP_LEGS_3](resources/models/GROUP_LEGS_3.stl)
- [GROUP_LEGS_4](resources/models/GROUP_LEGS_4.stl)

## Materials List

| Part                                         | Qty |                         |
| -------------------------------------------- | --- | ----------------------- |
| Arduino Nano V3.0                            | 1   | https://amzn.to/2Ek0Rtx |
| Nano I/O Shield v3.0 (with 5v toggle switch) | 1   | https://ebay.to/2RIoyPs |
| Ultrasonic Module HC-SR04 Distance Sensor    | 1   | https://amzn.to/3mFSaLz |
| HM-10 Bluetooth Module                       | 1   | https://amzn.to/2RIGpFQ |
| SG90 9G Micro Servos                         | 8   | https://amzn.to/3iU7odx |
| Breadboard Jumper Wires                      | 8   | https://amzn.to/2RKGrNF |
| 18650 Battery Shield                         | 1   | https://amzn.to/2FSBf7O |
| 18650 Batteries                              | 2   | https://amzn.to/32YADGJ |
| USB to DC 5.5 x 2.1mm 5V cable               | 1   | https://amzn.to/2HuPrEN |

## Mobile App Configurations

I chose to drive the robot with the [ArduinoBlue](https://sites.google.com/stonybrook.edu/arduinoble/) mobile app and library. The joystick is preconfigured (for steering and throttle) but you will need to setup buttons initially to drive the remaining functionality. The following list of functions are available to setup as buttons within the app:

| ID  | Name       | Description                                |
| --- | ---------- | ------------------------------------------ |
| 1   | Autonomous | Toggle on/off autonomous mode              |
| 2   | Stand      | All legs in an up position                 |
| 3   | Lay        | All legs in a down position                |
| 4   | Sit        | Back legs in down in a sitting position    |
| 5   | Crouch     | Front legs in down in a crouching position |
| 6   | Tilt       | Tilting each leg in a clockwise rotation   |
| 7   | Strut      | Strut walk forward for a few paces         |

## Libraries

- ArduinoBlue https://github.com/purwar2016/ArduinoBlue-library
- VarSpeedServo https://github.com/netlabtoolkit/VarSpeedServo

## Software & Other Resources

- Visual Studio Code - https://code.visualstudio.com/
- Arduino IDE - https://www.arduino.cc/en/Main/Software
- Ultimaker Cura - https://ultimaker.com/software/ultimaker-cura
- ArduinoBlue Mobile App - https://sites.google.com/stonybrook.edu/arduinoble/
