#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SGP40.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme280;
Adafruit_SGP40 sgp;

#define I2C_HUB_ADDR 0x70
#define EN_MASK 0x08
#define DEF_CHANNEL 0x00
#define MAX_CHANNEL 0x08

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }  // Wait for serial console to open!
  Wire.begin();
  Serial.println("SGP40 test");

  /* //Wire.write
  Wire.beginTransmission(0x59);
  Wire.write(0x36);
  Wire.write(0x82);
  Serial.println(Wire.read());
 // Wire.endTransmission(0x59);*/

  if (!sgp.begin()) {
    Serial.println("Sensor not found :(");
    while (1)
      ;
  }
  Serial.print("Found SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
  setBusChannel(0x07);  // функция смены I2C-порта
  bool bme_status = bme280.begin();
  if (!bme_status) {
    Serial.println("Не найден по адресу 0х77, пробую другой...");
    bme_status = bme280.begin(0x76);
    if (!bme_status)
      Serial.println("Датчик не найден, проверьте соединение");
  }
}

int counter = 0;
void loop() {
  uint16_t raw;
  setBusChannel(0x07);  // функция смены I2C-порта
  float t = bme280.readTemperature();
  float h = bme280.readHumidity();
  raw = sgp.measureRaw();

  Serial.print("Measurement: ");
  Serial.print(raw);
  Serial.print(";\t");
  delay(10);
  Serial.print("VOC Index: ");
  Serial.println(sgp.measureVocIndex(t, h));
  delay(10);
}

bool setBusChannel(uint8_t i2c_channel) {
  if (i2c_channel >= MAX_CHANNEL) {
    return false;
  } else {
    Wire.beginTransmission(I2C_HUB_ADDR);
    // Wire.write(i2c_channel | EN_MASK); // для микросхемы PCA9547
    Wire.write(0x01 << i2c_channel);  // Для микросхемы PW548A
    Wire.endTransmission();
    return true;
  }
}