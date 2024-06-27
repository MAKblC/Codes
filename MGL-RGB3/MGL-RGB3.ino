/*
  В скетче поочередно будут включаться светодиоды: в мониторе порта можно увидеть соответствующий канал
*/

#include <Wire.h>
#include <PCA9634.h>

PCA9634 testModule(0x1C);
/* Адрес зависит от перемычек на модуле(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
  Данный пример позволяет запустить MGL-RGB3 с тремя надетыми джамперами
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
  /* leds.setBrightness(x, P);
    x - светодиод:
    0,6 - белые
    1, 4 - УФ
    3 - красный RGB
    2 - зеленый RGB
    5 - синий RGB
    P - яркость (0x00-0xff) (0-255)
  */
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
  // с помощью функции
  RGB(255, 0, 0); // красный
  delay(1000);
  RGB(255, 255, 0); // желтый
  delay(1000);
  RGB(255, 0, 255); // розовый
  delay(1000);
}

// краткая функция управления RGB светодиодом
void RGB(byte r, byte g, byte b) {
  testModule.write1(3, r);
  testModule.write1(2, g);
  testModule.write1(5, b);
}