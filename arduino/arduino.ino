/**
 * @file nav_comm.ino
 * @brief Main Arduino sketch for GPS, Compass, LoRa, and Ultrasonic integration.
 */

#include "gps.h"
#include "compass.h"
#include "ultrasonic.h"
#include "constants.h"

/** @brief Packet counter for outgoing messages */
int packetNo = 0;

/** @brief Timestamp of last path message sent */
unsigned long lastPathSent = 0;
/** @brief Timestamp of last obstacle message sent */
unsigned long lastObsSent = 0;

/**
 * @brief Arduino setup function. Initializes all modules.
 */
void setup() {
  Serial.begin(9600);
  initUltrasonic();
  initCompass();
  initGPS();
}

/**
 * @brief Arduino main loop. Handles GPS logging and obstacle detection.
 */
void loop() {
  String msg;
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (logPathPoint(msg)) {
        msg += "," + String(packetNo++);
        Serial.println(msg);
      }
    }
  }
  float distance = measureDistance();

  if ((distance < MAX_OBS_DISTANCE) && (distance > MIN_OBS_DISTANCE)) {
    delay(50);
    float second_reading = measureDistance();
    delay(50);
    float third_reading = measureDistance();

    if ((second_reading <= MAX_OBS_DISTANCE && second_reading >= MIN_OBS_DISTANCE) && (third_reading <= MAX_OBS_DISTANCE && third_reading >= MIN_OBS_DISTANCE)) {
      int heading = readCompass();
      String obsMsg = "OBS," + String(gps.location.lat(), 6) + "," +
                      String(gps.location.lng(), 6) + "," +
                      String(heading) + "," +
                      String((second_reading + third_reading) / 2.0, 2) + "," +
                      String(packetNo++);
      Serial.println(obsMsg);
    }
  }
}
