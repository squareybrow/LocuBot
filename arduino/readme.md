# Arduino Navigation & Communication System

## Overview

This project integrates **GPS**, **Compass (HMC5883)**, **LoRa communication**, and **Ultrasonic sensors** to create a modular navigation and obstacle detection system using Arduino MEGA 2560. It logs GPS path points, detects obstacles, and transmits data wirelessly via LoRa.

---

## Features

- **GPS Logging:** Records latitude, longitude, and compass heading at regular intervals.
- **Compass Integration:** Calibrated heading readings using the HMC5883 sensor.
- **Obstacle Detection:** Uses an ultrasonic sensor to detect and report obstacles within a configurable range.
- **LoRa Communication:** Sends path and obstacle data wirelessly.
- **Modular Design:** Each sensor and communication module is encapsulated for easy maintenance and extension.

---

## Hardware Requirements

- Arduino Mega
- GPS module (NEO-6M)
- HMC5883L Compass module
- LoRa module (SX1278)
- Ultrasonic sensor (HC-SR04)

---

## Pin Assignments

See [`pins.h`](pins.h):

| Module      | Pin Name   | Arduino Pin |
|-------------|------------|-------------|
| GPS         | RX         | Serial1(18) |
| GPS         | TX         | Serial1(19) |
| LoRa        | NSS        | 53          |
| LoRa        | RST        | 49          |
| LoRa        | DIO0       | 2           |
| Ultrasonic  | TRIG       | 40          |
| Ultrasonic  | ECHO       | 41          |

---

## Circuit Wiring Diagram
![Wiring Diagram](../docs/circuit.png)

---

## Message Formats

- **Path Message:**  
  `PATH,<lat>,<lon>,<heading>,<packetNo>`  
  - `lat`: Latitude  
  - `lon`: Longitude  
  - `heading`: Compass heading  
  - `packetNo`: Message sequence number

- **Obstacle Message:**  
  `OBS,<lat>,<lon>,<heading>,<distance>,<packetNo>`  
  - `distance`: Distance to obstacle

---

## File Structure

- `arduino.ino` — Main Arduino sketch
- `gps.h` / `gps.cpp` — GPS interface and logging
- `compass.h` / `compass.cpp` — Compass initialization and heading calculation
- `lora_comm.h` / `lora_comm.cpp` — LoRa initialization and message sending
- `ultrasonic.h` / `ultrasonic.cpp` — Ultrasonic sensor initialization and distance measurement
- `constants.h` — Project-wide constants for calibration, timing, and thresholds
- `pins.h` — Pin assignments for all modules

---

## Usage

1. **Wire all modules** according to the pin assignments above.
2. **Install required libraries** in the Arduino IDE (via Library Manager or links below):
    - [Arduino.h](https://www.arduino.cc/en/Reference/Arduino)
    - [Wire.h](https://www.arduino.cc/en/Reference/Wire)
    - [Adafruit_Sensor.h](https://github.com/adafruit/Adafruit_Sensor)
    - [Adafruit_HMC5883_U.h](https://github.com/adafruit/Adafruit_HMC5883_Unified)
    - [TinyGPS++.h](https://github.com/mikalhart/TinyGPSPlus)
    - [LoRa.h](https://github.com/sandeepmistry/arduino-LoRa)
    - [Crypto.h](https://rweather.github.io/arduinolibs/crypto.html)
    - [AES.h](https://rweather.github.io/arduinolibs/aes.html)
    - [SPI.h](https://www.arduino.cc/en/Reference/SPI)
3. **Upload** the project to your Arduino board.
4. **Open the Serial Monitor** to view status and sent messages.
5. **Monitor LoRa receiver** for incoming path and obstacle messages.

---

## Customization

- Adjust obstacle detection thresholds and message intervals in `constants.h`.
- Modify message formats or add new sensors as needed.
- Change pin layouts in `pins.h`

---
