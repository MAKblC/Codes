// в примере насос подключен к реле MGR-2: https://github.com/MAKblC/Codes/tree/master/MGR-2

#define PUMP 16

void setup() {
  // пины реле на выход
  pinMode(PUMP, OUTPUT);
}

void loop() {
  digitalWrite(PUMP, HIGH);
  delay(1000);
  digitalWrite(PUMP, LOW);
  delay(1000);
}
