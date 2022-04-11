// переменный резистор на задней стороне для регулировки контраста

#include <Wire.h>
#include <I2C_graphical_LCD_display.h>
I2C_graphical_LCD_display lcd;

void setup ()
{
  // Инициализация дисплея
  lcd.begin();

  // Рисование рамки
  lcd.frameRect (0, 0, 127, 63, 1, 1);

  // Рисование квадратика
  lcd.clear (10, 10, 20, 20, 0xFF);

  // Вывод строки
  lcd.gotoxy (10, 50);
  lcd.string ("Privet, MGBOT!", false);
}

void loop ()
{
}
