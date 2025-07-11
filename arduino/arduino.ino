// Arduino Sketch for Mapper bot using GPS, ULTRASONIC, MAGENETOMETER, LORA

#include "constants.h"
#include "pins.h"
#include "gps.h"
#include "ultrasonic.h"
#include "compass.h"
#include "lora_comm.h"

int packetNo = 0;

unsigned long lastPathSent = 0;
unsigned long lastObsSent = 0;

//Initialises LoRa, GPS, Ultrasonic, Compass

void setup() {
  Serial.begin(9600);
  delay(200);
  initLoRa();
  initGPS();
  initUltrasonic();
  initCompass();
}

// void loop() {
//   String msg;
//   while (ss.available() > 0) {
//     if (gps.encode(ss.read())) {
//       if (logPathPoint(msg)) {
//         msg += "," + String(packetNo++);
//         Serial.println(msg);
//       }
//     }
//   }
//   float distance = measureDistance();

//   if ((distance < MAX_OBS_DISTANCE) && (distance > MIN_OBS_DISTANCE)) {
//     delay(50);
//     float second_reading = measureDistance();
//     delay(50);
//     float third_reading = measureDistance();

//     if ((second_reading <= MAX_OBS_DISTANCE && second_reading >= MIN_OBS_DISTANCE) && (third_reading <= MAX_OBS_DISTANCE && third_reading >= MIN_OBS_DISTANCE)) {
//       int heading = readCompass();
//       String obsMsg = "OBS," + String(gps.location.lat(), 6) + "," +
//                       String(gps.location.lng(), 6) + "," +
//                       String(heading) + "," +
//                       String((second_reading + third_reading) / 2.0, 2) + "," +
//                       String(packetNo++);
//       Serial.println(obsMsg);
//     }
//   }
// }

void loop() {
  // GPS Path Logging:
  String msg;
  while(ss.available() > 0) {
    if (gps.encode(ss.read())) {
      if (millis() - lastPathSent > PATH_INTERVAL) {
        if (logPathPoint(msg)) {
          msg += "," + String(packetNo++);
          sendMessage(msg);
          lastPathSent = millis();
        }
      }
    }
  }

  // Obstacle Detection Logic:
  float distance = measureDistance();

  if ((distance < MAX_OBS_DISTANCE) && (distance > MIN_OBS_DISTANCE)) {
    delay(50);
    float second_reading = measureDistance();
    delay(50);
    float third_reading = measureDistance();

    if ((second_reading <= MAX_OBS_DISTANCE && second_reading >= MIN_OBS_DISTANCE) && (third_reading <= MAX_OBS_DISTANCE && third_reading >= MIN_OBS_DISTANCE)) { // 3 total readings to make the program less error prone
      if (millis() - lastObsSent > OBS_INTERVAL) {
        int heading = readCompass();
        String obsMsg = "OBS," + String(gps.location.lat(), 6) + "," +
                      String(gps.location.lng(), 6) + "," +
                      String(heading) + "," +
                      String((second_reading + third_reading) / 2.0, 2) + "," + // average reading
                      String(packetNo++);
        
        sendMessage(obsMsg);
        lastObsSent = millis();
      }
    }
  }
}