/*
  В скетче поочередно будут включаться светодиоды: в мониторе порта можно увидеть соответствующий канал
*/

#include <Wire.h>
#include <PCA9634.h>

PCA9634 testModule(0x08);
/* Адрес зависит от перемычек на модуле(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
  Данный пример позволяет запустить MGL-RGB3.2
*/

void setup() {
  Serial.begin(115200);
  testModule.begin();
  for (int channel = 0; channel < testModule.channelCount(); channel++)
  {
    testModule.setLedDriverMode(channel, PCA9634_LEDOFF); // выключить все светодиоды в режиме 0/1
  }
}

void loop() {
  for (int channel = 0; channel < testModule.channelCount(); channel++)
  {
    testModule.setLedDriverMode(channel, PCA9634_LEDON);
    Serial.println(channel);
    delay(500);
    testModule.setLedDriverMode(channel, PCA9634_LEDOFF);
    delay(500);
  }
  for (int channel = 0; channel < testModule.channelCount(); channel++)
  {
    testModule.setLedDriverMode(channel, PCA9634_LEDPWM); // установка режима ШИМ (0-255)
  }
  testModule.write1(3, 0x90);
  testModule.write1(2, 0x00);
  testModule.write1(5, 0x90);
  Serial.println("розовый");
  delay(1000);
  testModule.write1(3, 0x00);
  testModule.write1(2, 0x90);
  testModule.write1(5, 0x90);
  Serial.println("голубой");
  delay(1000);
  testModule.write1(3, 0x90);
  testModule.write1(2, 0x90);
  testModule.write1(5, 0x00);
  Serial.println("желтый");
  delay(1000);
  testModule.write1(3, 0x00);
  testModule.write1(2, 0x00);
  testModule.write1(5, 0x00);
}

