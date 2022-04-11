#include <Wire.h>
#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds9960;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация датчика
  if (!apds9960.begin()) {
    Serial.println("Failed to initialize device!");
  }
  // Инициализация режимов работы датчика
  apds9960.enableProximity(true);
  apds9960.enableGesture(true);
}

void loop() {
  uint8_t  gest_data  = 0;
  uint16_t prox_data  = 0;
  // Детектирование жеста и близости препятствия
  gest_data = apds9960.readGesture();
  prox_data = apds9960.readProximity();
  // Вывод измеренных значений в терминал
  if (gest_data == APDS9960_DOWN) {
    Serial.println("DOWN");
    Serial.println("PROX  = " + String(prox_data));
  }
  if (gest_data == APDS9960_UP) {
    Serial.println("UP");
    Serial.println("PROX  = " + String(prox_data));
  }
  if (gest_data == APDS9960_LEFT) {
    Serial.println("LEFT");
    Serial.println("PROX  = " + String(prox_data));
  }
  if (gest_data == APDS9960_RIGHT) {
    Serial.println("RIGHT");
    Serial.println("PROX  = " + String(prox_data));
  }
}
