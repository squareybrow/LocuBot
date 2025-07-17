# GPS Mapper Bot Project

A modular system for autonomous robot navigation, real-time obstacle detection, secure wireless data transmission, and advanced visualization. This project combines Arduino-based embedded firmware, Python data processing, and Unity-powered 2D visualization.

---

## What’s in This Project?

- **Arduino Firmware:**  
  Collects GPS, compass, and ultrasonic sensor data, encrypts it using AES, and transmits wirelessly via LoRa.  
  *See [`arduino/readme.md`](arduino/readme.md) and [System Architecture](docs/system_architecture.md) for details.*

- **Python Toolkit:**  
  Logs, parses, and analyzes data received from the robot, estimates obstacle positions, and generates CSV logs and 2D plots.  
  *See [`python/readme.md`](python/readme.md).*

- **Unity Visualization:**  
  Loads CSV data and animates the robot’s journey, displaying its path, heading, and detected obstacles in a 2D environment.  
  *See [`unity/readme.md`](unity/readme.md).*

- **Technical Documentation:**  
  In-depth guides on system architecture, LoRa protocol, AES encryption, compass calibration, and obstacle detection.  
  *See [`docs/docs_structure.md`](docs/docs_structure.md) all technical references.*

---

## Documentation Map

- [System Architecture](docs/system_architecture.md)
- [Arduino Firmware Details](arduino/readme.md)
- [Python Data Toolkit](python/readme.md)
- [Unity Visualization](unity/readme.md)
- [AES Encryption](docs/aes_encryption.md)
- [LoRa Protocol](docs/lora_protocol.md)
- [Compass Implementation](docs/compass_implementation.md)
- [Obstacle Detection](docs/obstacle_detection.md)

---

## Quick Start

1. **Hardware & Firmware:**  
   Wire up your Arduino Mega with the required modules and upload the firmware ([arduino/readme.md](arduino/readme.md)).

2. **Data Logging & Analysis:**  
   Use the Python scripts to log and process data from the robot ([python/readme.md](python/readme.md)).

3. **Visualization:**  
   Import the CSV data into Unity to replay and analyze robot runs ([unity/readme.md](unity/readme.md)).

4. **Technical Details:**  
   Explore the [`docs/`](docs/) folder for deep dives into protocols, algorithms, and implementation.

---

*This project demonstrates a complete workflow for robotics: from real-time embedded sensing and secure wireless communication, to data analysis and interactive visualization. For detailed guides, see the documentation*
