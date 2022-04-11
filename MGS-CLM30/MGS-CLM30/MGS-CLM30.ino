#include <Wire.h>

#define sensor_addr 0x39

float red_data   = 0;
float green_data = 0;
float blue_data  = 0;
float clear_data = 0;
float prox_data  = 0;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  init_sensor();
  delay(500);
}

void loop() {
  // Измерение
  poll_sensor();
  // Вывод измеренных значений в терминал
  Serial.println("RED   = " + String(red_data, 1));
  Serial.println("GREEN = " + String(green_data, 1));
  Serial.println("BLUE  = " + String(blue_data, 1));
  Serial.println("CLEAR = " + String(clear_data, 1));
  Serial.println("PROX  = " + String(prox_data, 1));
  delay(350);
}

// Инициализация датчика
void init_sensor() {
  Wire.begin();
  Wire.beginTransmission(sensor_addr);
  Wire.write(0x80);       // Регистр управления питанием
  Wire.write(0b00001111); // Включение ожидания, ALS, Proximity и Color
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(0x81);       // Регистр времени интегрирования АЦП
  Wire.write(0b00000000); // 712 мс, 65535 циклов
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(0x83);       // Регистр времени ожидания
  Wire.write(0b11111111); // 2.78 мс
  Wire.endTransmission();
  Wire.beginTransmission(sensor_addr);
  Wire.write(0x8F);       // Регистр управления
  //Wire.write(0b00110000); // Усиление 1x, отключена подсветка
  Wire.write(0b00000000); // Усиление 1x, дополнительные режимы отключены
  Wire.endTransmission();
}

// Получение данных с датчика
void poll_sensor() {
  unsigned int sensor_data[9];
  Wire.beginTransmission(sensor_addr);
  Wire.write(0x94); // Регистр данных для цвета и приближения
  Wire.endTransmission();
  Wire.requestFrom(sensor_addr, 9);
  if (Wire.available() == 9) {
    sensor_data[0] = Wire.read();
    sensor_data[1] = Wire.read();
    sensor_data[2] = Wire.read();
    sensor_data[3] = Wire.read();
    sensor_data[4] = Wire.read();
    sensor_data[5] = Wire.read();
    sensor_data[6] = Wire.read();
    sensor_data[7] = Wire.read();
    sensor_data[8] = Wire.read();
  }
  clear_data = sensor_data[1] * 256.0 + sensor_data[0];
  red_data   = sensor_data[3] * 256.0 + sensor_data[2];
  green_data = sensor_data[5] * 256.0 + sensor_data[4];
  blue_data  = sensor_data[7] * 256.0 + sensor_data[6];
  prox_data  = sensor_data[8];
}
