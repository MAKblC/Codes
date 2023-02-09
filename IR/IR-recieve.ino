#include "IRremote.h" // библиотека для пультов ДУ
IRrecv irrecv(27); // пин 27 для ИК-приемника
decode_results results; // переменная для принимаемого сигнала

void setup() {
  Serial.begin(115200); // Инициализация последовательного порта
  irrecv.enableIRIn(); // запускаем прием
}

void loop() {
  if ( irrecv.decode( &results )) { // если данные пришли
    Serial.println(results.value, HEX); // выводим в порт полученное значение
    irrecv.resume(); // принимаем следующую команду
  }
}
