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
  ControlGripper(OPEN);
  Serial.println("IAROMYR");
  delay(1000);

  timebase_add(RobusProcess, 20);
}

void loop()
{
  static bool initialized = false;

  if(initialized == false)
  {
    if(smart_align_init(100) == true)
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
