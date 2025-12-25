/*
  MPU-6050 (uno-mpu6050)

  Что нужно из набора:
    - MPU-6050 (гироскоп + акселерометр)
    - 4 провода (лучше папа-мама)

  Подключение (I2C):
    MPU-6050  ->  Arduino Uno
    VCC       ->  5V*  (или 3.3V, если на модуле написано 3V3)
    GND       ->  GND
    SDA       ->  A4
    SCL       ->  A5

  Что увидишь:
    - В Serial Monitor 115200: ускорение и гироскоп
*/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println(F("MPU6050 not found"));
    while (true) {
      delay(1000);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println(F("MPU6050 ready"));
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print(F("Accel m/s^2 X:"));
  Serial.print(a.acceleration.x, 2);
  Serial.print(F(" Y:"));
  Serial.print(a.acceleration.y, 2);
  Serial.print(F(" Z:"));
  Serial.print(a.acceleration.z, 2);

  Serial.print(F(" | Gyro dps X:"));
  Serial.print(g.gyro.x, 2);
  Serial.print(F(" Y:"));
  Serial.print(g.gyro.y, 2);
  Serial.print(F(" Z:"));
  Serial.println(g.gyro.z, 2);

  delay(200);
}
