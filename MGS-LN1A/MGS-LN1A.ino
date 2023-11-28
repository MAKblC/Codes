int pin = 35; 
/* 
на аналоговый пин ADC7 (цифровой адрес вывода - 35)
подключается аналоговый вывод Aout датчика MGS-LN1A
*/

void setup() {
 pinMode(pin, INPUT); 
 Serial.begin(115200);
}

void loop() {
 Serial.println(analogRead(pin));
 delay(10);
}