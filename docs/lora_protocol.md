# LoRa Communication Protocol

## Overview

This implementation uses **LoRa (Long Range)** technology optimized for maximum range and reliability. The system is configured for long-distance communication with built-in error correction and encryption.

## LoRa Configuration

### Radio Parameters

```cpp
LoRa.setSpreadingFactor(12);      // Highest range setting
LoRa.setSignalBandwidth(125E3);   // 125 kHz bandwidth
LoRa.setCodingRate4(8);           // Highest error correction
LoRa.setSyncWord(0x34);           // Private network identifier
LoRa.enableCrc();                 // Enable CRC checking
```

### Parameter Analysis

| Parameter | Value | Impact | Trade-off |
|-----------|-------|---------|-----------|
| **Spreading Factor** | 12 | Max range (~10-15km) | Slowest data rate |
| **Bandwidth** | 125 kHz | Good range/speed balance | Standard for 433MHz |
| **Coding Rate** | 4/8 | Maximum error correction | 50% overhead |
| **Sync Word** | 0x34 | Private network isolation | Prevents interference |

## Range and Performance

### Theoretical Range

- **Line of sight**: Up to 15km
- **Urban environment**: 2-5km
- **Indoor/obstacles**: 0.5-2km

### Data Rate Calculation

```
Data Rate = SF × BW × CR
Where:
- SF = Spreading Factor (12)
- BW = Bandwidth (125 kHz)
- CR = Coding Rate (4/8)

Effective Rate = 125000 × (4/8) × (1/4096) ≈ 15.26 bps
```

### Time on Air

For a typical message (32 bytes encrypted):
```
ToA = Preamble + Header + Payload
    = 8 symbols + 4.25 symbols + payload symbols
    ≈ 2.5 seconds per message
```

## Message Format

### Path Message Structure

```
Format: "PATH,<lat>,<lon>,<heading>,<packetNo>"
Example: "PATH,40.123456,-74.654321,180,42"
```

**Fields:**
- `PATH`: Message type identifier
- `lat`: Latitude (6 decimal places, ±90.000000)
- `lon`: Longitude (6 decimal places, ±180.000000)
- `heading`: Compass heading (0-359 degrees)
- `packetNo`: Sequential packet number

### Obstacle Message Structure

```
Format: "OBS,<lat>,<lon>,<heading>,<distance>,<packetNo>"
Example: "OBS,40.123456,-74.654321,180,25.50,43"
```

**Fields:**
- `OBS`: Message type identifier
- `lat`: Latitude of obstacle detection
- `lon`: Longitude of obstacle detection
- `heading`: Direction robot was facing
- `distance`: Distance to obstacle (cm, 2 decimal places)
- `packetNo`: Sequential packet number

## Advanced Configuration

### Frequency Selection

```cpp
LoRa.begin(433E6);  // 433 MHz ISM band
```

**Alternative Frequencies:**
- **868 MHz**: Europe ISM band
- **915 MHz**: North America ISM band
- **433 MHz**: Global ISM band (chosen for maximum compatibility)

### Power Settings

```cpp
LoRa.setTxPower(20);  // Maximum power (20 dBm)
```

**Power Levels:**
- **20 dBm**: Maximum range, highest power consumption
- **17 dBm**: Good range, moderate power
- **14 dBm**: Reduced range, lower power consumption

### Sync Word Implementation

```cpp
LoRa.setSyncWord(0x34);
```

**Purpose:**
- Creates private network
- Prevents interference from other LoRa devices
- Filters out unwanted packets at hardware level

## Error Correction and Reliability

### Built-in Error Correction

The coding rate 4/8 provides:
- **50% redundancy**: Each bit transmitted twice
- **Error detection**: Can detect multiple bit errors
- **Error correction**: Can correct single bit errors per symbol

### CRC Validation

```cpp
LoRa.enableCrc();
```

**Benefits:**
- **Packet integrity**: Detects transmission errors
- **Automatic rejection**: Corrupted packets discarded
- **Reliability**: Ensures data accuracy

### Packet Sequence Numbers

```cpp
String msg = "PATH,lat,lon,heading," + String(packetNo++);
```

**Purpose:**
- **Duplicate detection**: Identify repeated packets
- **Ordering**: Maintain chronological sequence
- **Loss detection**: Identify missing packets

