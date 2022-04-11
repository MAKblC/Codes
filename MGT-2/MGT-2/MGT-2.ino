
#define PWMA 16
#define PWMB 17

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация выходов для управления моторами
  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);
  ledcSetup(1, 50, 10);
  ledcSetup(2, 50, 10);
}

void loop() {
  int value;
 
  for (value = 0 ; value <= 100; value += 1)
  {
    motorA_setpower(value);
    motorB_setpower(value);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }

  for (value = 100 ; value >= -100; value -= 1)
  {
    motorA_setpower(value);
    motorB_setpower(value);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }

  for (value = -100 ; value <= 0; value += 1)
  {
    motorA_setpower(value);
    motorB_setpower(value);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }
}

void motorA_setpower(float pwr)
{
  int pwmvalue = fabs(pwr) * 10.23;
  ledcWrite(1, pwmvalue);
}
void motorB_setpower(float pwr)
{
  int pwmvalue = fabs(pwr) * 10.23;
  ledcWrite(2, pwmvalue);
}
