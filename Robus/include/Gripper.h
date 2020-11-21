#ifndef GRIPPER_H
#define GRIPPER_H

#include <Config.h>
#include <LibRobus.h>
#include <Arduino.h>

void Grab(void);
void Release (void);
void ControlGripper(int state);
void ControlWrist(int state);

#endif