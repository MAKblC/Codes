#include <SimpleTimer.h>
#define WINDSPD_PIN 4 // Пин датчика скорости ветра
#define WINDSPD_UPDATE_TIME 10000
SimpleTimer timer_windspd;
static volatile uint16_t wind_speed = 0; // Счетчик импульсов датчика скорости ветра

float speedy;
void IRAM_ATTR counterWind() // Обработчик прерывания с датчика скорости ветра
{
  wind_speed = wind_speed + 1;
}

void setup()
{
  Serial.begin(115200);
  pinMode(WINDSPD_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(WINDSPD_PIN), counterWind, FALLING);
  readSensorWINDSPD();
  timer_windspd.setInterval(WINDSPD_UPDATE_TIME, readSensorWINDSPD);
}
void loop()
{
  timer_windspd.run();
}
void readSensorWINDSPD()
{
  speedy = wind_speed / 10.0 * 2.4 / 3.6; // Количество импульсов/10 секунд и переводим км/ч в м/с
  wind_speed = 0; // Сброс импульсов
  Serial.println("Скорость ветра: " + String(speedy, 2)+ " м/с");
}
