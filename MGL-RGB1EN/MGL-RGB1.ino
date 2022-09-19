#include <Wire.h>
#include "TLC59108.h"

#define HW_RESET_PIN 0 // Только программный сброс
#define I2C_ADDR TLC59108::I2C_ADDR::BASE

TLC59108 leds(I2C_ADDR + 7);

/*
  Джамперы JP0, JP1, JP2 служат для выбора I2C-адреса.

  Например:

  Три надетых перемычки (000) - следует добавить 0 бит 000(bin) = 0(dec) =
  TLC59108 leds(I2C_ADDR +0);

  Ни одной перемычки (111) – следует добавить 3 бита 111(bin) = 7(dec) =
  TLC59108 leds(I2C_ADDR +7);

  Одна перемычка на JP0 (110) – следует добавить 2 старших бита бита 110(bin) = 6(dec) =
  TLC59108 leds(I2C_ADDR +6);
  (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
*/

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация модуля
  Wire.begin();
  leds.init(HW_RESET_PIN);
  leds.setLedOutputMode(TLC59108::LED_MODE::PWM_IND);
}

void loop() {
  /* leds.setBrightness(x, P);
    x - светодиод:
    0,6 - белые
    1, 4 - УФ
    3 - красный RGB
    2 - зеленый RGB
    5 - синий RGB
    P - яркость (0x00-0xff) (0-255)
  */
  for (byte pwm = 0; pwm < 0xff; pwm++) {
    leds.setBrightness(3, pwm);
    delay(1);
  }
  for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setBrightness(3, pwm);
    delay(1);
  }

  for (byte pwm = 0; pwm < 0xff; pwm++) {
    leds.setBrightness(2, pwm);
    delay(1);
  }
  for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setBrightness(2, pwm);
    delay(1);
  }

  for (byte pwm = 0; pwm < 0xff; pwm++) {
    leds.setBrightness(5, pwm);
    delay(1);
  }
  for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setBrightness(5, pwm);
    delay(1);
  }

  for (byte pwm = 0; pwm < 0xff; pwm++) {
    leds.setBrightness(0, pwm);
    leds.setBrightness(6, pwm);
    delay(1);
  }
  for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setBrightness(0, pwm);
    leds.setBrightness(6, pwm);
    delay(1);
  }

  for (byte pwm = 0; pwm < 0xff; pwm++) {
    leds.setBrightness(1, pwm);
    leds.setBrightness(4, pwm);
    delay(1);
  }
  for (byte pwm = 0xfe; pwm < 0xff; pwm--) {
    leds.setBrightness(1, pwm);
    leds.setBrightness(4, pwm);
    delay(1);
  }
}
