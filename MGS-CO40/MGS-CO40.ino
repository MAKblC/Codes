#include <Wire.h>
#include "Adafruit_SGP40.h" // библиотека для MGS-CO40
Adafruit_SGP40 sgp; // создаем объект класса

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(10); }
  Wire.begin();
  Serial.println("тест MGS-CO40");
  // инициализация датчика
  if (!sgp.begin()) {
    Serial.println("Датчик не обнаружен :(");
    while (1)
      ;
  }
  Serial.print("Датчик MGS-CO40 обнаружен");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);
}

void loop() {
  uint16_t raw;
  // сниманием сырые показания
  raw = sgp.measureRaw();
  Serial.print("Показания: ");
  Serial.print(raw);
  Serial.print(";\t");
  delay(10);
  Serial.print("VOC Индекс: ");
  // вывод VOC-индекса
  Serial.println(sgp.measureVocIndex());
  delay(10);
}
