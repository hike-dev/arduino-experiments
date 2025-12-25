/*
  Stepper 28BYJ-48 + ULN2003 (uno-stepper-28byj48)

  Что нужно из набора:
    - Шаговый двигатель 28BYJ-48
    - Драйвер ULN2003
    - Jumper Wires

  Подключение:
    ULN2003 -> Arduino Uno
    VCC     -> 5V
    GND     -> GND
    IN1     -> D8
    IN2     -> D10
    IN3     -> D9
    IN4     -> D11

  Мотор:
    - Вставь штекер мотора в разъём на плате ULN2003.

  Что увидишь:
    - Шаговый двигатель будет равномерно вращаться.
*/

#include <Arduino.h>
#include <Stepper.h>
#include <shared/Timing.h>

constexpr int kStepsPerRevolution = 2048;  // 28BYJ-48 with ULN2003
Stepper stepper(kStepsPerRevolution, 8, 10, 9, 11);
IntervalTimer timer(10);
int stepCounter = 0;

void setup() {
  stepper.setSpeed(10);  // rpm
}

void loop() {
  if (!timer.ready()) {
    return;
  }
  stepper.step(1);
  stepCounter++;
  if (stepCounter >= kStepsPerRevolution) {
    stepCounter = 0;
  }
}
