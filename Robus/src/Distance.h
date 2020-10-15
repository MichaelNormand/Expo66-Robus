#ifndef DISTANCE_H
#define DISTANCE_H

#include <Config.h>
#include <LibRobus.h>

void AddLength(int length);
void AddRotation(int angle, int direction);
void AddPulse(int pulse);
void UpdateMotors(void);
bool DistanceToGoal(int32_t goal, int dir0, int dir1);
float PID(int32_t encoder, float speed, int dir, bool motor, float *dataPID);

#endif