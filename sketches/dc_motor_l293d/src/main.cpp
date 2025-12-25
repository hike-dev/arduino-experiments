#include <Arduino.h>

constexpr uint8_t kEnablePin = 5;  // must be PWM
constexpr uint8_t kIn1 = 8;
constexpr uint8_t kIn2 = 7;

void setDirectionForward() {
  digitalWrite(kIn1, HIGH);
  digitalWrite(kIn2, LOW);
}

void setDirectionReverse() {
  digitalWrite(kIn1, LOW);
  digitalWrite(kIn2, HIGH);
}

void setSpeed(uint8_t speed) { analogWrite(kEnablePin, speed); }

void setup() {
  pinMode(kEnablePin, OUTPUT);
  pinMode(kIn1, OUTPUT);
  pinMode(kIn2, OUTPUT);
  setDirectionForward();
}

void loop() {
  for (uint8_t speed = 0; speed <= 255; speed += 15) {
    setSpeed(speed);
    delay(80);
  }
  delay(500);
  setDirectionReverse();
  for (uint8_t speed = 0; speed <= 255; speed += 15) {
    setSpeed(speed);
    delay(80);
  }
  delay(500);
  setDirectionForward();
}
