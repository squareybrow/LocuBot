#ifndef ULTRASONIC_H
#define ULTRASONIC_H

/**
 * @file ultrasonic.h
 * @brief Ultrasonic sensor interface.
 */

/**
 * @brief Initializes the ultrasonic sensor pins.
 */
void initUltrasonic();

/**
 * @brief Measures distance using the ultrasonic sensor.
 * @return Distance in centimeters.
 */
float measureDistance();

#endif