#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include "lora_comm.h"
#include "constants.h"
#include "pins.h"

/**
 * @brief Initializes the LoRa module.
 */
void initLoRa() {
    LoRa.setPins(LoRa_SS, LoRa_RST, LoRa_DIO0);
    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed. Check wiring.");
        while (true);
    }

    LoRa.setSyncWord(0x35);
    LoRa.enableCrc();
    Serial.println("LoRa transmitter ready.");
}

/**
 * @brief Sends a message via LoRa.
 * @param msg Message to send.
 * @return true if sent.
 */
bool sendMessage(const String& msg) {
    LoRa.beginPacket();
    LoRa.print(msg);
    LoRa.endPacket();

    Serial.println("Sent: " + msg);
    return true;
}