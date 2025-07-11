#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include "pins.h"  // must define: #define GPS_SERIAL Serial1

/**
 * @file gps.h
 * @brief Interface for GPS module (Mega version).
 */

/** @brief Global GPS object */
extern TinyGPSPlus gps;

/** @brief Reference to Mega hardware serial for GPS */
#define ss GPS_SERIAL

/**
 * @brief Initializes the GPS module.
 */
void initGPS();

/**
 * @brief Logs current GPS position and heading to a string.
 * @param[out] outMsg Output string.
 * @return false if location is invalid, true otherwise.
 */
bool logPathPoint(String& outMsg);

#endif