## Transmission Timing

### Interval Control

```cpp
constexpr unsigned long PATH_INTERVAL = 1000;  // 1 second
constexpr unsigned long OBS_INTERVAL = 1000;   // 1 second
```

**Timing Strategy:**
- **Path messages**: Every 1 second when GPS valid
- **Obstacle messages**: Every 1 second when obstacle detected
- **Prevents flooding**: Maintains network stability

### Collision Avoidance

```cpp
if (millis() - lastPathSent > PATH_INTERVAL) {
    sendMessage(msg);
    lastPathSent = millis();
}
```

**Implementation:**
- **Time-based**: Prevents rapid successive transmissions
- **Type-specific**: Separate timing for path vs obstacle
- **Non-blocking**: Doesn't halt other operations

## Security Integration

### Encryption Layer

```cpp
// In sendMessage():
byte cipher[total_len];
for (int i = 0; i < total_len; i += 16) {
    aes.encryptBlock(cipher + i, padded_msg + i);
}
```

**Security Features:**
- **AES-128 encryption**: Applied before transmission
- **Block cipher**: 16-byte blocks
- **Transparent**: No changes to message format

### Authentication

Current implementation relies on:
- **Shared key**: Only devices with correct key can decrypt
- **Sync word**: Hardware-level filtering
- **Message format**: Structured data validation

## Network Topology

### Point-to-Point Communication

```
[Robot/Mapper] --LoRa--> [Base Station/Receiver]
```

**Characteristics:**
- **Simplex**: One-way communication (robot to base)
- **Star topology**: Multiple robots to single base
- **No mesh**: Direct communication only

### Multi-Robot Support

```cpp
// Each robot has unique sync word or encryption key
LoRa.setSyncWord(0x34 + robotID);
```

**Scaling Options:**
- **Frequency division**: Different robots use different frequencies
- **Time division**: Robots transmit at different intervals
- **Code division**: Different sync words or encryption keys

## Performance Monitoring

### Signal Quality Metrics

```cpp
int rssi = LoRa.packetRssi();
float snr = LoRa.packetSnr();
```

**RSSI (Received Signal Strength Indicator):**
- **Range**: -120 to 0 dBm
- **Good signal**: > -100 dBm
- **Weak signal**: < -110 dBm

**SNR (Signal-to-Noise Ratio):**
- **Range**: -20 to +10 dB
- **Good quality**: > 0 dB
- **Acceptable**: > -10 dB

## Troubleshooting

### Common Issues

1. **No transmission**
   - **Check wiring**: Verify SPI connections, make sure at least 3 grounds are connected.
   - **Check frequency**: Ensure correct band for region
   - **Check power**: Verify adequate power supply

2. **Short range**
   - **Increase TX power**: Up to 20 dBm
   - **Check antenna**: Ensure proper antenna connection
   - **Optimize placement**: Elevate antenna, avoid obstacles

3. **Garbled messages**
   - **Check encryption**: Verify matching keys
   - **Check CRC**: Enable CRC validation
   - **Interference**: Try different frequency

### Debug Output

```cpp
Serial.println("LoRa Transmitter");
Serial.println("Frequency: " + String(LoRa.frequency()));
Serial.println("TX Power: " + String(LoRa.txPower()));
Serial.println("Sync Word: 0x" + String(LoRa.syncWord(), HEX));
```

## Advanced Features

### Adaptive Data Rate

```cpp
void adjustDataRate(int rssi) {
    if (rssi > -90) {
        LoRa.setSpreadingFactor(7);  // Faster rate
    } else if (rssi < -110) {
        LoRa.setSpreadingFactor(12); // Maximum range
    }
}
```

### Frequency Hopping

```cpp
int frequencies[] = {433E6, 434E6, 435E6};
int currentFreq = 0;

void hopFrequency() {
    currentFreq = (currentFreq + 1) % 3;
    LoRa.setFrequency(frequencies[currentFreq]);
}
```

## Future Enhancements

1. **Mesh networking**: Enable robot-to-robot communication
2. **Adaptive parameters**: Automatic SF/BW adjustment based on conditions
3. **Compression**: Reduce message size for faster transmission
4. **Retransmission**: Automatic retry on transmission failure

---

*This LoRa implementation prioritizes range and reliability over speed, making it ideal for long-distance navigation and mapping applications.*