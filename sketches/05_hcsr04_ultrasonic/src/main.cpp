/*
  HC-SR04 Ultrasonic (uno-hcsr04)

  Что нужно из набора:
    - HC-SR04
    - Jumper Wires + (по желанию) макетная плата

  Подключение:
    HC-SR04  ->  Arduino Uno
    VCC      ->  5V
    GND      ->  GND
    TRIG     ->  D7
    ECHO     ->  D6

  Что увидишь:
    - Открой Serial Monitor 115200 и увидишь "Distance cm: ..."

  Важно:
    - Для Arduino Uno (5V) ECHO обычно можно подключать напрямую.
    - Для плат 3.3V обычно нужен делитель на ECHO.
*/

#include <Arduino.h>

constexpr uint8_t kTrigPin = 7;
constexpr uint8_t kEchoPin = 6;

float measureCm() {
  digitalWrite(kTrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(kTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(kTrigPin, LOW);

  const unsigned long duration = pulseIn(kEchoPin, HIGH, 30000);
  return (duration * 0.0343F) / 2.0F;
}

void setup() {
  pinMode(kTrigPin, OUTPUT);
  pinMode(kEchoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  const float distance = measureCm();
  Serial.print(F("Distance cm: "));
  Serial.println(distance, 2);
  delay(250);
}
