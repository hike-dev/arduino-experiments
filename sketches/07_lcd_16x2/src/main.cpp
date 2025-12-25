/*
  LCD 16x2 (uno-lcd-16x2)

  Что нужно из набора:
    - LCD 16x2 (параллельный)
    - Потенциометр (для контраста)
    - Jumper Wires + макетная плата

  Подключение (сигнальные пины как в коде ниже):
    LCD RS -> D12
    LCD E  -> D11
    LCD D4 -> D5
    LCD D5 -> D4
    LCD D6 -> D3
    LCD D7 -> D2

  Контраст (самое важное, иначе экран может быть пустой):
    Pot end 1  -> 5V
    Pot end 2  -> GND
    Pot middle -> LCD V0/VO

  Дополнительно для этого скетча:
    - Можно соединить Pot middle ещё и с A0, чтобы на экране показывалось значение.

  Что увидишь:
    - На первой строке "LCD ready", на второй строке "Pot: <число>".
*/

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
