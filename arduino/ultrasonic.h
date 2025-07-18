#ifndef ULTRASONIC_H
#define ULTRASONIC_H

// Ultrasonic sensor interface

// Initializes the ultrasonic sensor pins
void initUltrasonic();

// Measures distance using the ultrasonic sensor
// Returns distance in centimeters
float measureDistance();

#endif