#include <Wire.h>
#include <Adafruit_MCP4725.h>
Adafruit_MCP4725 buzzer;

int vol1 = 1000;
int vol2 = 100; // разница значений = громкость
int ton;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  buzzer.begin(0x61); // С перемычкой адрес будет 0x60
  buzzer.setVoltage(0, false); // выключение звука
}
void loop() {
  buzzer.setVoltage(0, false); // выключение звука
  note(3, 450); note(5, 150); note(6, 450); // пример нескольких нот
  delay(300);
  note(10, 250); note(8, 250); note(10, 250); // пример нескольких нот
  delay(300);
}

void note( int type, int duration) { // нота (нота, длительность)
  switch (type) {
    case 1: ton = 1000; break;
    case 2: ton = 860; break;
    case 3: ton = 800; break;
    case 4: ton = 700; break;
    case 5: ton = 600; break;
    case 6: ton = 525; break;
    case 7: ton = 450; break;
    case 8: ton = 380; break;
    case 9: ton = 315; break;
    case 10: ton = 250; break;
    case 11: ton = 190; break;
    case 12: ton = 130; break;
    case 13: ton = 80; break;
    case 14: ton = 30; break;
    case 15: ton = 1; break;
  }
  delay(10); // воспроизведение звука с определенной тональностью и длительностью
  for (int i = 0; i < duration; i++) {
    buzzer.setVoltage(vol1, false);
    buzzer.setVoltage(vol2, false);
    delayMicroseconds(ton);
  }
}
