
#include <Wire.h> 
#include <BH1750FVI.h> 

BH1750FVI LightSensor;
int lux;

void setup() {

  Serial.begin(115200);

  LightSensor.begin();
  LightSensor.setMode(Continuously_High_Resolution_Mode); 

  Serial.println("Датчик запущен");

}

void loop() {

  lux = LightSensor.getAmbientLight();
  Serial.print("Освещенность: ");
  Serial.print(lux);
  Serial.println(" Лк");
  delay(1000);

}