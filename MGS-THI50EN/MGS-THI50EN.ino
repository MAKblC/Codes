#include <Wire.h>
#include <MCP3221.h>
#include <Adafruit_MCP9808.h>

MCP3221 mcp3221_5(0x49); // Адрес может отличаться(также попробуйте просканировать адрес: https://github.com/MAKblC/Codes/tree/master/I2C%20scanner)

int a = 2248; // масштабирование значений
int b = 1165;
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

void setup()
{
  Serial.begin(115200);
  Wire.begin();
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


