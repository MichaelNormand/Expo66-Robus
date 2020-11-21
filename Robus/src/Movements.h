#ifndef MOVEMENTS_H
#define MOVEMENTS_H

#include <LibRobus.h>
#include <math.h>
#include <Arduino.h>
#include <PID.h>

int Move(float cm, bool dir, int state);
int Rotate(float deg, bool direction);
void SpeedUp(float *speed, float goal, float distance);
void SpeedDown(float *speed, float goal, float distance);

#endif