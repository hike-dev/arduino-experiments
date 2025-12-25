# Servo SG-90 (uno-servo-sg90)

## Что нужно из набора

- Сервопривод SG-90
- Провода

## Подключение

Обычно цвета такие:

- GND: коричневый/чёрный → GND
- +5V: красный → 5V (или внешний 5V)
- SIGNAL: оранжевый/жёлтый/белый → D9

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  SERVO[SG-90]:::module

  UNO -- GND --> SERVO
  UNO -- 5V --> SERVO
  UNO -- D9 (signal) --> SERVO

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#ecfeff,stroke:#155e75,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-servo-sg90`

## Важно

- Если серво дёргается или Arduino перезагружается — используй внешний 5V источник для серво.
- При внешнем питании обязательно соедини земли: GND источника и GND Arduino.
