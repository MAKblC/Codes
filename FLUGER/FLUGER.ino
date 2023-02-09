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
  String wind_dir_text = ""; // строковая переменная для обозначения направления
  if (sensval >= 11.4 && sensval < 12.35) { // проверка значения и сопоставление с направлением ветра
    dir = 0.0; // N
    wind_dir_text = "N";
  } else if (sensval >= 5 && sensval < 6.45) {
    dir = 22.5; // NNE
    wind_dir_text = "NNE";
  } else if (sensval >= 6.45 && sensval < 8) {
    dir = 45.0; // NE
    wind_dir_text = "NE";
  } else if (sensval >= 0.48 && sensval < 0.7) {
    dir = 67.5; // ENE
    wind_dir_text = "ENE";
  } else if (sensval >= 0.7 && sensval < 1.05) {
    dir = 90.0; // E
    wind_dir_text = "E";
  } else if (sensval < 0.48) {
    dir = 112.5; // ESE
    wind_dir_text = "ESE";
  } else if (sensval >= 1.8 && sensval < 2.8) {
    dir = 135.0; // SE
    wind_dir_text = "SE";
  } else if (sensval >= 1.05 && sensval < 1.8) {
    dir = 157.5; // SSE
    wind_dir_text = "SSE";
  } else if (sensval >= 3.7 && sensval < 5) {
    dir = 180.0; // S
    wind_dir_text = "S";
  } else if (sensval >= 2.8 && sensval < 3.7) {
    dir = 202.5; // SSW
    wind_dir_text = "SSW";
  } else if (sensval >= 9.35 && sensval < 10.2) {
    dir = 225.0; // SW
    wind_dir_text = "SW";
  } else if (sensval >= 8 && sensval < 9.35) {
    dir = 247.5; // WSW
    wind_dir_text = "WSW";
  } else if (sensval >= 14.1) {
    dir = 270.0; // W
    wind_dir_text = "W";
  } else if (sensval >= 12.35 && sensval < 13.1) {
    dir = 292.5; // WNW
    wind_dir_text = "WNW";
  } else if (sensval >= (13.1) && sensval < 14.1) {
    dir = 315.0; // NW
    wind_dir_text = "NW";
  } else if (sensval >= 10.2 && sensval < 11.4) {
    dir = 337.5; // NNW
    wind_dir_text = "NNW";
  }
  Serial.println("Направление ветра: "); // вывод информации в порт
  Serial.println(String(dir, 1) + "°");
  Serial.println(wind_dir_text);
}
