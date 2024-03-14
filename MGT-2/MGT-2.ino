// пины транзисторов
#define PWMA 16
#define PWMB 17

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация выходов для управления моторами
  ledcAttachPin(PWMA, 1);
  ledcAttachPin(PWMB, 2);
  // канал, частота, разрядность
  ledcSetup(1, 50, 10);
  ledcSetup(2, 50, 10);
}

void loop() {
  int value;
  // плавное включение
  for (value = 0; value <= 100; value++) {
    ledcWrite(1, value * 10.23);
    ledcWrite(2, value * 10.23);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }
  // плавное выключение
  for (value = 100; value >= 0; value--) {
    ledcWrite(1, value * 10.23);
    ledcWrite(2, value * 10.23);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }
}
