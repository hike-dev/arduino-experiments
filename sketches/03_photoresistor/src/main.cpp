/*
  Photoresistor / LDR (uno-photoresistor)

  Что нужно из набора:
    - Фоторезистор
    - Резистор 10k
    - Jumper Wires + макетная плата

  Подключение (делитель напряжения):
    5V ---[ LDR ]---+--- A0
                    |
                  [10k]
                    |
                   GND

  Что увидишь:
    - В Serial Monitor 115200: "LDR raw: <число>"
*/

#include <Arduino.h>
#include <shared/Pinout.h>

constexpr uint8_t kLdrPin = A0;
constexpr unsigned long kPrintEveryMs = 500;

unsigned long lastPrint = 0;

void setup() {
  shared::startSerial();
}

void loop() {
  const int raw = analogRead(kLdrPin);
  const unsigned long now = millis();
  if (now - lastPrint >= kPrintEveryMs) {
    lastPrint = now;
    Serial.print(F("LDR raw: "));
    Serial.println(raw);
  }
  delay(10);
}
