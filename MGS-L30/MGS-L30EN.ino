#include <Wire.h>
#include <ClosedCube_OPT3001.h>

ClosedCube_OPT3001 opt3001;
#define OPT3001_ADDRESS 0x44 //44-47 (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  opt3001.begin(OPT3001_ADDRESS);
  OPT3001_Config newConfig;
  newConfig.RangeNumber = B1100;
  newConfig.ConvertionTime = B0;
  newConfig.Latch = B1;
  newConfig.ModeOfConversionOperation = B11;
  OPT3001_ErrorCode errorConfig = opt3001.writeConfig(newConfig);
}

void loop() {
  // Измерение
  OPT3001 result = opt3001.readResult();
  float l = result.lux;
  // Вывод измеренных значений в терминал
  Serial.println("Ambient light intensity: " + String(l, 1) + " lx");
  delay(250);
}
