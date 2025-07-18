#include "ultrasonic.h"
#include <Arduino.h>
#include "constants.h"
#include "pins.h"

// Initializes the ultrasonic sensor pins
void initUltrasonic() {
    pinMode(TRIG_PIN, OUTPUT);  // Set trigger pin as output
    pinMode(ECHO_PIN, INPUT);   // Set echo pin as input
}

// Measures distance using the ultrasonic sensor
// Returns distance in centimeters. Returns 999 if no reading
float measureDistance() {
  // Send a clean LOW pulse first
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Send HIGH pulse for 10 microseconds to trigger measurement
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long ping_travel_time;

  // Measure the time for echo pulse to return with timeout
  ping_travel_time = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT);
  if (ping_travel_time == 0) return 999;  // No signal reading (timeout or no obstacle)

  // Calculate distance: divide by 2 because sound travels to object and back
  float time = (ping_travel_time / 1E6) / 2;  // Convert microseconds to seconds, then divide by 2
  float distance = SOUND_SPEED * time * 100;  // Convert meters to centimeters

  return distance;
}