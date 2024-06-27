#include <Wire.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

void setupSensor() {
  // 1.) Акселерометр
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G);

  // 2.) Магнетометр
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Гироскоп
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial) {
    delay(1);
  }
  Serial.println("LSM9DS1 data read demo");
  if (!lsm.begin()) {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1)
      ;
  }
  Serial.println("Found LSM9DS1 9DOF");
  setupSensor();
}

void loop() {

  lsm.read();
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp);
  printAttitude(a.acceleration.x, a.acceleration.y, a.acceleration.z, m.magnetic.x, m.magnetic.y, m.magnetic.z);

  // Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(" m/s^2");
  // Serial.print("\tY: "); Serial.print(a.acceleration.y);     Serial.print(" m/s^2 ");
  // Serial.print("\tZ: "); Serial.print(a.acceleration.z);     Serial.println(" m/s^2 ");

  // Serial.print("Mag X: "); Serial.print(m.magnetic.x);   Serial.print(" uT");
  // Serial.print("\tY: "); Serial.print(m.magnetic.y);     Serial.print(" uT");
  // Serial.print("\tZ: "); Serial.print(m.magnetic.z);     Serial.println(" uT");

  // Serial.print("Gyro X: "); Serial.print(g.gyro.x);   Serial.print(" rad/s");
  // Serial.print("\tY: "); Serial.print(g.gyro.y);      Serial.print(" rad/s");
  // Serial.print("\tZ: "); Serial.print(g.gyro.z);      Serial.println(" rad/s");

  Serial.println();
  delay(200);
}


void printAttitude(float ax, float ay, float az, float mx, float my, float mz) {
  float roll = atan2(ay, az);
  float pitch = atan2(-ax, sqrt(ay * ay + az * az));

  float heading;
  if (my == 0)
    heading = (mx < 0) ? PI : 0;
  else
    heading = atan2(mx, my);
  // - 12 - магнитное отклонение
  heading -= 12 * PI / 180;

  if (heading > PI) heading -= (2 * PI);
  else if (heading < -PI) heading += (2 * PI);

  // конвертация в градусы
  heading *= 180.0 / PI;
  pitch *= 180.0 / PI;
  roll *= 180.0 / PI;

  Serial.print("Тангаж, Крен: ");
  Serial.print(pitch, 2);
  Serial.print(", ");
  Serial.println(roll, 2);
  Serial.print("Курс: ");
  Serial.println(heading, 2);
}