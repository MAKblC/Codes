#include <Wire.h>
#include <MCP3221.h>
#include <Adafruit_MCP9808.h>
byte ADDR;
MCP3221 mcp3221_5(ADDR);
int a = 2248; // масштабирование значений
int b = 1165;
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  ADDR = scan(); // скан адреса
  Serial.println(" АДРЕС:");
  Serial.println(ADDR, HEX);
  mcp3221_5.setAddress(ADDR);
  
  mcp3221_5.setAlpha(DEFAULT_ALPHA);
  mcp3221_5.setNumSamples(DEFAULT_NUM_SAMPLES);
  mcp3221_5.setSmoothing(ROLLING_AVG);
  
  if (!tempsensor.begin(0x18))
  {
    Serial.println("Couldn't find MCP9808!");
    while (1);
  }
  tempsensor.setResolution(3);

}

void loop()
{
  tempsensor.wake();
  float t1 = tempsensor.readTempC();
  float h1 = mcp3221_5.getData();
  h1 = map(h1, a, b, 0, 100);
  Serial.println(h1);
  Serial.println(t1);
  delay(500);
}

byte scan() { // сканирование адреса
  byte error, address;
  Serial.println("Сканирую...");
  for (address = 8; address < 127; address++ ) {
	if (address == 0x18) continue; // пропускаем адрес датчика температуры
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C устройство найдено по адресу 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      return address;
      Serial.println(" !");
      break;
    }
  }
}

