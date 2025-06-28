#include "ultrasonic.h"
#include <Arduino.h>
#include "constants.h"
#include "pins.h"

/**
 * @brief Initializes the ultrasonic sensor pins.
 */
void initUltrasonic() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

/**
 * @brief Measures distance using the ultrasonic sensor.
 * @return Distance in centimeters. Returns 999 if no reading.
 */
float measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long ping_travel_time;

  ping_travel_time = pulseIn(ECHO_PIN, HIGH, PULSE_TIMEOUT); // timeout
  if (ping_travel_time == 0) return 999;  // Signal no reading

  float time = (ping_travel_time / 1E6) / 2;
  float distance = SOUND_SPEED * time * 100;

  return distance;
}