#include <Arduino.h>
#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
constexpr uint8_t kContrastPotPin = A0;

void setup() {
  lcd.begin(16, 2);
  lcd.print("LCD ready");
}

void loop() {
  const int pot = analogRead(kContrastPotPin);
  lcd.setCursor(0, 1);
  lcd.print("Pot:     ");
  lcd.setCursor(5, 1);
  lcd.print(pot);
  delay(250);
}
