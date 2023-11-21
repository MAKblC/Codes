#define SOIL_MOISTURE    34 // A6
#define SOIL_TEMPERATURE 35 // A7
// откалиброванные значения АЦП
const float air_value    = 1587.0;
const float water_value  = 800.0;
const float moisture_0   = 0.0;
const float moisture_100 = 100.0;

const float k = 6.27; // коэффициент поправки напряжения АЦП ESP32 для ~4.45В

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
}

void loop() {
  // Измерение
  float adc0 = analogRead(SOIL_MOISTURE);
  float adc1 = analogRead(SOIL_TEMPERATURE);
  float t = ((adc1 / 4095.0 * k) - 0.5) * 100.0; // АЦП разрядность (12) = 4095 
  float h = map(adc0, air_value, water_value, moisture_0, moisture_100);
  // Вывод измеренных значений в терминал
  Serial.println("Soil humidity = " + String(h, 1) + " %");
  Serial.println("Soil temperature = " + String(t, 1) + " *C");
  delay(250);
}
