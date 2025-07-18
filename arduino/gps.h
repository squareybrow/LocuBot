#ifndef GPS_H
#define GPS_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include "pins.h"  // must define: #define GPS_SERIAL Serial1

// Interface for GPS module (Mega version)

// Global GPS object
extern TinyGPSPlus gps;

// Reference to Mega hardware serial for GPS
#define ss GPS_SERIAL

// Initializes the GPS module
void initGPS();

// Logs current GPS position and heading to a string
// Output string is passed by reference in outMsg
// Returns false if location is invalid, true otherwise
bool logPathPoint(String& outMsg);

#endif