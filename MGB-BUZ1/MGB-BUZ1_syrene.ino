#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 buzzer;
int j = 30000;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  buzzer.begin(0x61); // С перемычкой адрес будет 0x60
}

void loop() {
  // Звук сирены
  for (int i = 0; i < (5 - j / 6000); i++) {
    buzzer.setVoltage(0, false);
    //delayMicroseconds(j);
    delay_nop(j);
    buzzer.setVoltage(4095, false);
    //delayMicroseconds(j);
    delay_nop(j);
  }
  j = j - 100;
  if (j <= 0) {
    j = 30000;
  }
}

// Задержка пустыми командами
void delay_nop(int u) {
  for (int i = 0; i < u; i++) {
    _NOP();
  }
}
