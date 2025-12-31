/*
  LCD 16x2 (uno-lcd-16x2)

  Что нужно из набора:
    - LCD 16x2 + I2C-платка ("backpack", 4 пина: GND/VCC/SDA/SCL)
    - Провода + макетная плата

  Подключение (I2C, 4 провода):
    LCD GND -> GND
    LCD VCC -> 5V
    LCD SDA -> A4 (SDA)
    LCD SCL -> A5 (SCL)

  Контраст:
    - Обычно регулируется маленьким подстроечником на I2C-платке.

  Дополнительно (не обязательно):
    - Можно подключить потенциометр к A0 (wiper -> A0, края -> 5V/GND),
      тогда на экране будет показываться значение A0.

  Что увидишь:
    - На первой строке "LCD ready", на второй строке "Pot: <число>".
*/

#include <Arduino.h>
#include <Wire.h>

#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;
constexpr uint8_t kPotPin = A0;

void setup() {
  Serial.begin(115200);

  const int status = lcd.begin(16, 2);
  if (status != 0) {
    // Most common causes: wrong wiring (SDA/SCL swapped), no backpack, bad power.
    Serial.print(F("LCD begin() failed, status="));
    Serial.println(status);
    for (;;) {
      delay(1000);
    }
  }

  lcd.print("LCD ready");
}

void loop() {
  const int pot = analogRead(kPotPin);
  lcd.setCursor(0, 1);
  lcd.print("Pot:     ");
  lcd.setCursor(5, 1);
  lcd.print(pot);
  delay(250);
}
