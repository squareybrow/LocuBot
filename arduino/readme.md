<<<<<<< HEAD
# GPS Bot Mapper

A modular system for collecting, transmitting, and visualizing GPS-based navigation and obstacle data from autonomous bots or vehicles. The project consists of two main components:

- **Arduino Navigation & Communication System** (hardware + firmware)
- **Python Toolkit** for data logging, processing, and visualization

---

## 1. Arduino Navigation & Communication System

Located in the `arduino/` folder.

### Overview

This subsystem integrates **GPS**, **Compass (HMC5883)**, **LoRa communication**, and **Ultrasonic sensors** to create a modular navigation and obstacle detection system for Arduino-compatible boards. It logs GPS path points, detects obstacles, and transmits data wirelessly via LoRa.

### Features
=======
# Arduino Navigation & Communication System

## Overview

This project integrates **GPS**, **Compass (HMC5883)**, **LoRa communication**, and **Ultrasonic sensors** to create a modular navigation and obstacle detection system for Arduino-compatible boards. It logs GPS path points, detects obstacles, and transmits data wirelessly via LoRa.

---

## Features
>>>>>>> bad439e (Reinitialize Arduino folder)

- **GPS Logging:** Records latitude, longitude, and compass heading at regular intervals.
- **Compass Integration:** Calibrated heading readings using the HMC5883 sensor.
- **Obstacle Detection:** Uses an ultrasonic sensor to detect and report obstacles within a configurable range.
- **LoRa Communication:** Sends path and obstacle data wirelessly.
- **Modular Design:** Each sensor and communication module is encapsulated for easy maintenance and extension.

<<<<<<< HEAD
### Hardware Requirements
=======
---

## Hardware Requirements
>>>>>>> bad439e (Reinitialize Arduino folder)

- Arduino-compatible board (e.g., Uno, Mega)
- GPS module (e.g., NEO-6M)
- HMC5883L Compass module
- LoRa module (e.g., SX1278)
- Ultrasonic sensor (e.g., HC-SR04)
- Jumper wires, breadboard, and power supply

<<<<<<< HEAD
### Pin Assignments

See [`pins.h`](arduino/pins.h):
=======
---

## Pin Assignments

See [`pins.h`](pins.h):
>>>>>>> bad439e (Reinitialize Arduino folder)

| Module      | Pin Name   | Arduino Pin |
|-------------|------------|-------------|
| GPS         | RX         | 7           |
| GPS         | TX         | 6           |
| LoRa        | SS         | 10          |
| LoRa        | RST        | 9           |
| LoRa        | DIO0       | 3           |
| Ultrasonic  | TRIG       | 5           |
| Ultrasonic  | ECHO       | 4           |

<<<<<<< HEAD
### Message Formats
=======
---

## Message Formats
>>>>>>> bad439e (Reinitialize Arduino folder)

- **Path Message:**  
  `PATH,<lat>,<lon>,<heading>,<packetNo>`
- **Obstacle Message:**  
  `OBS,<lat>,<lon>,<heading>,<distance>,<packetNo>`

<<<<<<< HEAD
### File Structure
=======
---

## File Structure
>>>>>>> bad439e (Reinitialize Arduino folder)

- `nav_comm.ino` — Main Arduino sketch
- `gps.h` / `gps.cpp` — GPS interface and logging
- `compass.h` / `compass.cpp` — Compass initialization and heading calculation
- `lora_comm.h` / `lora_comm.cpp` — LoRa initialization and message sending
- `ultrasonic.h` / `ultrasonic.cpp` — Ultrasonic sensor initialization and distance measurement
- `constants.h` — Project-wide constants for calibration, timing, and thresholds
- `pins.h` — Pin assignments for all modules

<<<<<<< HEAD
### Usage
=======
---

## Usage
>>>>>>> bad439e (Reinitialize Arduino folder)

