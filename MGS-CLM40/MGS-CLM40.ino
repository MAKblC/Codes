#include <Wire.h>
#include <veml6040.h>

VEML6040 RGBWSensor;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  if (!RGBWSensor.begin())
    Serial.println("ERROR: couldn't detect the sensor!");
  RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  delay(1500);
}

void loop() {
  // Измерение
  float r = RGBWSensor.getRed();
  float g = RGBWSensor.getGreen();
  float b = RGBWSensor.getBlue();
  float w = RGBWSensor.getWhite();
  float c = RGBWSensor.getCCT();
  float l = RGBWSensor.getAmbientLight();
  // Вывод измеренных значений в терминал
  Serial.println("RED   = " + String(r, 1));
  Serial.println("GREEN = " + String(g, 1));
  Serial.println("BLUE  = " + String(b, 1));
  Serial.println("WHITE = " + String(w, 1));
  Serial.println("CCT   = " + String(c, 1));
  Serial.println("LIGHT = " + String(l, 1));
  delay(350);
}
