#include <Wire.h>
#include <VL53L0X.h>
VL53L0X lox;

// Режим работы датчика
//#define LONG_RANGE
//#define HIGH_SPEED
#define HIGH_ACCURACY

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  Wire.begin();
  lox.init();
  lox.setTimeout(500);
#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  lox.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  lox.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  lox.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif
#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  lox.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  lox.setMeasurementTimingBudget(200000);
#endif
}

void loop() {
  // Измерение
  float dist = lox.readRangeSingleMillimeters();
  // Вывод измеренных значений в терминал
  Serial.println("Distance  = " + String(dist, 0) + " mm  ");
  delay(250);
}
