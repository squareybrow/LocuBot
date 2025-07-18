#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "compass.h"
#include "constants.h"

// Create a global magnetometer object with a unique ID
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

/**
 * @brief Initializes the HMC5883 compass sensor.
 */
void initCompass() {
    if(!mag.begin())
    {
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while(true); // Infinite loop to halt execution if sensor is missing
    }
}

/**
 * @brief Reads and averages compass heading over 10 samples.
 * @return Heading in degrees (0-359).
 */
int readCompass() {
  sensors_event_t event; // Structure to hold sensor data
  
  float sum_heading = 0; // Accumulates heading values for averaging
  float heading;

  for (int i = 0; i < 10; i++) {
    mag.getEvent(&event); // Read sensor data

    // Normalize X and Y values using calibration constants
    float x_norm = ((event.magnetic.x - x_min) / (x_max - x_min)) * 2.0 - 1.0;
    float y_norm = ((event.magnetic.y - y_min) / (y_max - y_min)) * 2.0 - 1.0;

    // Calculate heading in radians
    heading = atan2(y_norm, x_norm);

    // Add magnetic declination to correct for local difference between magnetic and true north
    heading += declinationAngle;

    sum_heading += heading; // Add to sum for averaging
    delay(10); // Short delay between readings for stability
  }

  // Average the heading over 10 samples
  heading = sum_heading / 10.0;

  // Ensure heading is within 0 to 2*PI radians
  if (heading < 0) heading += 2 * PI;
  if (heading > 2 * PI) heading -= 2 * PI;

  // Convert radians to degrees
  float headingDegrees = heading * 180.0 / PI;
  return (int)headingDegrees; // Return as integer
}