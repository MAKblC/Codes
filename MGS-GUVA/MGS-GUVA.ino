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
  mcp3221.setVinput(VOLTAGE_INPUT_5V);
}

void loop()
{
  float sensorVoltage;
  float sensorValue;
  float UV_index;

  sensorValue = mcp3221.getVoltage();
  sensorVoltage = 1000 * (sensorValue / 4096 * 5.0); // напряжение на АЦП
  UV_index = 370 * sensorVoltage / 200000; // Индекс УФ (эмпирическое измерение)
  Serial.println("Выходное напряжение = " + String(sensorVoltage, 1) + "мВ");
  Serial.println("UV index = " + String(UV_index, 1));
  delay(200);
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
