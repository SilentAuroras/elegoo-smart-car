# Elegoo Car

Driving modes for ELEGOO Smart Robot Car v4.0. This defaults to obstacle avoidance by default, while hoping to implement other options in the future.

This uses the PlatformIO extension in VS Code or CLion, instead of the Arduino IDE.

Pinouts are defined for the SmartCar Shield-V1.1 in the ELEGOO documentation.

# Elegoo Car Modes

The current modes implemented for the Elegoo Car are as follows:

| Mode          | Status      |
| ------------------ | ----------- |
| Obstacle Avoidance |   Working   |


## Todo
Below is a list of issues or features that are added as issues arise:
- [x] Start on battery power only
- [x] Implement backup functionality
- [ ] Fix clearDirection(), hitting backup too often
- [ ] Better corner detection
