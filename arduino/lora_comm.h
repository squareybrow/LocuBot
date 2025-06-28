#ifndef LORA_COMM_H
#define LORA_COMM_H

#include <Arduino.h>
#include <LoRa.h>

/**
 * @file lora_comm.h
 * @brief Interface for LoRa communication.
 */

/**
 * @brief Initializes the LoRa module.
 */
void initLoRa();

/**
 * @brief Sends a message via LoRa.
 * @param msg Message to send.
 * @return true if sent.
 */
bool sendMessage(const String& msg);

#endif
