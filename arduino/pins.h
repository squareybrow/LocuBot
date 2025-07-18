#ifndef PINS_H
#define PINS_H

//Uses Arduino MEGA 2560

// Pin assignments for GPS, LoRa, and Ultrasonic modules

// GPS module uses hardware serial port 1 (pins 18 & 19)
#define GPS_SERIAL Serial1 // RX 18, TX 19

// LoRa module SPI connections
constexpr uint8_t LoRa_SS = 53;    // Slave Select pin for SPI communication
constexpr uint8_t LoRa_RST = 49;   // Reset pin to restart LoRa module
constexpr uint8_t LoRa_DIO0 = 2;   // Digital I/O pin for LoRa interrupts

// Ultrasonic sensor HC-SR04 connections
constexpr uint8_t TRIG_PIN = 40;   // Trigger pin to initiate measurement
constexpr uint8_t ECHO_PIN = 41;   // Echo pin to receive pulse return

#endif