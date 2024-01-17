#include <Wire.h>
#include <MGS_FR403.h>
MGS_FR403 Fire;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Fire.begin();
}

void loop() {
  Fire.get_ir_and_vis();
  Serial.print("ИК: ");
  Serial.println(String(Fire.ir_data, 1));
  Serial.print("Видимый: ");
  Serial.println(String(Fire.vis_data, 1));
  delay(500);
}
