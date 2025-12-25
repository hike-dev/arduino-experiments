/*
  RGB LED (uno-rgb-led)

  Что нужно из набора:
    - RGB светодиод
    - 3 резистора 220Ω или 330Ω
    - Jumper Wires

  Подключение (как в коде):
    R -> D11 через резистор
    G -> D10 через резистор
    B -> D9  через резистор
    Общая ножка RGB (обычно самая длинная, если common cathode) -> GND

  Что увидишь:
    - Плавные переливы цветов.

  Если цвета странные:
    - Возможно у RGB другой порядок ножек (поменяй местами провода R/G/B).
    - Возможно RGB "общий плюс" (common anode) — тогда нужна другая схема.
*/

#include <Arduino.h>
#include <shared/Pinout.h>

constexpr shared::PwmPins kRgb{11, 10, 9};
constexpr uint8_t kStep = 5;

struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

const Color kPalette[] = {
    {255, 0, 0},   {255, 128, 0}, {255, 255, 0}, {0, 255, 0},
    {0, 255, 255}, {0, 0, 255},   {128, 0, 255}, {255, 255, 255},
};

void applyColor(const Color &c) {
  shared::writePwm(kRgb.r, c.r);
  shared::writePwm(kRgb.g, c.g);
  shared::writePwm(kRgb.b, c.b);
}

void setup() {
  shared::setupOutput(kRgb.r);
  shared::setupOutput(kRgb.g);
  shared::setupOutput(kRgb.b);
}

void loop() {
  static size_t index = 0;
  static uint8_t level = 0;
  const Color current = kPalette[index % (sizeof(kPalette) / sizeof(Color))];
  Color faded{static_cast<uint8_t>((current.r * level) / 255),
              static_cast<uint8_t>((current.g * level) / 255),
              static_cast<uint8_t>((current.b * level) / 255)};
  applyColor(faded);
  level = level + kStep;
  if (level == 0) {
    index++;
  }
  delay(20);
}
