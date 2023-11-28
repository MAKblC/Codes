int pin = 35; // аналоговый пин

void setup() {
 pinMode(pin, INPUT); 
 Serial.begin(115200);
}

void loop() {
 Serial.println(analogRead(pin));
 delay(10);
}