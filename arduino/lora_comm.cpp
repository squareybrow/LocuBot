#include <Arduino.h>
#include <Crypto.h>
#include <LoRa.h>
#include <SPI.h>
#include <AES.h>
#include "lora_comm.h"
#include "constants.h"
#include "pins.h"

/**
 * @brief Initializes the LoRa module.
 */

AES128 aes;
byte key[16] = {'s','e','c','r','e','t','k','e','y','1','2','3','4','5','6','7'};


void initLoRa() {
    LoRa.setPins(LoRa_SS, LoRa_RST, LoRa_DIO0);
    if (!LoRa.begin(433E6)) {
        Serial.println("LoRa init failed. Check wiring.");
        while (true);
    }

    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3);
    LoRa.setCodingRate4(8);
    LoRa.setSyncWord(0x34);
    LoRa.enableCrc();

    aes.setKey(key, sizeof(key));
    Serial.println("LoRa + AES Sender Ready");
}

/**
 * @brief Sends a message via LoRa.
 * @param msg Message to send.
 * @return true if sent.
 */
bool sendMessage(const String& msg) {
    int msg_len = msg.length();
    int pad_len = 16 - (msg_len % 16);
    int total_len = msg_len + pad_len;

    byte padded_msg[total_len];

    for (int i = 0; i < msg_len; i++) {
        padded_msg[i] = msg[i];
    }

    for (int i = 0; i < pad_len; i++) {
        padded_msg[msg_len + i] = pad_len;
    }

    byte cipher[total_len];

    for (int i = 0; i < total_len; i += 16) {
        aes.encryptBlock(cipher + i, padded_msg + i);
    }
    
    LoRa.beginPacket();
    LoRa.write(cipher, total_len);
    LoRa.endPacket();

    Serial.print("Encrypted: ");
    for (int i = 0; i < total_len; i++) {
        Serial.print(cipher[i], HEX);
        Serial.print("");
    }

    Serial.println();

    Serial.println("Sent: " + msg);
    return true;
}