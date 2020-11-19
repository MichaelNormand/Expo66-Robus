#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"
#include "Sound.h"

void IR_update(void);
void sonar_update(void);

void setup()
{
  sound_init();

  BoardInit();
  timebase_add(sound_play_object, 2000);
}

void loop()
{
  SOFT_TIMER_Update();
}

void IR_update(void)
{
  //Serial.print("IR data = ");
  //Serial.println(ROBUS_ReadIR(0));
  ROBUS_ReadIR(0);
}

void sonar_update(void)
{
  //Serial.print("SONAR data = ");
  //Serial.println(SONAR_GetRange(1));
  SONAR_GetRange(1);
}