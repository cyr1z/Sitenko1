# PCF8574 Arduino library

A library for controlling TI PCF8574 GPIO expander chips over I2C from an Arduino-compatible device.

*Currently only supports writing to the chip*

### Available functions are:
* Main constructor, with the default address having the address pins either floating or grounded.    
      PCF8574(int address = 0x38);

* The barebones writing function.
      void write(uint8_t pin, uint8_t state);

* The writeAll functions are fairly self explanatory.
      void writeAll(uint8_t state);
      void writeAllLow();
      void writeAllHigh();


* Here's a more applicable example:
      PCF8574 pcf;        // create an object for the chip, with default address 0x38
      pcf.write(0, LOW);  // turn on an LED via low-side switching       
                          // LED is connected to VCC, chip between LED and ground
      delay(1000);        // wait one second
      pcf.write(0, HIGH); // turn it back off



### Contributions are welcome - code under GPLV3

*Questions should be addressed to jkillelea@protonmail.ch*
