#include <ESP32_Servo.h>
Servo myservo;

void setup() {
  myservo.attach(19);      // пин сервомотора
}

void loop() {
  // поворот на угол
  myservo.write(170);
  delay(1000);
  myservo.write(10);
  delay(1000);

  //плавный поворот
  for (int i = 0; i < 181; i++) {
    myservo.write(i);
    delay(30);
  }
  for (int i = 180; i > 0; i--) {
    myservo.write(i);
    delay(30);
  }
}
