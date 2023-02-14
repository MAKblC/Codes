
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  lightMeter.begin();
}

void loop() {
  float lux = lightMeter.readLightLevel(); // считывание освещенности
  Serial.print("Освещенность: ");
  Serial.print(lux);
  Serial.println(" Люкс");
  delay(1000);
}
