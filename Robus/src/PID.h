#ifndef PID_H
#define PID_H

#include <LibRobus.h>

#define PONCTUAL_CONSTANT 0.00001
#define INTEGRAL_CONSTANT 0
#define DERIVATIVE_CONSTANT 0.00025

void PID(int motorToCheck, float &encoder, int direction);
bool AdjustOneCycle();
void SetDistanceToGoal(float requiredPulses, int leftMotorDirection, int rightMotorDirection);

#endif