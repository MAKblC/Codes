/*
**********************************************************************
  тестовый код для определения цвета при помощи Модуль датчика цвета, освещенности, приближения и жестов MGS-CLM60
  Функция GetColor() возвращает номер элемента массива ColorRGB, который наиболее близок к цвету, который определяется датчиком в момент считывания
  Ядро esp32 v2.0.11 
  Created by Vlasov Timofey
  //********************************************************************
*/



#include <Adafruit_APDS9960.h>
#include <Wire.h>
Adafruit_APDS9960 apds9960;
int colorRGB[][4] = {
  // данные RGB, для цветных меток. Для корректной работы необходимо внести данные о цвете не только меток, но и других цветов, которые встречаются на полигоне
  { 255, 123, 218 },    // 0 - красный
  { 255, 102, 186 },  // 1 - зеленый
  { 255, 204, 236 },   //  2 - синий
  { 243, 255, 251 }  //  3 - желтый

};

uint16_t RGB[3];

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  Wire.begin();
  delay(100);

  if (!apds9960.begin()) {
    Serial.println("Failed to initialize device!");
  }
  // Инициализация режимов работы датчика
  apds9960.enableColor(true);
  apds9960.enableProximity(true);
  delay(1000);
}
void loop() {
  GetColor();
  delay(700);
}

byte GetColor() {
  // uint16_t RGB[3];
  uint16_t clear_data = 0;
  while (!apds9960.colorDataReady()) {
    delay(5);
  }

  apds9960.getColorData(&RGB[0], &RGB[1], &RGB[2], &clear_data);

  int max;
  for (int i = 0; i <= 2; i++) {
    max = RGB[i] > max ? RGB[i] : max;
  }

  Serial.println("RED   = " + String(map(RGB[0], 0, max, 0, 255)));
  Serial.println("GREEN = " + String(map(RGB[1], 0, max, 0, 255)));
  Serial.println("BLUE  = " + String(map(RGB[2], 0, max, 0, 255)));
  //Serial.println("MaxColor: " + String(max));

  Serial.println("sizeof(colorRGB)" + String(sizeof(colorRGB) / sizeof(colorRGB[1])));

  for (int i = 0; i <= sizeof(colorRGB) / sizeof(colorRGB[1]) - 1; i++) {
    colorRGB[i][3] = 0;
  }

  for (int i = 0; i <= sizeof(colorRGB) / sizeof(colorRGB[1]) - 1; i++) {
    for (int j = 0; j <= 2; j++) {
      colorRGB[i][3] += abs(colorRGB[i][j] - map(RGB[j], 0, max, 0, 255));
    }
  }
  int colorMax = 0;
  for (int i = 0; i <= sizeof(colorRGB) / sizeof(colorRGB[1]) - 1; i++) {
    colorMax = colorRGB[i][3] < colorRGB[colorMax][3] ? i : colorMax;
  }

  Serial.println("номер в массиве " + String(colorMax));
  Serial.println("-------------------------------------------------------------------------------------------");
  return colorMax;
}
