// в данном примере светодиодная лента управляется через силовой ключ MGT-2
// можно управлять лентой через модуль реле (см. примеры MGR-2/MGR-2I2C, ...)

// пин для управления через транзистор
#define LED_FITO 4

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация выходов для управления лентой
  ledcAttachPin(LED_FITO, 1);
  // канал, частота, разрядность
  ledcSetup(1, 5000, 10);
}

void loop() {
  int value;
  // плавное включение
  for (value = 0; value <= 100; value++) {
    ledcWrite(1, value * 10.23);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }
  // плавное выключение
  for (value = 100; value >= 0; value--) {
    ledcWrite(1, value * 10.23);
    Serial.println("Power: " + String(value) + " %");
    delay(50);
  }
}
