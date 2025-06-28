#ifndef PINS_H
#define PINS_H

/**
 * @file pins.h
 * @brief Pin assignments for GPS, LoRa, and Ultrasonic modules.
 */

/** @brief GPS module RX pin */
constexpr uint8_t GPS_RX = 7;
/** @brief GPS module TX pin */
constexpr uint8_t GPS_TX = 6;

/** @brief LoRa module Slave Select pin */
constexpr uint8_t LoRa_SS = 10;
/** @brief LoRa module Reset pin */
constexpr uint8_t LoRa_RST = 9;
/** @brief LoRa module DIO0 pin */
constexpr uint8_t LoRa_DIO0 = 3;

/** @brief Ultrasonic sensor trigger pin */
constexpr uint8_t TRIG_PIN = 5;
/** @brief Ultrasonic sensor echo pin */
constexpr uint8_t ECHO_PIN = 4;

#endif