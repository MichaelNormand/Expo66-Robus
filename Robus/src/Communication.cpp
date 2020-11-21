#include <Communication.h>

void Communication_Init(void)
{
  Wire.begin();
}

void DataRequest()
{
  static uint8_t data[16];
  int i = 0;

  Wire.requestFrom(8, 16);
  while(Wire.available())
  {
    data[i] = Wire.read();
    i++;
  }
  GetSetData(data, SET);
}