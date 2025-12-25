# MAX7219 + 8x8 Matrix (uno-max7219-matrix)

## Что нужно из набора

- MAX7219 модуль
- Матрица 8×8
- Провода

## Подключение (как в коде)

- VCC → 5V
- GND → GND
- DIN → D12
- CLK → D11
- CS → D10

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  MAX[MAX7219]:::module
  MAT[8x8 matrix]:::part

  UNO -- 5V --> MAX
  UNO -- GND --> MAX
  UNO -- D12 (DIN) --> MAX
  UNO -- D11 (CLK) --> MAX
  UNO -- D10 (CS) --> MAX

  MAX -- drives --> MAT

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#e0f2fe,stroke:#075985,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-max7219-matrix`
