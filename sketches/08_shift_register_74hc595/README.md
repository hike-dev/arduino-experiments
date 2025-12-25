# 74HC595 Shift Register (uno-74hc595)

## Что нужно из набора

- 74HC595N
- Провода
- (Рекомендуется) 8 светодиодов + 8 резисторов 220/330Ω

## Управляющие пины (как в коде)

- DS (data) → D11
- SH_CP (clock) → D12
- ST_CP (latch) → D8

```mermaid
flowchart LR
  UNO[Arduino Uno]:::board
  SR[74HC595]:::module
  LEDS[LEDs + resistors]:::part

  UNO -- D11 (DS) --> SR
  UNO -- D12 (SH_CP) --> SR
  UNO -- D8 (ST_CP) --> SR
  UNO -- 5V --> SR
  UNO -- GND --> SR

  SR -- Q0..Q7 --> LEDS

  classDef board fill:#f3f4f6,stroke:#111827,color:#111827;
  classDef module fill:#f1f5f9,stroke:#0f172a,color:#111827;
  classDef part fill:#eef2ff,stroke:#3730a3,color:#111827;
```

## Проверка

- Залить: `pio run -t upload -e uno-74hc595`

## Примечание

74HC595 имеет дополнительные пины (OE/MR), которые обычно фиксируют в нужные уровни. В этом репозитории скетч показывает принцип работы “сдвигового регистра”; если хочешь — добавлю подробную распиновку для макетки.
