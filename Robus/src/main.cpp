#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);

  BoardInit();
}

void loop()
{
  SOFT_TIMER_Update();
}

/*void togglePIN4(void)
{
  static bool inverter = false;
  
  inverter = !inverter;
  digitalWrite(PIN5, inverter);
}*/