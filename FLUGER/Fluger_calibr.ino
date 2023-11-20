#include <SimpleTimer.h>
#define WINDDIR_PIN 34 // пин для флюгера
#define WINDDIR_UPDATE_TIME 2000 // период обновления
SimpleTimer timer_winddir;
float dir;

void setup()
{
  Serial.begin(115200);
  delay(512);
  readSensorWINDDIR(); // функция считывания направления ветра
  timer_winddir.setInterval(WINDDIR_UPDATE_TIME, readSensorWINDDIR); // настройки таймера для обновления
}

void loop()
{
  timer_winddir.run(); // отслеживание таймера
}

void readSensorWINDDIR()
{
  double sensval = analogRead(34) * 5.0 / 1023.0; // считывание значения с аналогового входа
  /* выставите флюгер на нужное положение и затем зафиксируйте полученное значение
   *  определите значения 8 направлений (+8 дополнительных)
   *  разбейте значения на диапазоны
   *  испльзуйте эти диапазоны в своем скетче для метеостанции
   */
  Serial.println(sensval);
}
