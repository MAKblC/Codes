#include <Wire.h>
#include "MCP3221.h"
const byte DEV_ADDR = 0x4F;  // 0x5С , 0x4D
MCP3221 mcp3221(DEV_ADDR);

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация I2C интерфейса
  Wire.begin();
}

void loop()
{
  float adc0 = mcp3221.getVoltage();
  Serial.println(adc0);
  delay(200);
}

