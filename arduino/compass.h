#ifndef COMPASS_H
#define COMPASS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>

//Initialises Magnetometer
void initCompass();

// Reads Compass heading
int readCompass();

#endif
