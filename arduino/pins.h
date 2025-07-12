#ifndef PINS_H
#define PINS_H

//Uses Arduino MEGA 2560

/**
 * @file pins.h
 * @brief Pin assignments for GPS, LoRa, and Ultrasonic modules.
 */
#define GPS_SERIAL Serial1 // RX 18, TX 19

/** @brief LoRa module Slave Select pin */
constexpr uint8_t LoRa_SS = 53;
/** @brief LoRa module Reset pin */
constexpr uint8_t LoRa_RST = 49;
/** @brief LoRa module DIO0 pin */
constexpr uint8_t LoRa_DIO0 = 2;

/** @brief Ultrasonic sensor trigger pin */
constexpr uint8_t TRIG_PIN = 40;
/** @brief Ultrasonic sensor echo pin */
constexpr uint8_t ECHO_PIN = 41;

#endif