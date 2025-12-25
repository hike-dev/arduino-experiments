# IR Receiver (uno-ir-receiver)

## Что нужно из набора

- ИК‑приёмник
- ИК‑пульт
- Провода

## Подключение

- VCC → 5V
- GND → GND
- SIGNAL → D7

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  IR[IR receiver]:::module
  RMT[Remote]:::part

  UNO -- 5V --> IR
  UNO -- GND --> IR
  UNO -- D7 (signal) --> IR
  RMT -. IR light .-> IR

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#f8fafc,stroke:#334155,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-ir-receiver`
- Монитор: `pio device monitor -b 115200`
