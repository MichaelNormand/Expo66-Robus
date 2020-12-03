#include <Arduino.h>
#include "Communication.h"
#include "Timebase.h"
#include "LibRobus.h"
#include "Sound.h"
#include "Sonar.h"
#include "SmartMovement.h"
#include "Manual_Override.h"
#include "Gripper.h"
#include "Sweep.h"

void DistanceCallback(float distance)
{
}

void RotateRightCallback(float angle)
{
  float rotate[4];
  rotate[DIS] = 0;
  rotate[DEG] = ANGLE;
  rotate[DIR] = RIGHT;
  rotate[STATE] = ROTATE;

  GetSetMove(rotate, SET);
}

void RotateLeftCallback(float angle)
{
  float rotate[4];
  rotate[DIS] = 0;
  rotate[DEG] = ANGLE;
  rotate[DIR] = LEFT;
  rotate[STATE] = ROTATE;

  GetSetMove(rotate, SET);
}

void SweepCallback()
{
  int status = INIT;
  GetSetSweepStatus(&status, SET);
}

void GrabCallback()
{
}

void ReleaseCallback()
{
}

void ObjectTypeRequestCallback()
{
}

void CycleCommunication()
{
  HandleBluetooth();
}

void IR_update(void);

void setup()
{
  BoardInit();
  sound_init();
  sonar_init();
  Communication_Init(DistanceCallback, RotateRightCallback, RotateLeftCallback, SweepCallback, GrabCallback, ReleaseCallback, ObjectTypeRequestCallback);

  //ControlWrist(DOWN);
  //delay(1000);
  timebase_add(RobusProcess, 20);
  //timebase_add(CycleCommunication, 20);
  timebase_add(DataRequest, 100);
  timebase_add(sonar_update, 20);
  timebase_add(sweep, 20);
  int status = INIT;
  GetSetSweepStatus(&status, SET);
}

void loop()
{
  /*
  static float move[4] = {0, 0, 0, 0};
  static bool initialized = false;

  if (initialized == false)
  {
    initialized = true;
    smart_align_init(100);
  }
  
  */
  SOFT_TIMER_Update();
}