#include <Wire.h>
#include "MCP3221.h"
const byte DEV_ADDR = 0x4F;  // 0x5С , 0x4D (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
MCP3221 mcp3221(DEV_ADDR);

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация I2C интерфейса
  Wire.begin();
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
