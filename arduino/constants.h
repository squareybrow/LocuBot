#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * @file constants.h
 * @brief Project-wide constants for sensors, calibration, and timing.
 */

/** @brief Speed of sound in air (m/s) */
constexpr float SOUND_SPEED = 340.1;
/** @brief Timeout for ultrasonic pulse (microseconds) */
constexpr unsigned long PULSE_TIMEOUT = 12000;

/** @brief Magnetic declination angle (radians) */
constexpr float declinationAngle = 0.009;
/** @brief Minimum X value for compass calibration */
constexpr float x_min = -27.64;
/** @brief Maximum X value for compass calibration */
constexpr float x_max = 43.36;
/** @brief Minimum Y value for compass calibration */
constexpr float y_min = -47.82;
/** @brief Maximum Y value for compass calibration */
constexpr float y_max = 24.36;

/** @brief Minimum obstacle detection distance (cm) */
constexpr int MIN_OBS_DISTANCE = 15;
/** @brief Maximum obstacle detection distance (cm) */
constexpr int MAX_OBS_DISTANCE = 30;

/** @brief Interval between path messages (ms) */
constexpr unsigned long PATH_INTERVAL = 1000;
/** @brief Interval between obstacle messages (ms) */
constexpr unsigned long OBS_INTERVAL = 1000;

#endif