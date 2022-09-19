#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x70); // адрес зависит от перемычек на плате (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация драйвера
  Wire.begin();
  pwm.begin();
  // Частота (Гц)
  pwm.setPWMFreq(100);
  // Все порты выключены
  pwm.setPWM(8, 0, 4096);
  pwm.setPWM(9, 0, 4096);
  pwm.setPWM(10, 0, 4096);
  pwm.setPWM(11, 0, 4096);
}

void loop() {
  // плавный разгон и остановка
  for (int i = 0; i <= 100; i++) { 
    motorA_setpower(i, false);
    motorB_setpower(i, true);
    delay(25);
  }
  for (int i = 100; i >= -100; i--) {
    motorA_setpower(i, false);
    motorB_setpower(i, true);
    delay(25);
  }
  for (int i = -100; i <= 0; i++) {
    motorA_setpower(i, false);
    motorB_setpower(i, true);
    delay(25);
  }
  for (int i = 0; i <= 100; i++) {
    motorA_setpower(i, false);
    motorB_setpower(i, false);
    delay(25);
  }
  for (int i = 100; i >= -100; i--) {
    motorA_setpower(i, false);
    motorB_setpower(i, false);
    delay(25);
  }
  for (int i = -100; i <= 0; i++) {
    motorA_setpower(i, false);
    motorB_setpower(i, false);
    delay(25);
  }

}

// Мощность мотора "A" от -100% до +100% (от знака зависит направление вращения)
void motorA_setpower(float pwr, bool invert)
{
  // Проверка, инвертирован ли мотор
  if (invert)
  {
    pwr = -pwr;
  }
  // Проверка диапазонов
  if (pwr < -100)
  {
    pwr = -100;
  }
  if (pwr > 100)
  {
    pwr = 100;
  }
  int pwmvalue = fabs(pwr) * 40.95;
  if (pwr < 0)
  {
    pwm.setPWM(10, 0, 4096);
    pwm.setPWM(11, 0, pwmvalue);
  }
  else
  {
    pwm.setPWM(11, 0, 4096);
    pwm.setPWM(10, 0, pwmvalue);
  }
}

// Мощность мотора "B" от -100% до +100% (от знака зависит направление вращения)
void motorB_setpower(float pwr, bool invert)
{
  // Проверка, инвертирован ли мотор
  if (invert)
  {
    pwr = -pwr;
  }
  // Проверка диапазонов
  if (pwr < -100)
  {
    pwr = -100;
  }
  if (pwr > 100)
  {
    pwr = 100;
  }
  int pwmvalue = fabs(pwr) * 40.95;
  if (pwr < 0)
  {
    pwm.setPWM(8, 0, 4096);
    pwm.setPWM(9, 0, pwmvalue);
  }
  else
  {
    pwm.setPWM(9, 0, 4096);
    pwm.setPWM(8, 0, pwmvalue);
  }
}
