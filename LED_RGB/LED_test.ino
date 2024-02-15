#include <FastLED.h>                   // конфигурация матрицы    
//#include <FastLED_GFX.h>
//#include <FastLEDMatrix.h>
#define NUM_LEDS 64                    // количество светодиодов в матрице  
CRGB leds[NUM_LEDS];                   // определяем матрицу (FastLED библиотека)
#define LED_PIN             18         // пин к которому подключена матрица 
#define COLOR_ORDER         GRB        // порядок цветов матрицы 
#define CHIPSET             WS2812     // тип светодиодов    

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);    // конфигурация матрицы // matrix configuration
  FastLED.setBrightness(90); // яркость (0-255), не рекомендуется выставлять много, особенно при питании через USB
}

void loop() {
  fill_solid( leds, NUM_LEDS, CRGB(255, 0, 0));          // заполнить всю матрицу выбранным цветом
  FastLED.show();
  delay(500);
  fill_solid( leds, NUM_LEDS, CRGB(0, 255, 255));          // заполнить всю матрицу выбранным цветом
  FastLED.show();
  delay(500);
  fill_solid( leds, NUM_LEDS, CRGB(0, 0, 0));          // заполнить всю матрицу выбранным цветом
  FastLED.show();
  delay(500);
  // воспроизвести весь спектр цветов
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setHue(i * 255 / NUM_LEDS);
  }
  FastLED.show();
  delay(2000);
  FastLED.clear(); // очистить матрицу
  delay(500);
  leds[0].setRGB(255, 0, 0);   // RGB, 0-255
  leds[8].setRGB(255, 255, 0);   // RGB, 0-255
  FastLED.show();
  delay(2000);
  // бегущий огонь
  for (int i = 0; i < NUM_LEDS; i++) {
    FastLED.clear();
    leds[i].setHue(i * 255 / NUM_LEDS);
    FastLED.show();
    delay(100);
  }
}
