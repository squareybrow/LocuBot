#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

/**
 * @file gps.h
 * @brief Interface for GPS module.
 */

/** @brief Global GPS object */
extern TinyGPSPlus gps;
/** @brief Software serial for GPS communication */
extern SoftwareSerial ss;

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