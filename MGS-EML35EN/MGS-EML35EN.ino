#include <Wire.h>
#include <SC18IS602.h>
SC18IS602 i2cspi = SC18IS602(SC18IS602_ADDRESS_000);

float energy_data = 0;
float dist_data   = 0;
float noise_counter = 0;
float disturber_counter = 0;
float lightning_counter = 0;

void setup()
{
  // Инициализация последовательного порта
  Serial.begin(115200);

  // Инициализация микросхемы SPI
  i2cspi.begin(SC18IS602_SS_2);
  i2cspi.setBitOrder(MSBFIRST);
  i2cspi.setDataMode(SC18IS602_SPI_MODE1);
  i2cspi.setClockDivider(SC18IS602_CLOCK_58K);

  // Инициализация датчика
  if (!(init_as3935()))
    Serial.println("Sensor not found!");
  delay(500);

  // Вывод начальных значений
  Serial.println("ENERGY   = " + String(energy_data, 1));
  Serial.println("DISTANCE = " + String(dist_data, 1));
  Serial.println("NOISE COUNTER = " + String(noise_counter, 1));
  Serial.println("DISTURBER COUNTER = " + String(disturber_counter, 1));
  Serial.println("LIGHTNING COUNTER = " + String(lightning_counter, 1));
  Serial.println();
}

void loop()
{
  // Измерение
  if (poll_sensor()) // Выводить данные, только если возникло событие
  {
    // Вывод измеренных значений в терминал
    Serial.println("ENERGY   = " + String(energy_data, 1));
    Serial.println("DISTANCE = " + String(dist_data, 1));
    Serial.println("NOISE COUNTER = " + String(noise_counter, 1));
    Serial.println("DISTURBER COUNTER = " + String(disturber_counter, 1));
    Serial.println("LIGHTNING COUNTER = " + String(lightning_counter, 1));
    Serial.println();
  }
}

// Инициализация датчика
int init_as3935()
{
  uint8_t result = 0x00;
  uint8_t data[] = {0x00, 0x00};
  uint8_t init_flag = 0;

  // Инициализцаия и установка значений регистров по умолчанию
  data[0] = 0x3C;
  data[1] = 0x96;
  result = i2cspi.transfer(data, 0x02);
  if (result == 0x02)
    init_flag = 1;
  else
    init_flag = 0;
  return init_flag;
}

// Получение данных с датчика
int poll_sensor()
{
  uint8_t result = 0x00;
  uint8_t data[] = {0x00, 0x00};
  uint8_t int_flag = 0;
  // Чтение регистра прерываний 0x03
  data[0] = 0x03 | 0b01000000;
  data[1] = 0xFF;
  result = i2cspi.transfer(data, 0x02);
  // Если возникло прерывание, то определяем какое, увеличиваем счетчики и считывание другие регистры
  if (data[1] & 0b1111)
  {
    int_flag = 1;

    // Подсчет событий
    if (data[1] & 0b1)
      noise_counter = noise_counter + 1;
    if (data[1] & 0b100)
      disturber_counter = disturber_counter + 1;
    if (data[1] & 0b1000)
      lightning_counter = lightning_counter + 1;

    // Энергия разряда
    data[0] = 0x04 | 0b01000000;
    data[1] = 0xFF;
    result = i2cspi.transfer(data, 0x02);
    energy_data = data[1];
    // Serial.println(data[1]);
    data[0] = 0x05 | 0b01000000;
    data[1] = 0xFF;
    result = i2cspi.transfer(data, 0x02);
    energy_data = energy_data + ((float)data[1]) * 256.0;
    // Serial.println(data[1]);
    data[0] = 0x06 | 0b01000000;
    data[1] = 0xFF;
    result = i2cspi.transfer(data, 0x02);
    energy_data = energy_data + ((float)data[1]) * 65536.0;
    // Serial.println(data[1]);

    // Расстояния до разряда
    data[0] = 0x07 | 0b01000000;
    data[1] = 0xFF;
    result = i2cspi.transfer(data, 0x02);
    dist_data = data[1];
  }
  return int_flag;
}
