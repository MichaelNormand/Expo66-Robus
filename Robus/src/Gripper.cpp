#include <Gripper.h>

void Grab(void)
{
    ControlGripper(OPEN);
    ControlWrist(DOWN);
    ControlGripper(CLOSE);
    ControlWrist(UP);
}

void Release(void)
{
    ControlWrist(DOWN);
    ControlGripper(OPEN);
    ControlWrist(UP);
    ControlGripper(CLOSE);
}

void ControlGripper(int state)
{
    if (state == OPEN)
        SERVO_SetAngle(GRIPPER, 120);
    else
        SERVO_SetAngle(GRIPPER, 0);
}

void ControlWrist(int state)
{
  if (state == DOWN)
    SERVO_SetAngle(WRIST, DOWN_VAL);
  else
    SERVO_SetAngle(WRIST, UP_VAL);
}