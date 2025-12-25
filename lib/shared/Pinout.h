#pragma once

#include <Arduino.h>

namespace shared {
struct PwmPins {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

inline void setupOutput(uint8_t pin, uint8_t initialLevel = LOW) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, initialLevel);
}

inline void setupInputPullup(uint8_t pin) { pinMode(pin, INPUT_PULLUP); }

inline void writePwm(uint8_t pin, uint8_t value) { analogWrite(pin, value); }

inline void startSerial(unsigned long baud = 115200) {
  Serial.begin(baud);
}
}  // namespace shared
