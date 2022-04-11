#include "PCA9536.h"
PCA9536 pca9536;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(115200);
  // Инициализация I2C и микросхемы управления реле
  Wire.begin();
  pca9536.reset();
  pca9536.setMode(IO_OUTPUT);
}

void loop() {
  // Включение реле методом бегущих огней
  pca9536.setState(IO0, IO_HIGH);
  pca9536.setState(IO1, IO_LOW);
  pca9536.setState(IO2, IO_LOW);
  pca9536.setState(IO3, IO_LOW);
  delay(1000);
  pca9536.setState(IO0, IO_LOW);
  pca9536.setState(IO1, IO_HIGH);
  pca9536.setState(IO2, IO_LOW);
  pca9536.setState(IO3, IO_LOW);
  delay(1000);
  pca9536.setState(IO0, IO_LOW);
  pca9536.setState(IO1, IO_LOW);
  pca9536.setState(IO2, IO_HIGH);
  pca9536.setState(IO3, IO_LOW);
  delay(1000);
  pca9536.setState(IO0, IO_LOW);
  pca9536.setState(IO1, IO_LOW);
  pca9536.setState(IO2, IO_LOW);
  pca9536.setState(IO3, IO_HIGH);
  delay(1000);
  pca9536.setState(IO_LOW);
  delay(1000);
  pca9536.setState(IO_HIGH);
  delay(1000);
  pca9536.setState(IO_LOW);
  delay(1000);
}
