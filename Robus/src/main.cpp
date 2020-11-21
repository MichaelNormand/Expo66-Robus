#include <Arduino.h>
#include "Timebase.h"
#include "LibRobus.h"
#include "Sound.h"
#include "Sonar.h"
#include "SmartMovement.h"
#include "Manual_Override.h"
#include "Gripper.h"

void IR_update(void);
void sonar_update(void);

void setup()
{
  sound_init();

  BoardInit();

  ControlWrist(DOWN);

  delay(3000);

  Serial.println("IAROMYR");
  timebase_add(RobusProcess, 20);
  //timebase_add(sound_play_object, 2000);
  //timebase_add(sonar_update, 150);
}

void loop()
{
  static bool initialized = false;

  if(initialized == false)
  {
    if(smart_movement_init() == true)
      initialized = true;
  }

  SOFT_TIMER_Update();
}

void IR_update(void)
{
  //Serial.print("IR data = ");
  //Serial.println(ROBUS_ReadIR(0));
  ROBUS_ReadIR(0);
}
