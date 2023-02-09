int pin = 19; // пин считывателя вентилятора
unsigned long duration; // переменная для считывания
#define wind 16 // пин вентилятора

void setup()
{
  Serial.begin(115200);
  pinMode(pin, INPUT);
  pinMode(wind, OUTPUT);
  digitalWrite(wind, HIGH);
}

void loop()
{
  duration = pulseIn(pin, HIGH); // функция считывания длительности импульсов
  Serial.println(duration);
  if (duration > 10000) {
    Serial.println("Неполадки с кулером. Проверьте питание или посторонние предметы вблизи кулера");
  }
  if (duration == 0) {
    Serial.println("Питание для вентилятора отсутствует. Проверьте подключение");
  }
}
