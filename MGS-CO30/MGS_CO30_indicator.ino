#include "SparkFun_SGP30_Arduino_Library.h"
#include <Wire.h>
SGP30 mySensor;

int ctitical_CO2 = 600;
int critical_TVOC = 150;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  if (mySensor.begin() == false) {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  mySensor.initAirQuality();
}

void loop() {
  // первые 15 измерений будут неизменными
  delay(100);
  mySensor.measureAirQuality();
  if (mySensor.CO2 > ctitical_CO2) {
    Serial.println("Превышен допустимый уровень углекислого газа!");
  }
  if (mySensor.TVOC > critical_TVOC) {
    Serial.println("Превышен допустимый уровень летучих органических соединений!");
  }
}
