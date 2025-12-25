/*
  Joystick (uno-joystick)

  Что нужно из набора:
    - Джойстик-модуль
    - Jumper Wires

  Подключение:
    Joystick -> Arduino Uno
    VCC      -> 5V
    GND      -> GND
    VRx      -> A0
    VRy      -> A1
    SW       -> D2 (в этом скетче включена внутренняя подтяжка pull-up)

  Что увидишь:
    - В Serial Monitor: X, Y и состояние кнопки.
*/

#include <Arduino.h>
#include <shared/Pinout.h>

constexpr uint8_t kXPin = A0;
constexpr uint8_t kYPin = A1;
constexpr uint8_t kButtonPin = 2;
constexpr unsigned long kPrintEveryMs = 200;

unsigned long lastPrint = 0;

void setup() {
  shared::startSerial();
  shared::setupInputPullup(kButtonPin);
}

void loop() {
  const int x = analogRead(kXPin);
  const int y = analogRead(kYPin);
  const bool pressed = digitalRead(kButtonPin) == LOW;

  const unsigned long now = millis();
  if (now - lastPrint >= kPrintEveryMs) {
    lastPrint = now;
    Serial.print(F("X:"));
    Serial.print(x);
    Serial.print(F(" Y:"));
    Serial.print(y);
    Serial.print(F(" Btn:"));
    Serial.println(pressed ? "pressed" : "open");
  }
}
