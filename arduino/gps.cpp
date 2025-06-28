#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include "gps.h"
#include "compass.h"
#include "constants.h"
#include "pins.h"

/**
 * @brief Global GPS object.
 */
TinyGPSPlus gps;
/**
 * @brief Software serial for GPS communication.
 */
SoftwareSerial ss(GPS_RX, GPS_TX);

/**
 * @brief Initializes the GPS module.
 */
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