#include "IRremote.h" // библиотека для пультов ДУ
IRrecv irrecv(27); // пин 27 для ИК-приемника
decode_results results; // переменная для принимаемого сигнала
#define LED 18 // пин для ЙоТика 32В

void setup() {
  Serial.begin(115200); // Инициализация последовательного порта
  irrecv.enableIRIn(); // запускаем прием
  pinMode(LED, OUTPUT);
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    if (results.value == 0xFF18E7) { // если это кнопка "2"
      digitalWrite(LED, HIGH); // включить светодиод
    }
    if (results.value == 0xFF4AB5) { // если это кнопка "8"
      digitalWrite(LED, LOW); // выключить светодиод
    }
    irrecv.resume(); // принимаем следующую команду
  }
}
