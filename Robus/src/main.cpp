#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"

void setup()
{
  // put your setup code here, to run once:
  BoardInit();
}

void loop()
{
  SOFT_TIMER_Update();
}
