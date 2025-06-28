#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include "compass.h"
#include "constants.h"

/**
 * @brief Global magnetometer object.
 */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

/**
 * @brief Initializes the HMC5883 compass sensor.
 */
void initCompass() {
    if(!mag.begin())
    {
        Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
        while(true);
    }
}

/**
 * @brief Reads and averages compass heading over 10 samples.
 * @return Heading in degrees (0-359).
 */
int readCompass() {
  sensors_event_t event;
  
  float sum_heading = 0;
  float heading;

  for (int i = 0; i < 10; i++) {
    mag.getEvent(&event);

    // Normalize X and Y
    float x_norm = ((event.magnetic.x - x_min) / (x_max - x_min)) * 2.0 - 1.0;
    float y_norm = ((event.magnetic.y - y_min) / (y_max - y_min)) * 2.0 - 1.0;

    heading = atan2(y_norm, x_norm);

    // Apply local magnetic declination (~0.009 rad)
    heading += declinationAngle;

    sum_heading += heading;
    delay(10); // small delay between readings
  }

  heading = sum_heading / 10.0;

  if (heading < 0) heading += 2 * PI;
  if (heading > 2 * PI) heading -= 2 * PI;

  float headingDegrees = heading * 180.0 / PI;
  return (int)headingDegrees;
}