// в данном примере используется функция ШИМ для esp32
#define  amper  14   // пин индикатора
const int freq = 5000; // частота
const int ledChannel = 0; // канал
const int resolution = 8; // разрешение

void setup() {
  ledcSetup(ledChannel, freq, resolution);
  ledcAttachPin(amper, ledChannel);
}

void loop() {
  // увеличиваем показание индикатора
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }

  // уменьшаем показание индикатора
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledChannel, dutyCycle);
    delay(15);
  }
}
