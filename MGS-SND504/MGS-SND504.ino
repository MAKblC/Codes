#include <Wire.h>
#include "MCP3221.h"

MCP3221 mcp3221(0x48); // Адрес может отличаться(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация I2C интерфейса
  Wire.begin();
}

void loop() {
  // Измерение
  float adc0 = mcp3221.getVoltage();
  // Вывод измеренных значений в терминал
  Serial.println("Sound level = " + String(adc0, 1));
  delay(50);
}
