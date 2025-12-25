# Arduino Uno R3 Starter Experiments

PlatformIO-based multi-sketch workspace targeting Arduino Uno R3. Each sketch lives under `sketches/<name>/src/main.cpp` with its own PlatformIO environment.

## Build and Upload
- Install PlatformIO Core (`pip install platformio`) or open with the VS Code PlatformIO extension.
- Build: `pio run -e uno-blink`
- Upload: `pio run -t upload -e uno-blink`
- Monitor (115200 baud unless noted): `pio device monitor -b 115200`
- Switch sketches by changing `-e` to the desired environment name (see below).

## Environments and Wiring
- `uno-blink`: uses `LED_BUILTIN`.
- `uno-rgb-led`: PWM pins R=11, G=10, B=9, common cathode to GND, current-limit resistors.
- `uno-photoresistor`: LDR to 5V, 10k to GND, midpoint to A0.
- `uno-hcsr04`: TRIG=7, ECHO=6 (add voltage divider for echo if needed), Vcc=5V, GND.
- `uno-servo-sg90`: signal=9, Vcc=5V, GND (power from adapter if servo chatters).
- `uno-stepper-28byj48`: ULN2003 IN1=8, IN2=10, IN3=9, IN4=11, Vcc=5V, GND.
- `uno-dc-motor-l293d`: ENA=5 (PWM), IN1=8, IN2=7, motor on OUT1/OUT2, external 9V supply to L293D Vmotor and GND tied to Uno.
- `uno-lcd-16x2`: LiquidCrystal RS=12, E=11, D4=5, D5=4, D6=3, D7=2, contrast pot wiper to A0 (or V0), ends to 5V/GND.
- `uno-joystick`: VRx=A0, VRy=A1, SW=2 with pull-up, Vcc=5V, GND.
- `uno-ir-receiver`: signal=7, Vcc=5V, GND. Uses IRremote library; monitor serial for decoded frames.
- `uno-mpu6050`: SDA=A4, SCL=A5, Vcc=5V, GND. Uses Adafruit MPU6050.
- `uno-max7219-matrix`: DIN=12, CLK=11, CS=10, Vcc=5V, GND. Uses LedControl.
- `uno-74hc595`: DS=11, SH_CP=12, ST_CP(latch)=8, outputs to LEDs with resistors.

## Shared Helpers
Common helpers live in `lib/shared`:
- `Timing.h`: simple `IntervalTimer` for periodic actions.
- `Pinout.h`: small pin helpers for outputs, PWM, and serial start.

## Notes
- Power motors/servos from an external supply and tie grounds together with the Uno.
- IR decoding and sensor readings stream over serial; open the monitor to view data.
- Adjust pin assignments as needed; update the corresponding `main.cpp` if you rewire.
