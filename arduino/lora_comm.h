#ifndef LORA_COMM_H
#define LORA_COMM_H

#include <Arduino.h>
#include <LoRa.h>
#include <Crypto.h>
#include <AES.h>

// AES cipher and key used for encrypting messages before transmission
extern AES128 aes;
extern byte key[16];

// Initialize LoRa module and AES encryption
// Sets radio parameters for long range and reliability
void initLoRa();

// Encrypts the message using AES and sends it via LoRa
// Pads the message to 16 bytes, encrypts each block, then transmits
bool sendMessage(const String& msg);

#endif
