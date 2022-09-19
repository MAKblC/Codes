// Подключите устройство к I2C (21/22)
#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial);
  Serial.println("\nI2C Сканер");
}

void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Сканирую...");

  nDevices = 0;
  for (address = 8; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C устройство найдено по адресу 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Неизвестное устройство по адресу 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("Не найдено I2C устройств\n");
  else
    Serial.println("готово!\n");

  delay(5000);
}
