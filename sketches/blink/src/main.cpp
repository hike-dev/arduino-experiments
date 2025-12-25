#include <Arduino.h>
#include <shared/Timing.h>

constexpr uint8_t kLedPin = LED_BUILTIN;
IntervalTimer timer(500);

void setup() {
  pinMode(kLedPin, OUTPUT);
}

void loop() {
  if (timer.ready()) {
    digitalWrite(kLedPin, !digitalRead(kLedPin));
  }
}
