#ifndef DISTANCE_H
#define DISTANCE_H

#include <Config.h>
#include <LibRobus.h>

float PID(int32_t encoder, float speed, int dir, bool motor, float *dataPID);
bool DistanceToGoal(int32_t goal, int dir0, int dir1);

#endif