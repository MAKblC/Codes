#include <LiquidCrystal_I2C.h>

// столбцы и строки
int lcdColumns = 16;
int lcdRows = 2;

// добавляем экзмпляр (адрес, количество столбцов, количество строк)
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows); // 0x27

void setup() {
  // запуск LCD
  lcd.init();
  // включаем подсветку
  lcd.backlight();
  // устанавливаем курсор
  lcd.setCursor(0, 0);
  // выводим сообщение
  lcd.print("Hello, World!");
}

void loop() { // выводим количество секунд с момента старта работы
  lcd.setCursor(0, 1);
  lcd.print(millis() / 100);
}
