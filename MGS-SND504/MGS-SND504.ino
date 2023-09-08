#include <Wire.h>
#include "MCP3221.h"
byte ADDR;
MCP3221 mcp3221(ADDR);

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация I2C интерфейса
  Wire.begin();
  ADDR = scan(); // скан адреса
  Serial.println(" АДРЕС:");
  Serial.println(ADDR, HEX);
  mcp3221.setAddress(ADDR);
}

void loop() {
  // Измерение
  float adc0 = mcp3221.getVoltage();
  // Вывод измеренных значений в терминал
  Serial.println("Sound level = " + String(adc0, 1));
  delay(50);
}

byte scan() { // сканирование адреса
  byte error, address;
  Serial.println("Сканирую...");
  for (address = 8; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C устройство найдено по адресу 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      return address;
      Serial.println(" !");
      break;
    }
  }
}
