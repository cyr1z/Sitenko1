// Copyright Jacob Killelea <jkillelea@protonmail.ch>
// This example code and the associated libraries are licensed under the GNU GPLV3
/*
 * For this code to run properly, pins A0, A1, and A2 on the PCF8574 should either be directly
 * grounded or left to float.
 * A LED and associated resistor should be placed in series so that they are
 * directly attached to VCC on one end, and the PCF8574 chip on the other.
 * When the PCF8574 pins are "high," they do not allow current to pass through.
 * When the pins are "low," current flows freely to ground and the LEDs light up.
 */

#include <Wire.h>
#include <PCF8574.h>

PCF8574 pcf; // create new object from PCF8574.h library, with default address 0x38

void setup() {
  pcf.writeAll(HIGH); // turns all the LEDs off.
}

void loop() {
  for(int i = 0; i < 8; i++) {
    pcf.write(i, LOW); // briefly toggle each LED on
    delay(50);
    pcf.write(i, HIGH);
  }
}
