# Photoresistor / LDR (uno-photoresistor)

## Что нужно из набора

- Фоторезистор
- Резистор 10k
- Провода + макетная плата

## Подключение (делитель напряжения)

- 5V → LDR → (точка) → A0
- Из точки → резистор 10k → GND

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  LDR[Photoresistor]:::part
  R[10k]:::part

  UNO -- 5V --> LDR
  LDR -- node --> UNO
  UNO -- A0 --> UNO
  UNO -- node --> R
  R -- GND --> UNO

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-photoresistor`
- Монитор: `pio device monitor -b 115200`
