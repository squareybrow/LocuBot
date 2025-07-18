#ifndef CONSTANTS_H
#define CONSTANTS_H

// Project-wide constants for sensors, calibration, and timing

// Speed of sound in air at room temperature (m/s)
constexpr float SOUND_SPEED = 340.1;
// Maximum time to wait for ultrasonic pulse return (microseconds)
constexpr unsigned long PULSE_TIMEOUT = 12000;

// Magnetic declination angle for compass correction (radians)
constexpr float declinationAngle = 0.009;
// Compass calibration boundaries for X-axis
constexpr float x_min = -27.64;
constexpr float x_max = 43.36;
// Compass calibration boundaries for Y-axis
constexpr float y_min = -47.82;
constexpr float y_max = 24.36;

// Obstacle detection range limits (cm)
constexpr int MIN_OBS_DISTANCE = 15;  // Minimum distance to consider as obstacle
constexpr int MAX_OBS_DISTANCE = 30;  // Maximum distance to detect obstacles

// Communication timing intervals (milliseconds)
constexpr unsigned long PATH_INTERVAL = 1000;  // How often to send path data
constexpr unsigned long OBS_INTERVAL = 1000;   // How often to send obstacle data

#endif