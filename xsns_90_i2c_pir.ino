#ifdef USE_I2C_PIR

#include <Wire.h>

#define I2C_PIR_ADDRESS 0x64  // I2C address of the PIR sensor

// Function prototypes
void I2CPIRInit(void);
uint8_t I2CPIRRead(void);

// Initialize the PIR sensor
void I2CPIRInit(void) {
  Wire.begin();  // Initialize I2C
}

// Read motion state from the PIR sensor
uint8_t I2CPIRRead(void) {
  Wire.requestFrom(I2C_PIR_ADDRESS, 1);  // Request 1 byte from PIR sensor
  if (Wire.available()) {
    return Wire.read();  // Return the motion state (1: motion, 0: no motion)
  }
  return 0xFF;  // Return 0xFF if no data received
}

// Tasmota integration
bool Xsns90(uint8_t function) {
  if (function == FUNC_INIT) {
    I2CPIRInit();
  } else if (function == FUNC_EVERY_SECOND) {
    uint8_t motionState = I2CPIRRead();
    if (motionState != 0xFF) {  // Valid data received
      if (motionState == 1) {
        AddLog(LOG_LEVEL_INFO, PSTR("PIR 0x64: Motion detected"));  // Corrected logging function
      } else {
        AddLog(LOG_LEVEL_INFO, PSTR("PIR 0x64: No motion"));  // Corrected logging function
      }
    } else {
      AddLog(LOG_LEVEL_ERROR, PSTR("PIR 0x64: Error reading I2C data"));  // Corrected logging function
    }
  }
  return true;
}

#endif  // USE_I2C_PIR
