#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme280;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  bool bme_status = bme280.begin();
  if (!bme_status) {
    Serial.println("Не найден по адресу 0х77, пробую другой...");
    bme_status = bme280.begin(0x76);
    if (!bme_status)
      Serial.println("Датчик не найден, проверьте соединение");
  }
}

void loop() {
  // Измерение
  float t = bme280.readTemperature();
  float h = bme280.readHumidity();
  float p = bme280.readPressure() / 100.0F;
  // Вывод измеренных значений в терминал
  Serial.println("Air temperature = " + String(t, 1) + " *C");
  Serial.println("Air humidity = " + String(h, 1) + " %");
  Serial.println("Air pressure = " + String(p, 1) + " hPa"); // 1 mmHg = 1 hPa / 1.33
  delay(250);
}
