#define  button 4 // пин для подключения
int  buttonState; // переменная для хранения состояния кнопки

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
}

void loop() {
  buttonState = digitalRead(button); // проверяем состояние кнопки
  if (buttonState == LOW) {
    Serial.println ("ВКЛ");
  }
  else {
    Serial.println ("ВЫКЛ");
  }
  delay(200);
}
