#include <Arduino.h>
#include <LedControl.h>

// DIN, CLK, CS, number of devices
LedControl matrix(12, 11, 10, 1);

const byte kSmiley[8] = {
    B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100,
};

const byte kArrow[8] = {
    B00011000,
    B00011000,
    B01111110,
    B00111100,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
};

void drawImage(const byte image[8]) {
  for (uint8_t row = 0; row < 8; row++) {
    matrix.setRow(0, row, image[row]);
  }
}

void setup() {
  matrix.shutdown(0, false);
  matrix.setIntensity(0, 8);
  matrix.clearDisplay(0);
}

void loop() {
  drawImage(kSmiley);
  delay(800);
  drawImage(kArrow);
  delay(800);
}
