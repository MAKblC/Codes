#include "SparkFun_SGP30_Arduino_Library.h"
#include <Wire.h>
SGP30 mySensor;

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
  delay(1000);
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");
}
