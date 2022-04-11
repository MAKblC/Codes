#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_CCS811.h>
Adafruit_CCS811 ccs811;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация и температурная компенсация датчика
  bool ccs_status = ccs811.begin();
  if (!ccs_status)
    Serial.println("Failed to start sensor CCS811!");
  while (!ccs811.available());
  float ccs_temp = ccs811.calculateTemperature();
  ccs811.setTempOffset(ccs_temp - 25.0);
}

void loop() {
  float t = 0;
  float co2 = 0;
  float tvoc = 0;
  // Проверка наличия измеренных данных
  if (ccs811.available())
  {
    t = ccs811.calculateTemperature();
    if (!ccs811.readData())
    {
      // Считывание измеренных данных
      co2 = ccs811.geteCO2();
      tvoc = ccs811.getTVOC();
      // Вывод измеренных значений в терминал
      Serial.println("T    = " + String(t, 1) + " *C");
      Serial.println("CO2  = " + String(co2, 1) + " ppm");
      Serial.println("TVOC = " + String(tvoc, 1) + " ppm");
    }
  }
  delay(250);
}
