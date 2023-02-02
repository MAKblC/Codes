// переменный резистор R4 на задней стороне для регулировки контраста

#include <Wire.h>
#include <I2C_graphical_LCD_display.h>
I2C_graphical_LCD_display lcd;

int val = 0;
float b = 0;
char b1[8];
char val2[8];

void setup ()
{
   // Инициализация дисплея
  lcd.begin();

  // Рисование рамки
  lcd.frameRect (0, 0, 127, 63, 1, 1);

  // Рисование квадратика
  lcd.clear (10, 10, 20, 20, 0xFF);

  // Вывод строки
  lcd.gotoxy (10, 50); // координата курсора
  lcd.string ("Privet, MGBOT!", false);
}

void loop ()
{
  val = hallRead(); // считывание значеия датчика Холла
  itoa(val, val2, 10); // перевод int в char
  lcd.gotoxy (10, 30); 
  lcd.string(val2); 
  lcd.gotoxy (40, 10);
  b = b + 0.3; // инкремент значения
  dtostrf(b, 6, 2, b1);  // перевод float в char
  lcd.string(b1);
  delay(1000);
}