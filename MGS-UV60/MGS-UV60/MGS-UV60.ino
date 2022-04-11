#include <Wire.h>
#include <VEML6075.h>
VEML6075 veml6075;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  Wire.begin(21, 22);
  Wire.setClock(10000L);
  if (!veml6075.begin())
    Serial.println("VEML6075 not found!");
}

void loop() {
  // Измерение
  veml6075.poll();
  float uva = veml6075.getUVA();
  float uvb = veml6075.getUVB();
  float uv_index = veml6075.getUVIndex();
  // Вывод измеренных значений в терминал
  Serial.println("UVA = " + String(uva, 1) + "   ");
  Serial.println("UVB = " + String(uvb, 1) + "   ");
  Serial.println("UV INDEX = " + String(uv_index, 1) + "   ");
  delay(250);
}
