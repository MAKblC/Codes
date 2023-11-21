/* 
Измерение значений с аналогового датчика температуры и влажности почвы  MGS-TH50
с помощью платы расширения I2C MGB-D1015 (порт АЦП)
*/
#include <Adafruit_ADS1015.h>
#include <Wire.h>

Adafruit_ADS1015 ads(0x48);
const float air_value    = 83900.0; // значения для калибровки датчика почвы
const float water_value  = 45000.0;
const float moisture_0   = 0.0;
const float moisture_100 = 100.0;  // настройка АЦП на плате расширения I2C MGB-D10 

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  ads.begin();    // инициализация АЦП
}

void loop()
{
  float adc0 = (float)ads.readADC_SingleEnded(0) / 2047.0 * 6.144;
  float adc1 = (float)ads.readADC_SingleEnded(1) / 2047.0 * 6.144;
  // измерение температуры
  float t1 = (adc1  - 0.5) * 100.0; // по формуле для TC1047A
  // преобразование значения влажности в диапазон от 0 до 100%
  float h1 = map(adc0, air_value, water_value, moisture_0, moisture_100); 
  Serial.println("soil temperature = " + String(t1, 1) + " °C");
  Serial.println("soil humidity = " + String(h1, 1) + " %");
  delay(1000);
}