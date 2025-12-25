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
