#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"

void setup()
{
  BoardInit();
}

void loop()
{
  SOFT_TIMER_Update();
}