1. **Wire all modules** according to the pin assignments above.
2. **Install required libraries** in the Arduino IDE:
   - [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
   - [Adafruit HMC5883 Unified](https://github.com/adafruit/Adafruit_HMC5883_Unified)
   - [LoRa](https://github.com/sandeepmistry/arduino-LoRa)
3. **Upload** the project to your Arduino board.
4. **Open the Serial Monitor** to view status and sent messages.
5. **Monitor LoRa receiver** for incoming path and obstacle messages.

<<<<<<< HEAD
### Customization
=======
---

## Customization
>>>>>>> bad439e (Reinitialize Arduino folder)

- Adjust obstacle detection thresholds and message intervals in `constants.h`.
- Modify message formats or add new sensors as needed.

---
<<<<<<< HEAD

## 2. Python Toolkit

Located in the `python/` folder.

### Overview

This toolkit provides scripts for logging, processing, analyzing, and visualizing GPS path and obstacle data collected from the Arduino system or similar sources.

### Features

- **Serial Data Logging:** Capture real-time GPS and obstacle data from a microcontroller via serial port and save to CSV.
- **Parse and filter GPS path and obstacle data from CSV files.**
- **Estimate obstacle positions using heading and distance.**
- **Visualize bot trajectory and obstacle locations in both absolute (UTM) and relative coordinates.**
- **Generate publication-quality plots for analysis.**

### File Overview

- **log_serial_data.py**  
  - Connects to a serial port (default `/dev/ttyACM0`, change as needed for your system).
  - Listens for incoming messages in the format:
    - `PATH,<lat>,<lon>,<heading>`
    - `OBS,<lat>,<lon>,<heading>,<distance>`
  - Writes all received lines to `backup.txt` for redundancy.
  - Saves parsed path data to `path_data.csv` and obstacle data to `obs_data.csv` upon exit (Ctrl+C).

- **plot_map.py**  
  - Reads `path_data.csv` and `obs_data.csv`.
  - Converts all coordinates to UTM (meters) for accurate distance representation.
  - Estimates obstacle positions in UTM coordinates using heading and distance.
  - Plots both:
    - **Absolute trajectory:** Path and obstacles in UTM coordinates (`trajectory_absolute.png`)
    - **Relative trajectory:** Path and obstacles relative to the start point (`trajectory_relative.png`)
  - Visualizes heading directions for both path and obstacles.
  - Draws dotted lines from the bot to each estimated obstacle position.
  - Outputs estimated obstacle positions to `estimated_data.csv`.

### Data Format

Both scripts expect or generate the following CSV files:

- **path_data.csv**
  ```
  Latitude,Longitude,Heading
  12.9716,77.5946,90
  12.9717,77.5947,95
  ...
  ```

- **obs_data.csv**
  ```
  Latitude,Longitude,Heading,Distance
  12.9716,77.5946,180,150
  ...
  ```

### How It Works

1. **Data Logging:**  
   Run `log_serial_data.py` to capture real-time data from your bot's serial output.  
   - All lines are backed up to `backup.txt`.
   - Path and obstacle data are saved to `path_data.csv` and `obs_data.csv` when you stop the script.

2. **Data Processing & Visualization:**  
   Run `plot_map.py` to:
   - Filter and convert GPS coordinates to UTM.
   - Estimate obstacle positions using heading and distance.
   - Plot the bot's path and obstacles in both absolute and relative coordinates.
   - Save plots as PNG images and estimated obstacle positions as `estimated_data.csv`.

### Usage

1. **Install dependencies:**
   ```sh
   pip install numpy matplotlib utm pyserial
   ```

2. **Log data from your bot:**
   - Edit `log_serial_data.py` to use the correct serial port for your system (e.g., `COM3` on Windows).
   - Run:
     ```sh
     python log_serial_data.py
     ```
   - Stop with Ctrl+C when done. This will save `path_data.csv` and `obs_data.csv`.

3. **Visualize and analyze:**
   - Run:
     ```sh
     python plot_map.py
     ```
   - View the generated plots: `trajectory_absolute.png`, `trajectory_relative.png`.
   - Check `estimated_data.csv` for processed obstacle positions.

### Example Output

- `trajectory_absolute.png` — Path and obstacles in UTM meters.
- `trajectory_relative.png` — Path and obstacles relative to the start point.
- `estimated_data.csv` — Estimated obstacle positions in UTM coordinates.

### Requirements

- Python 3.x
- numpy
- matplotlib
- utm
- pyserial (for serial logging)

### Customization

- Adjust plotting parameters (colors, markers, skip intervals) in `plot_map.py` as needed.
- Change the serial port and baud rate in `log_serial_data.py` to match your hardware.
- Extend the scripts to support additional sensors or data fields.

---

## License

MIT License

---
=======
>>>>>>> bad439e (Reinitialize Arduino folder)
