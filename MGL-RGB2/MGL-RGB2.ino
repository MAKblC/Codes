#include <Wire.h>
#include <PCA9634.h>

PCA9634 testModule(0x4D); //(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

/*
  0 - UV1 Ультрафиолет
  1 - W1 Белый
  2-
  3- R Красный
  4- B Синий
  5 - UV2 Ультрафиолет
  6 - W2 Белый
  7 - G Зелёный
*/

void setup() {
  Serial.begin(115200);
  testModule.begin();
  for (int channel = 0; channel < testModule.channelCount(); channel++)
  {
    testModule.setLedDriverMode(channel, PCA9634_LEDOFF); // выключить все светодиоды в режиме 0/1
    testModule.write1(channel, 0x00); // выключить все светодиоды в режиме ШИМ
    delay(200);
    testModule.setLedDriverMode(channel, PCA9634_LEDPWM); // установка режима ШИМ
  }
}

void loop() {
  // проверка всех каналов по очереди
  for (int channel = 0; channel < 8; channel++)
  {
    for (byte pwm = 0; pwm < 0xff; pwm++) {
      testModule.write1(channel, pwm);
      delay(1);
    }
    for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
      testModule.write1(channel, pwm);
      delay(1);
    }
  }
}
