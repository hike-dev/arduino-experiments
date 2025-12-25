/*
  Servo SG-90 (uno-servo-sg90)

  Что нужно из набора:
    - Сервопривод SG-90
    - Jumper Wires

  Подключение:
    Servo (обычно) -> Arduino Uno
    GND (коричн/чёрн) -> GND
    5V  (красный)     -> 5V (или внешний 5V источник)
    SIG (оранж/жёлт)  -> D9

  Что увидишь:
    - Серво будет плавно ходить от 0 до 180 градусов

  Важно:
    - Если серво дёргается или Arduino перезагружается, используй внешнее питание 5V
      и обязательно соедини земли (GND) вместе.
*/

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
