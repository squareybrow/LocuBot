#include <Arduino.h>
#include <TinyGPS++.h>
#include "gps.h"
#include "compass.h"
#include "constants.h"
#include "pins.h"  // has: #define GPS_SERIAL Serial1

TinyGPSPlus gps;

// Use Serial1 (Mega) instead of SoftwareSerial
#define ss GPS_SERIAL

void initGPS() {
    ss.begin(9600);
}

/**
 * @brief Logs current GPS position and heading to a comma-separated string.
 * @param[out] outMsg Output string with format "PATH,lat,lon,heading"
 * @return false if location is invalid, true otherwise.
 */
bool logPathPoint(String& outMsg) {
    if(!gps.location.isValid()) {
        return false;
    }
    int heading = readCompass();
    outMsg = "PATH," + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) + "," + String(heading);
    return true;
}