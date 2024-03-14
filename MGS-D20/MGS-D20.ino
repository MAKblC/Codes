#include <Wire.h>
#include <VL53L0X.h>
VL53L0X lox;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  Wire.begin();
  lox.init();
  lox.setTimeout(500);
  // параметры для режима высокой точности
  lox.setMeasurementTimingBudget(200000);
}

void loop() {
  // Измерение
  float dist = lox.readRangeSingleMillimeters();
  // Вывод измеренных значений в терминал
  Serial.println("Distance  = " + String(dist, 0) + " mm  ");
  delay(250);
}
