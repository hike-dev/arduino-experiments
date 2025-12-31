# HC-SR04 Ultrasonic (uno-hcsr04)

## Что нужно из набора

- HC-SR04
- Провода (jumper wires)
- Макетная плата (по желанию)

## Подключение

## Иллюстрация (как на макетке)

![Breadboard wiring](../../docs/images/breadboard/uno_hcsr04.svg)

- VCC → 5V
- GND → GND
- TRIG → D7
- ECHO → D6

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  HCSR[HC-SR04]:::module

  UNO -- 5V --> HCSR
  UNO -- GND --> HCSR
  UNO -- D7 (TRIG) --> HCSR
  HCSR -- ECHO --> UNO

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-hcsr04`
- Открыть монитор: `pio device monitor -b 115200`

## Важно

- Для Arduino Uno (5V) ECHO обычно можно подключать напрямую.
- Для плат 3.3V часто нужен делитель на ECHO.
