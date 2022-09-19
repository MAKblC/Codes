#include <Wire.h>
#include <INA226.h>
INA226 ina226;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  Wire.begin();
  ina226.begin(0x40); // зависит от расположения перемычек (также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)
  ina226.configure(INA226_AVERAGES_1, INA226_BUS_CONV_TIME_1100US, INA226_SHUNT_CONV_TIME_1100US, INA226_MODE_SHUNT_BUS_CONT);
  ina226.calibrate(0.002, 10);
}

void loop() {
  Serial.print("Bus voltage:   ");
  Serial.print(ina226.readBusVoltage(), 5);
  Serial.println(" V");
  Serial.print("Bus power:     ");
  Serial.print(ina226.readBusPower(), 5);
  Serial.println(" W");
  Serial.print("Shunt voltage: ");
  Serial.print(ina226.readShuntVoltage(), 5);
  Serial.println(" V");
  Serial.print("Shunt current: ");
  Serial.print(ina226.readShuntCurrent(), 5);
  Serial.println(" A");
  Serial.println("");
  delay(500);
}
