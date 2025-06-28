#ifndef COMPASS_H
#define COMPASS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

/**
 * @file compass.h
 * @brief Interface for compass (HMC5883) sensor.
 */

/** @brief Global magnetometer object */
extern Adafruit_HMC5883_Unified mag;

/**
 * @brief Initializes the compass sensor.
 */
void initCompass();

/**
 * @brief Reads the compass heading.
 * @return Heading in degrees (0-359).
 */
int readCompass();

#endif
