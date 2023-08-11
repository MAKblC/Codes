#include <Wire.h>
#include <BH1750FVI.h>

BH1750FVI LightSensor_1; // экземпляры пяти датчиков освещенности
BH1750FVI LightSensor_2;
BH1750FVI LightSensor_3;
BH1750FVI LightSensor_4;
BH1750FVI LightSensor_5;

// Константы для I2C шилда
#define I2C_HUB_ADDR        0x70
#define EN_MASK             0x08
#define DEF_CHANNEL         0x00
#define MAX_CHANNEL         0x08

/*
  I2C порт 0x07 - выводы GP16 (SDA), GP17 (SCL)
  I2C порт 0x06 - выводы GP4 (SDA), GP13 (SCL)
  I2C порт 0x05 - выводы GP14 (SDA), GP15 (SCL)
  I2C порт 0x04 - выводы GP5 (SDA), GP23 (SCL)
  I2C порт 0x03 - выводы GP18 (SDA), GP19 (SCL)
*/

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);

  // Инициализация I2C
  Wire.begin();
  delay(1000);

  // Инициализация датчика #1
  setBusChannel(0x07); // функция смены I2C-порта
  LightSensor_1.begin();
  LightSensor_1.setMode(Continuously_High_Resolution_Mode);

  // Инициализация датчика #2
  setBusChannel(0x06); // функция смены I2C-порта
  LightSensor_2.begin();
  LightSensor_2.setMode(Continuously_High_Resolution_Mode);

  // Инициализация датчика #3
  setBusChannel(0x05); // функция смены I2C-порта
  LightSensor_3.begin();
  LightSensor_3.setMode(Continuously_High_Resolution_Mode);

  // Инициализация датчика #4
  setBusChannel(0x04); // функция смены I2C-порта
  LightSensor_4.begin();
  LightSensor_4.setMode(Continuously_High_Resolution_Mode);

  // Инициализация датчика #5
  setBusChannel(0x03); // функция смены I2C-порта
  LightSensor_5.begin();
  LightSensor_5.setMode(Continuously_High_Resolution_Mode);
}

void loop() {
  // Считывание датчиков
  setBusChannel(0x07);
  float light1 = LightSensor_1.getAmbientLight();
  setBusChannel(0x06);
  float light2 = LightSensor_2.getAmbientLight();
  setBusChannel(0x05);
  float light3 = LightSensor_3.getAmbientLight();
  setBusChannel(0x04);
  float light4 = LightSensor_4.getAmbientLight();
  setBusChannel(0x03);
  float light5 = LightSensor_5.getAmbientLight();

  Serial.println("Ambient light intensity 1: " + String(light1, 1) + " lx");
  Serial.println("Ambient light intensity 2: " + String(light2, 1) + " lx");
  Serial.println("Ambient light intensity 3: " + String(light3, 1) + " lx");
  Serial.println("Ambient light intensity 4: " + String(light4, 1) + " lx");
  Serial.println("Ambient light intensity 5: " + String(light5, 1) + " lx");

}

// Функция установки нужного выхода I2C
bool setBusChannel(uint8_t i2c_channel)
{
  if (i2c_channel >= MAX_CHANNEL)
  {
    return false;
  }
  else
  {
    Wire.beginTransmission(I2C_HUB_ADDR);
    Wire.write(i2c_channel | EN_MASK); // для микросхемы PCA9547
	// Wire.write(0x01 << i2c_channel); // Для микросхемы PW548A
    Wire.endTransmission();
    return true;
  }
}
