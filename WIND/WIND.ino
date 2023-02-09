// в примере вентилятор подключен к реле MGR-2: https://github.com/MAKblC/Codes/tree/master/MGR-2

#define WIND 17

void setup() {
  // пины реле на выход
  pinMode(WIND, OUTPUT);
}

void loop() {
  digitalWrite(WIND, HIGH);
  delay(1000);
  digitalWrite(WIND, LOW);
  delay(1000);
}
