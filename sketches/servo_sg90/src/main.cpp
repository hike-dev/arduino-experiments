#include <Arduino.h>
#include <Servo.h>
#include <shared/Timing.h>

constexpr uint8_t kServoPin = 9;
constexpr uint8_t kMinAngle = 0;
constexpr uint8_t kMaxAngle = 180;
constexpr uint8_t kStep = 5;

Servo servo;
IntervalTimer timer(25);
int angle = kMinAngle;
int delta = kStep;

void setup() {
  servo.attach(kServoPin);
}

void loop() {
  if (!timer.ready()) {
    return;
  }
  angle += delta;
  if (angle >= kMaxAngle || angle <= kMinAngle) {
    delta = -delta;
    angle = constrain(angle, kMinAngle, kMaxAngle);
  }
  servo.write(angle);
}
