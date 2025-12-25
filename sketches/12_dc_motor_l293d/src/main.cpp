/*
  DC Motor + L293D (uno-dc-motor-l293d)

  Что нужно из набора:
    - DC мотор
    - L293D
    - Адаптер 9V (для питания мотора) и провода

  Подключение (логика управления как в коде):
    ENA (speed, PWM) -> D5
    IN1              -> D8
    IN2              -> D7

  Мотор:
    OUT1/OUT2 (L293D) -> два вывода мотора

  Питание (важно!):
    - Логика драйвера питается от 5V (Vcc1)
    - Питание мотора (Vmotor) берём от 9V адаптера
    - GND у Arduino и GND у питания мотора должны быть соединены

  Что увидишь:
    - Мотор разгоняется и меняет направление.
*/

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
