/* 
Плата расширения предназначена для подключения нескольких датчиков на одну шину I2C
Подключите плату к I2C-интерфейсу
Датчик (в примере: Датчик освещенности MGS-L75) к любому из разъемов платы
*/
#include <Wire.h>
#include <BH1750FVI.h>
BH1750FVI LightSensor_1;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  LightSensor_1.begin(); // (0x23), (0x5C) (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
  LightSensor_1.setMode(Continuously_High_Resolution_Mode);
}

void loop() {
  // Измерение
  float l = LightSensor_1.getAmbientLight();
  // Вывод измеренных значений в терминал
  Serial.println("Ambient light intensity: " + String(l, 1) + " lx");
  delay(250);
}

