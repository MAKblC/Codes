/* в скетче к набору Динамика подключены 2 цифровых датчика линии
либо можно подключить аналоговые (MGS-LN1A)
Робот едет по линии, используя простой пропорциональный регулятор
*/

int pin1 = 35; // A7
int pin2 = 34; // A6

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x70); // адрес зависит от перемычек на плате (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  Serial.begin(115200);
  Wire.begin();
  pwm.begin();
  // Частота (Гц)
  pwm.setPWMFreq(100);
  // Все порты выключены
  pwm.setPWM(8, 0, 4096);
  pwm.setPWM(9, 0, 4096);
  pwm.setPWM(10, 0, 4096);
  pwm.setPWM(11, 0, 4096);
  delay(1000);
}

void loop() {
  // если датчик 1 наступает на линию, то кренимся вправо
  if (analogRead(pin1) < 3000 and analogRead(pin2) > 3000) {
    motorB_setpower(30, false);
    motorA_setpower(10, false);
  }
  // если датчик 2 наступает на линию, то кренимся влево
  else if (analogRead(pin2) < 3000 and analogRead(pin1) > 3000) {
    motorB_setpower(10, true);
    motorA_setpower(30, true);
  }
  // если оба датчика не попадают на линию, то едем прямо
  else if (analogRead(pin2) > 3000 and analogRead(pin1) > 3000) {
    motorB_setpower(20, false);
    motorA_setpower(20, true);
  }
  
}

// Мощность мотора "А" от -100% до +100% (от знака зависит направление вращения)
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
