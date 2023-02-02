#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN 18
/* (количество рядов в матрице, количество
столбцов в матрице, количество соединенных матриц в ряд, количество соединенных матрицы в столбец, пин 18,
отсчет в матрице начинается снизу, отсчет в матрице начинается справа, отсчет идет по рядам, отсчет идет
прогрессивно(после 7 светодиода 8ой начинается с новой строки, тип светодиодов)*/
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, 1, 1, PIN, NEO_MATRIX_BOTTOM +
                            NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE, NEO_GRB +
                            NEO_KHZ800);

void setup() {
  matrix.begin(); // инициализация матрицы
  matrix.setTextWrap(false); // текст будет бежать «вне экрана»
  matrix.setBrightness(100); // яркость
  matrix.setTextColor( matrix.Color(255, 0, 6)); // текст красного цвета
  matrix.setFont(0); // шрифт по умолчанию
  Serial.begin(115200);
  delay(512);

}

void loop() {
  for (int curs = 8; curs > -75; curs--) { // 75 – длина строки
    matrix.fillScreen(matrix.Color(0, 0, 0)); // фон черный
    matrix.show();
    matrix.setCursor(curs, 0); // курсор сдвигается по оси Х в цикле
    matrix.print(utf8rus("Привет, Друг!")); // фразу писать в кавычках
    portDISABLE_INTERRUPTS(); // данная строка нужна для корректного отображения на esp32
    matrix.show();
    portENABLE_INTERRUPTS();// данная строка нужна для корректного отображения на esp32
    delay (100); // скорость «бега»
  }

}
 // для корректного отображения русских символов
String utf8rus(String source)
{ int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };
  k = source.length(); i = 0;
  while (i < k) {
    n = source[i]; i++;
    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) {
              n = 0xA8;
              break;
            }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x2F; //sometimes can be 0x30 instead 0x2F
            break;
          }
        case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) {
              n = 0xB8;
              break;
            }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x6F; //sometimes can be 0x70 instead 0x6F
            break;
          }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}
