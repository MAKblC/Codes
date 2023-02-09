#include <SimpleTimer.h> // библиотека таймера
#define RAIN_PIN 13 // пин к которому подключен осадкомер
#define RAIN_UPDATE_TIME 1000 // период обновления данных 10сек
SimpleTimer timer_rain; // экземпляр таймера
float rain; // переменная для осадков
static volatile uint16_t rain_rate = 0; // Счетчик импульсов датчика дождя

void IRAM_ATTR counterRain() // цикл прерывания для подсчета импульсов
{
  rain_rate = rain_rate + 1; // инкремент импульсов
}

void setup()
{
  Serial.begin(115200); // Инициализация последовательного порта
  pinMode(RAIN_PIN, INPUT_PULLUP); // Инициализация входа датчика дождя
  attachInterrupt(digitalPinToInterrupt(RAIN_PIN), counterRain, FALLING); // Инициализация  прерываний на входах с импульсных датчиков
  readSensorRAIN(); // первое чтение дождемера
  timer_rain.setInterval(RAIN_UPDATE_TIME, readSensorRAIN); // конфигурация таймера
}
void loop()
{
  timer_rain.run(); // запуск таймера
}
void readSensorRAIN() // Чтение датчика уровня осадков по таймеру
{
  rain = rain_rate * 0.2794; // количество импульсов * мм осадков
  rain_rate = 0; // сброс количества импульсов
  Serial.println("Осадки при измерении 1 раз в секунду: " + String(rain, 2)+ " мм"); // вывод значения в последовательный порт
}
