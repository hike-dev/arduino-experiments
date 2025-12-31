# RGB LED (uno-rgb-led)

## Что нужно из набора

- RGB светодиод
- 3 резистора 220Ω или 330Ω
- Провода

## Подключение

## Иллюстрация (как на макетке)

![Breadboard wiring](../../docs/images/breadboard/uno_rgb_led.svg)

- R → D11 через резистор
- G → D10 через резистор
- B → D9 через резистор
- Общий вывод → GND (для common cathode)

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  RGB[RGB LED]:::module
  Rr[220/330Ω]:::part
  Rg[220/330Ω]:::part
  Rb[220/330Ω]:::part

  UNO -- D11 --> Rr --> RGB
  UNO -- D10 --> Rg --> RGB
  UNO -- D9 --> Rb --> RGB
  RGB -- common --> UNO

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#fdf2f8,stroke:#9d174d,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-rgb-led`

## Если цвета не такие

- У некоторых RGB другой порядок ножек — попробуй переставить провода R/G/B.
- Если RGB “общий плюс” (common anode), схема будет другой.
