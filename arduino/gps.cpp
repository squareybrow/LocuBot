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
    ss.begin(9600);  // Initialize GPS serial communication at 9600 baud
}

// Logs current GPS position and heading to a comma-separated string
// Output string format: "PATH,lat,lon,heading"
// Returns false if location is invalid, true otherwise
bool logPathPoint(String& outMsg) {
    if(!gps.location.isValid()) {
        return false;  // GPS hasn't got a valid fix yet
    }
    int heading = readCompass();  // Get current compass heading
    // Format: PATH,latitude,longitude,heading (6 decimal places for coordinates)
    outMsg = "PATH," + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6) + "," + String(heading);
    return true;
}