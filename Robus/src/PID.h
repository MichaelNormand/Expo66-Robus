#ifndef PID_H
#include <LibRobus.h>

#define PONCTUAL_CONSTANT 0.00001
#define INTEGRAL_CONSTANT 0
#define DERIVATIVE_CONSTANT 0.00025

void PID(int motorToCheck, float &encoder, int32_t actualGoal);
void ResetCycle();
void RotateLeft(float angle);
void RotateRight(float angle);
void GoForward(float distance);
#endif