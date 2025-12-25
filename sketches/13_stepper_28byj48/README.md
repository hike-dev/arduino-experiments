# Stepper 28BYJ-48 + ULN2003 (uno-stepper-28byj48)

## Что нужно из набора

- Шаговый двигатель 28BYJ-48
- Драйвер ULN2003
- Провода

## Подключение (как в коде)

- IN1 → D8
- IN2 → D10
- IN3 → D9
- IN4 → D11
- VCC → 5V
- GND → GND

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  ULN[ULN2003 driver]:::module
  ST[28BYJ-48 stepper]:::part

  UNO -- D8 (IN1) --> ULN
  UNO -- D10 (IN2) --> ULN
  UNO -- D9 (IN3) --> ULN
  UNO -- D11 (IN4) --> ULN
  UNO -- 5V --> ULN
  UNO -- GND --> ULN

  ULN -- motor cable --> ST

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#ecfccb,stroke:#3f6212,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-stepper-28byj48`

## SVG-схема

- Упрощённая картинка: ../../docs/images/uln2003_stepper.svg
