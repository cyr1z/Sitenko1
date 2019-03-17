#ifndef PCF8574_H
#define PCF8574_H

#include <Arduino.h>
#include <Wire.h>

class PCF8574 {
public:
  PCF8574(int address = 0x38); // default address, with A0, A1, and A2 all floating or grounded.
  void write(uint8_t pin, uint8_t state);
  void writeHigh(uint8_t pin);
  void writeLow(uint8_t pin);
  void writeAll(uint8_t state);

private:
  uint8_t _WRITE_ADDRESS = 0x38; // defaults
  uint8_t _READ_ADDRESS  = 0x39;
  uint8_t pin_state      = 0xFF; // power-on state

  void writeCallback();
  void sendInstructionToChip(uint8_t address, uint8_t instruction);
};

#endif /* end of include guard: PCF8574_H */
