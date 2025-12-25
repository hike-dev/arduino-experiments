# DC Motor + L293D (uno-dc-motor-l293d)

## Что нужно из набора

- Двигатель постоянного тока
- L293D
- Адаптер 9V (или батарейка) для питания мотора
- Провода + макетная плата

## Сигнальные пины (как в коде)

- ENA (PWM скорость) → D5
- IN1 (направление) → D8
- IN2 (направление) → D7

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  DRV[L293D]:::module
  M[DC Motor]:::part
  PWR[9V supply]:::part

  UNO -- D5 (ENA PWM) --> DRV
  UNO -- D8 (IN1) --> DRV
  UNO -- D7 (IN2) --> DRV

  UNO -- 5V (logic) --> DRV
  UNO -- GND --> DRV

  PWR -- +9V (Vmotor) --> DRV
  PWR -- GND --> DRV

  DRV -- OUT1 --> M
  DRV -- OUT2 --> M

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#fce7f3,stroke:#9d174d,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Важно (чтобы не перезагружалась Arduino)

- GND у Arduino и GND у питания мотора должны быть общими.
- Мотор нельзя питать напрямую от 5V пина Arduino.

## Проверка

- Залить: `pio run -t upload -e uno-dc-motor-l293d`

## SVG-схема

- Упрощённая картинка: ../../docs/images/l293d_dc_motor.svg
