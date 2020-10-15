#include <LibRobus.h>

#define PONCTUAL_CONSTANT 0.00001
#define INTEGRAL_CONSTANT 0
#define DERIVATIVE_CONSTANT 0.00025

unsigned long lastCycle = 0;
unsigned long actualTime = 0;
unsigned long cycleDelay = 10;
float pids[2] = {0, 0};
float pid = 0.0;
float overflowLeft = 0.0;
float overflowRight = 0.0;
float encoderLeft = 0.0;
float encoderRight = 0.0;
int32_t encoderRead = 0;
int32_t cycle = 1;
int32_t goal = 400;
int32_t actualSpeed = 10;
int32_t error = 0;
int32_t lastErrors[2] = {goal, goal};
int32_t lastError = 0;
int32_t nextError = 0;
int leftDirection = 1;
int rightDirection = 1;
float rightMotorTravel = 0.0;
float leftMotorTravel = 0.0;
float rightTraveledDistance = 0.0;
float leftTraveledDistance = 0.0;
int speedIncrease = 1;
float turningPoint = 0.0;

void PID(int motorToCheck, float &encoder, int direction);
bool AdjustOneCycle();
void SetDistanceToGoal(float requiredPulses, int leftMotorDirection, int rightMotorDirection);