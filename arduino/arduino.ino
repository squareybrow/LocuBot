/**
 * @file nav_comm.ino
 * @brief Main Arduino sketch for GPS, Compass, LoRa, and Ultrasonic integration.
 */

#include "lora_comm.h"

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
  initLoRa();
}

/**
 * @brief Arduino main loop. Handles GPS logging and obstacle detection.
 */
void loop() {
  String msg = "Hello 123456987 World fhuyfgaifll.jafl";
  msg += " " +  String(packetNo);
  sendMessage(msg);
  packetNo++;
}
