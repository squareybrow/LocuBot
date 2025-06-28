# Arduino Navigation & Communication System

## Overview

This project integrates **GPS**, **Compass (HMC5883)**, **LoRa communication**, and **Ultrasonic sensors** to create a modular navigation and obstacle detection system for Arduino-compatible boards. It logs GPS path points, detects obstacles, and transmits data wirelessly via LoRa.

---

## Features

- **GPS Logging:** Records latitude, longitude, and compass heading at regular intervals.
- **Compass Integration:** Calibrated heading readings using the HMC5883 sensor.
- **Obstacle Detection:** Uses an ultrasonic sensor to detect and report obstacles within a configurable range.
- **LoRa Communication:** Sends path and obstacle data wirelessly.
- **Modular Design:** Each sensor and communication module is encapsulated for easy maintenance and extension.

---

## Hardware Requirements

- Arduino-compatible board (e.g., Uno, Mega)
- GPS module (e.g., NEO-6M)
- HMC5883L Compass module
- LoRa module (e.g., SX1278)
- Ultrasonic sensor (e.g., HC-SR04)
- Jumper wires, breadboard, and power supply

---

## Pin Assignments

See [`pins.h`](pins.h):

| Module      | Pin Name   | Arduino Pin |
|-------------|------------|-------------|
| GPS         | RX         | 7           |
| GPS         | TX         | 6           |
| LoRa        | SS         | 10          |
| LoRa        | RST        | 9           |
| LoRa        | DIO0       | 3           |
| Ultrasonic  | TRIG       | 5           |
| Ultrasonic  | ECHO       | 4           |

---

## Message Formats

- **Path Message:**  
  `PATH,<lat>,<lon>,<heading>,<packetNo>`
- **Obstacle Message:**  
  `OBS,<lat>,<lon>,<heading>,<distance>,<packetNo>`

---

## File Structure

- `nav_comm.ino` — Main Arduino sketch
- `gps.h` / `gps.cpp` — GPS interface and logging
- `compass.h` / `compass.cpp` — Compass initialization and heading calculation
- `lora_comm.h` / `lora_comm.cpp` — LoRa initialization and message sending
- `ultrasonic.h` / `ultrasonic.cpp` — Ultrasonic sensor initialization and distance measurement
- `constants.h` — Project-wide constants for calibration, timing, and thresholds
- `pins.h` — Pin assignments for all modules

---

## Usage

1. **Wire all modules** according to the pin assignments above.
2. **Install required libraries** in the Arduino IDE:
   - [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
   - [Adafruit HMC5883 Unified](https://github.com/adafruit/Adafruit_HMC5883_Unified)
   - [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
3. **Upload** the project to your Arduino board.
4. **Open the Serial Monitor** to view status and sent messages.
5. **Monitor LoRa receiver** for incoming path and obstacle messages.

---

## Customization

- Adjust obstacle detection thresholds and message intervals in `constants.h`.
- Modify message formats or add new sensors as needed.

---

## License

MIT License.  
See [LICENSE](LICENSE) for details.

---
