#include "PCF8574.h"

// PUBLIC
// CONSTRUCTOR
PCF8574::PCF8574(int address) {
  _WRITE_ADDRESS = address;
  _READ_ADDRESS  = address + 1;
  Wire.begin();
}

void PCF8574::write(uint8_t pin, uint8_t state) {
  // note that digitalWite in Arduino.h takes uint8_t's for HIGH and LOW
  switch (state) {
    case HIGH:
      writeHigh(pin);
      break;
    case LOW:
      writeLow(pin);
      break;
  }
}

inline void PCF8574::writeHigh(uint8_t pin) {
  pin_state |= (1 << pin); // OR that bit with 1 (turn it to 1).
  writeCallback();         // All the other bits are OR'ed with zero (so not affected)
}

inline void PCF8574::writeLow(uint8_t pin) {
  pin_state &= ~(1 << pin); // AND that bit with 0 (turn it to 0)
  writeCallback();          // All the other bits are AND'ed with 1 (so not affected)
}

void PCF8574::writeAll(uint8_t state) {
  switch (state) {
    case HIGH:
      pin_state = 0xFF;
      break;
    case LOW:
      pin_state = 0x00;
      break;
  }
  writeCallback();
}

// PRIVATE
inline void PCF8574::writeCallback() {
  sendInstructionToChip(_WRITE_ADDRESS, pin_state);
}

void PCF8574::sendInstructionToChip(uint8_t address, uint8_t instruction) {
  Wire.beginTransmission(address);
  Wire.write(instruction);
  Wire.endTransmission();
}
