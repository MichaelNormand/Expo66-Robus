#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"
#include "Sound.h"
#include "Sonar.h"
#include "SmartMovement.h"
#include "Manual_Override.h"
#include "Gripper.h"
#include "Sweep.h"

void IR_update(void);

void setup()
{
  BoardInit();
  sound_init();

  ControlWrist(DOWN);
  delay(1000);
  timebase_add(RobusProcess, 20);
}

void loop()
{
  static float move[4] = {0, 0, 0, 0};
  static bool initialized = false;

 
  if(initialized == false)
  {
    initialized = true;
    smart_align_init(100);
  }

  SOFT_TIMER_Update();
}




