// Main sketch for Mapper bot using GPS, Ultrasonic, Magnetometer, and LoRa

#include "constants.h"
#include "pins.h"
#include "gps.h"
#include "ultrasonic.h"
#include "compass.h"
#include "lora_comm.h"

int packetNo = 0; // Used to track message sequence

unsigned long lastPathSent = 0; // Timestamp for last path message
unsigned long lastObsSent = 0;  // Timestamp for last obstacle message

// Setup all modules and serial communication
void setup() {
  Serial.begin(9600);
  delay(200);           // Give hardware time to power up
  initLoRa();           // LoRa + AES setup
  initGPS();            // GPS setup
  initUltrasonic();     // Ultrasonic sensor setup
  initCompass();        // Compass setup
}

void loop() {
  // Check for new GPS data and send path message at intervals
  String msg;
  while (ss.available() > 0) {
    if (gps.encode(ss.read())) {
      // Only send if enough time has passed since last message
      if (millis() - lastPathSent > PATH_INTERVAL) {
        if (logPathPoint(msg)) { // Format: "PATH,<lat>,<lon>,<heading>"
          msg += "," + String(packetNo++); // Add packet number
          sendMessage(msg);                // Encrypt and send via LoRa
          lastPathSent = millis();
        }
      }
    }
  }

  // Measure distance to obstacles and send message if detected
  float distance = measureDistance();

  // Only proceed if distance is within valid range
  if ((distance < MAX_OBS_DISTANCE) && (distance > MIN_OBS_DISTANCE)) {
    delay(50); // Short delay to reduce sensor noise
    float second_reading = measureDistance();
    delay(50);
    float third_reading = measureDistance();

    // Use three readings to avoid false positives
    if ((second_reading <= MAX_OBS_DISTANCE && second_reading >= MIN_OBS_DISTANCE) &&
        (third_reading <= MAX_OBS_DISTANCE && third_reading >= MIN_OBS_DISTANCE)) {
      // Only send if enough time has passed since last obstacle message
      if (millis() - lastObsSent > OBS_INTERVAL) {
        int heading = readCompass(); // Get current heading
        String obsMsg = "OBS," + String(gps.location.lat(), 6) + "," +
                        String(gps.location.lng(), 6) + "," +
                        String(heading) + "," +
                        String((second_reading + third_reading) / 2.0, 2) + "," + // Average last two readings
                        String(packetNo++);
        sendMessage(obsMsg); // Encrypt and send via LoRa
        lastObsSent = millis();
      }
    }
  }
}