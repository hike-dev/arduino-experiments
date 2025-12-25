#include <Arduino.h>
#include <IRremote.hpp>

constexpr uint8_t kIrPin = 7;

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(kIrPin, ENABLE_LED_FEEDBACK);
  Serial.println(F("IR receiver ready"));
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print(F("Protocol: "));
    Serial.print(IrReceiver.decodedIRData.protocol);
    Serial.print(F(" Address: 0x"));
    Serial.print(IrReceiver.decodedIRData.address, HEX);
    Serial.print(F(" Command: 0x"));
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();
  }
}
