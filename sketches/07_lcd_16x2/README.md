# LCD 16x2 (uno-lcd-16x2)

## Что нужно из набора

- LCD 16×2 (параллельный)
- Потенциометр (контраст)
- Провода + макетная плата

## Подключение (как в коде)

- RS → D12
- E → D11
- D4 → D5
- D5 → D4
- D6 → D3
- D7 → D2

## Контраст (V0/VO)

Контраст LCD настраивается потенциометром:

- один край потенциометра → 5V
- другой край → GND
- середина → V0/VO на LCD

Этот скетч дополнительно читает потенциометр на A0, поэтому можно сделать перемычку:

- середина потенциометра → A0

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  LCD[LCD 16x2]:::module
  POT[Potentiometer]:::part

  UNO -- D12 (RS) --> LCD
  UNO -- D11 (E) --> LCD
  UNO -- D5 (D4) --> LCD
  UNO -- D4 (D5) --> LCD
  UNO -- D3 (D6) --> LCD
  UNO -- D2 (D7) --> LCD

  UNO -- 5V --> POT
  UNO -- GND --> POT
  POT -- wiper --> LCD
  POT -- wiper --> UNO

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#fff7ed,stroke:#9a3412,color:#111827;
  classDef part fill:#fefce8,stroke:#854d0e,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-lcd-16x2`

## Если экран пустой

- Покрути потенциометр: контраст — самая частая причина.
