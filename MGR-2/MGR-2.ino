// подключенные к реле насос и вентилятор
// реле подключено к GP16/GP17
#define PUMP 16
#define WIND 17

void setup() {
  // пины реле на выход
  pinMode(PUMP, OUTPUT);
  pinMode(WIND, OUTPUT);
}

void loop() {
  digitalWrite(PUMP, HIGH);
  delay(1000);
  digitalWrite(PUMP, LOW);
  delay(1000);
  digitalWrite(WIND, HIGH);
  delay(1000);
  digitalWrite(WIND, LOW);
  delay(1000);
}
