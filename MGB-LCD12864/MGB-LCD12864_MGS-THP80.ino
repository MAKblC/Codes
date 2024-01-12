#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme280;
#include <I2C_graphical_LCD_display.h>
I2C_graphical_LCD_display lcd;

void setup ()
{
  Serial.begin(115200);
  bool bme_status = bme280.begin(0x76); // адрес без джампера
  if (!bme_status)
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  lcd.begin();
  lcd.gotoxy (0, 0);
  lcd.clear (0, 0, 128, 64, 0x00);
}

void loop ()
{
  float t = bme280.readTemperature();
  float h = bme280.readHumidity();
  float p = bme280.readPressure() / 100.0F;
  lcd.gotoxy (40, 53); // устанавливаем курсор в координату (40,53)
  lcd.string ("Temperature, C" , false); // пишем фразу для температуры
  char buf[8]; // создаем переменную типа char
  sprintf(buf, "%d", (int)t); // отправляем в нее данные о температуре
  lcd.clear (10, 53, 32, 60, 0x00); // очищаем место под данные
  lcd.gotoxy (10, 53); // устанавливаем курсор в координату (10,53)
  lcd.string (buf, false); // Пишем значение температуры
  lcd.gotoxy (40, 39); // устанавливаем курсор в координату (40,39)
  lcd.string ("Humidity, %" , false);// пишем фразу для влажности
  char buf1[8]; // создаем переменную типа char
  sprintf(buf1, "%d", (int)h); // отправляем в нее данные о влажности
  lcd.clear (10, 39, 32, 46, 0x00); // очищаем место под данные
  lcd.gotoxy (10, 39); // устанавливаем курсор в координату (10,39)
  lcd.string (buf1, false); // Пишем значение температуры
  lcd.gotoxy (40, 22); // устанавливаем курсор в координату (40,22)
  lcd.string ("Pressure, hPa" , false); // пишем фразу для давления
  char buf2[8]; // создаем переменную типа char
  sprintf(buf2, "%d", (int)p); // отправляем в нее данные о давлении
  lcd.clear (10, 22, 32, 32, 0x00); // очищаем место под данные
  lcd.gotoxy (10, 22); // устанавливаем курсор в координату (10,22)
  lcd.string (buf2, false); // Пишем значение давления
  delay(1000);
}
