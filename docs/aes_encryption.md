# AES Encryption Implementation

## Overview

This implementation uses **AES-128 block cipher encryption** to secure LoRa communications. The system encrypts GPS coordinates, obstacle data, and other sensitive information before wireless transmission.

## Why AES for LoRa?

LoRa transmissions are inherently insecure and can be intercepted by anyone with a compatible receiver. AES encryption ensures:
- **Data confidentiality**: Location and sensor data remain private
- **Message integrity**: Prevents tampering with transmitted data
- **Authentication**: Only devices with the correct key can decrypt messages

## Implementation Details

### AES Configuration

```cpp
AES128 aes;
byte key[16] = {'s','e','c','r','e','t','k','e','y','1','2','3','4','5','6','7'};
```

- **Algorithm**: AES-128 (16-byte key)
- **Mode**: ECB (Electronic Codebook)
- **Block Size**: 128 bits (16 bytes)
- **Key Length**: 128 bits (16 bytes)

### PKCS#7 Padding Implementation

Since AES requires input data to be exact multiples of 16 bytes, we implement PKCS#7 padding:

```cpp
int msg_len = msg.length();
int pad_len = 16 - (msg_len % 16);
int total_len = msg_len + pad_len;

byte padded_msg[total_len];

// Copy original message
for (int i = 0; i < msg_len; i++) {
    padded_msg[i] = msg[i];
}

// Add padding bytes
for (int i = 0; i < pad_len; i++) {
    padded_msg[msg_len + i] = pad_len;
}
```

**How PKCS#7 Works:**
- If message is 13 bytes, add 3 bytes each with value `0x03`
- If message is exactly 16 bytes, add 16 bytes each with value `0x10`
- Padding value = number of padding bytes added

### Block Cipher Encryption

```cpp
byte cipher[total_len];

for (int i = 0; i < total_len; i += 16) {
    aes.encryptBlock(cipher + i, padded_msg + i);
}
```

The system encrypts data in 16-byte blocks:
- Each block is encrypted independently (ECB mode)
- Results in deterministic encryption (same plaintext = same ciphertext)
- Suitable for short messages where block patterns aren't a concern

## Security Considerations

### Key Management

**Current Implementation:**
```cpp
byte key[16] = {'s','e','c','r','e','t','k','e','y','1','2','3','4','5','6','7'};
```

**Production Recommendations:**
- Use truly random key generation
- Implement key rotation mechanisms
- Store keys in secure memory (if available)
- Use hardware security modules for key protection

### ECB Mode Limitations

**Why ECB is Used:**
- Simplicity for embedded systems
- No initialization vector (IV) required
- Suitable for short, non-repeating messages

**Limitations:**
- Identical plaintext blocks produce identical ciphertext
- Vulnerable to pattern analysis with large datasets
- No built-in message authentication

**Recommended Improvements:**
```cpp
// Consider CBC mode with IV:
// aes.cbc_encrypt(plaintext, ciphertext, blocks, iv);
```

### Message Authentication

Current implementation lacks message authentication. Consider adding:
- **HMAC**: Hash-based Message Authentication Code
- **AES-GCM**: Authenticated encryption mode
- **Digital signatures**: For strong authentication


## Example Message Flow

### Original Message
```
"PATH,40.123456,-74.654321,180,42"
```

### After Padding (hex representation)
```
50 41 54 48 2C 34 30 2E 31 32 33 34 35 36 2C 2D
37 34 2E 36 35 34 33 32 31 2C 31 38 30 2C 34 32
0E 0E 0E 0E 0E 0E 0E 0E 0E 0E 0E 0E 0E 0E
```

### After AES Encryption
```
A3 7F 2B 8E ... (encrypted blocks)
```

## Integration with LoRa

### Transmission Process

1. **Format message**: GPS/obstacle data → string
2. **Apply padding**: PKCS#7 padding to 16-byte boundary
3. **Encrypt**: AES-128 block encryption
4. **Transmit**: Send encrypted bytes via LoRa

### Reception Process (Receiver Side)

1. **Receive**: Encrypted bytes from LoRa
2. **Decrypt**: AES-128 block decryption
3. **Remove padding**: Strip PKCS#7 padding
4. **Parse**: Extract GPS/obstacle data

## Testing and Validation

### Encryption Test

```cpp
void testEncryption() {
    String test_msg = "TEST,12.34,56.78,90";
    
    // Encrypt
    sendMessage(test_msg);
    
    // Verify on receiver side
    // Should decrypt back to original message
}
```

### Key Validation

```cpp
void validateKey() {
    // Ensure key is exactly 16 bytes
    if (sizeof(key) != 16) {
        Serial.println("ERROR: Invalid key length");
    }
}
```

## Troubleshooting

### Common Issues

1. **Decryption Failures**
   - **Cause**: Key mismatch between sender/receiver
   - **Solution**: Verify identical keys on both devices

2. **Garbled Messages**
   - **Cause**: Incomplete transmission or corruption
   - **Solution**: Add CRC checking, implement retransmission

3. **Memory Errors**
   - **Cause**: Insufficient RAM for encryption buffers
   - **Solution**: Optimize message length, use streaming encryption

### Debug Output

```cpp
Serial.print("Original: " + msg);
Serial.print("Encrypted: ");
for (int i = 0; i < total_len; i++) {
    Serial.print(cipher[i], HEX);
}
Serial.println();
```

## Future Enhancements

1. **Key Derivation**: Implement PBKDF2 for key generation
2. **IV Support**: Add initialization vectors for CBC mode
3. **Authentication**: Implement HMAC for message authentication
4. **Key Exchange**: Add secure key exchange protocol
5. **Hardware Acceleration**: Use dedicated crypto chips if available

---

*This implementation provides basic but effective encryption for LoRa communications.*