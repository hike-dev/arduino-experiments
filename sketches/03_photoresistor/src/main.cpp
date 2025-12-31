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
constexpr uint8_t kIndicatorLedPin = LED_BUILTIN;

// Подстрой под свою комнату/датчик:
// - меньше значения  -> темнее
// - больше значения  -> светлее
constexpr int kDarkThresholdRaw = 450;
constexpr int kHysteresisRaw = 25;
constexpr unsigned long kPrintEveryMs = 500;

unsigned long lastPrint = 0;
bool isDark = false;

void setup() {
  shared::startSerial();
  pinMode(kIndicatorLedPin, OUTPUT);
  digitalWrite(kIndicatorLedPin, LOW);
}

void loop() {
  const int raw = analogRead(kLdrPin);

  // Явная индикация: встроенный LED горит, когда темно.
  if (isDark) {
    if (raw > (kDarkThresholdRaw + kHysteresisRaw)) {
      isDark = false;
      digitalWrite(kIndicatorLedPin, LOW);
    }
  } else {
    if (raw < (kDarkThresholdRaw - kHysteresisRaw)) {
      isDark = true;
      digitalWrite(kIndicatorLedPin, HIGH);
    }
  }

  const unsigned long now = millis();
  if (now - lastPrint >= kPrintEveryMs) {
    lastPrint = now;
    Serial.print(F("LDR raw: "));
    Serial.println(raw);
  }
  delay(10);
}
