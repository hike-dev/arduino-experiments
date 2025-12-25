/*
  Shift Register 74HC595 (uno-74hc595)

  Что нужно из набора:
    - 74HC595N
    - (желательно) 8 светодиодов + 8 резисторов 220/330Ω
    - Jumper Wires + макетная плата

  Управляющие пины (как в коде):
    DS (data)   -> D11
    SH_CP (clk) -> D12
    ST_CP (latch) -> D8

  Что увидишь:
    - "Бегущий" бит/огонёк по выходам Q0..Q7.

  Примечание:
    - У 74HC595 есть ещё пины питания (VCC/GND) и управляющие (OE/MR).
      Если делаешь реальную схему с LED, лучше добавить отдельную схему в README рядом со скетчем.
*/

#include <Arduino.h>

constexpr uint8_t kLatchPin = 8;
constexpr uint8_t kClockPin = 12;
constexpr uint8_t kDataPin = 11;

const uint8_t kPatterns[] = {
    B00000001, B00000010, B00000100, B00001000,
    B00010000, B00100000, B01000000, B10000000,
    B01000000, B00100000, B00010000, B00001000,
    B00000100, B00000010,
};

void writePattern(uint8_t pattern) {
  digitalWrite(kLatchPin, LOW);
  shiftOut(kDataPin, kClockPin, MSBFIRST, pattern);
  digitalWrite(kLatchPin, HIGH);
}

void setup() {
  pinMode(kLatchPin, OUTPUT);
  pinMode(kClockPin, OUTPUT);
  pinMode(kDataPin, OUTPUT);
}

void loop() {
  for (uint8_t pattern : kPatterns) {
    writePattern(pattern);
    delay(120);
  }
}
