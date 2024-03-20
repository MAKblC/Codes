#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
MPU6050 mpu;

uint8_t fifoBuffer[45];  // буфер

void setup() {
  Serial.begin(115200);
  Wire.begin();
  //Wire.setClock(1000000UL);   // разгоняем шину на максимум

  // инициализация DMP
  mpu.initialize();
  mpu.dmpInitialize();
  mpu.setDMPEnabled(true);
}

void loop() {
  static uint32_t tmr;
  if (millis() - tmr >= 11) {  // таймер на 11 мс (период готовности значений)
    if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
      // переменные для расчёта (ypr можно вынести в глобальеы переменные)
      Quaternion q;
      VectorFloat gravity;
      float ypr[3];

      // расчёты
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

      // выводим результат в радианах (-3.14, 3.14)
      /* Serial.print(ypr[0]); // вокруг оси Z
      Serial.print(',');
      Serial.print(ypr[1]); // вокруг оси Y
      Serial.print(',');
      Serial.print(ypr[2]); // вокруг оси X
      Serial.println();*/
      //float angle = map(ypr[0], -3.14,3.14,0,360);
      // для градусов можно использовать degrees()
      // вывод значений от 0 до 360
      Serial.println(map(degrees(ypr[0]), -180, 180, 0, 360));
      tmr = millis();  // сброс таймера
    }
  }
}