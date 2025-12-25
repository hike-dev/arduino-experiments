# Joystick (uno-joystick)

## Что нужно из набора

- Джойстик-модуль
- Провода

## Подключение

- VCC → 5V
- GND → GND
- VRx → A0
- VRy → A1
- SW → D2 (в этом скетче включена внутренняя подтяжка pull-up)

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  J[Joystick]:::module

  UNO -- 5V --> J
  UNO -- GND --> J
  UNO -- A0 (VRx) --> J
  UNO -- A1 (VRy) --> J
  UNO -- D2 (SW) --> J

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#fef9c3,stroke:#854d0e,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-joystick`
- Монитор: `pio device monitor -b 115200`
