#include <PID.h>
bool cyclesFinished = false;
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

void PID(int motorToCheck, float &encoder, int direction)
{
  encoderRead = ENCODER_ReadReset(motorToCheck);
  error = encoderRead - (actualSpeed * direction);
  if (motorToCheck == 0 && overflowLeft > 0)
  {
    error += (overflowLeft * direction);
  }
  if (motorToCheck == 0 && overflowRight > 0)
  {
    error -= (overflowRight * direction);
  }
  if (motorToCheck == 1 && overflowLeft > 0)
  {
    error -= (overflowLeft * direction);
  }
  if (motorToCheck == 1 && overflowRight > 0)
  {
    error += (overflowRight * direction);
  }
  encoder = encoderRead;
  lastError = lastErrors[motorToCheck];
  nextError = (error - lastError) * (cycle + 1) + (error - ((error - lastError) * (cycle)));
  pid = pids[motorToCheck] - ((PONCTUAL_CONSTANT * error) + (INTEGRAL_CONSTANT * lastError) + (DERIVATIVE_CONSTANT * nextError));
  //Serial.println("Motor " + String(motorToCheck) + ". Encoder: " + String(encoderRead) + ".");
  if (pid > 1)
  {
    pid = 1;
  }
  if (pid < -1)
  {
    pid = -1;
  }
  pids[motorToCheck] = pid;
  lastErrors[motorToCheck] = error;
}

bool AdjustOneCycle()
{
  PID(0, encoderLeft, leftDirection);
  PID(1, encoderRight, rightDirection);
  leftTraveledDistance += encoderLeft;
  rightTraveledDistance += encoderRight;
  if (encoderLeft > encoderRight && leftDirection == rightDirection)
  {
    overflowLeft = encoderLeft - encoderRight;
    overflowRight = 0.0;
  }
  else if (encoderRight > encoderLeft && leftDirection == rightDirection)
  {
    overflowRight = encoderRight - encoderLeft;
    overflowLeft = 0.0;
  }
  else if (encoderLeft * -1 > encoderRight && leftDirection < rightDirection)
  {
    overflowLeft = encoderLeft - encoderRight;
    overflowRight = 0.0;
  }
  else if (encoderRight * -1 > encoderLeft && leftDirection < rightDirection)
  {
    overflowRight = encoderRight - encoderLeft;
    overflowLeft = 0.0;
  }
  else if (encoderLeft > encoderRight * -1 && leftDirection > rightDirection)
  {
    overflowLeft = encoderLeft - encoderRight;
    overflowRight = 0.0;
  }
  else if (encoderRight > encoderLeft * -1 && leftDirection > rightDirection)
  {
    overflowRight = encoderRight - encoderLeft;
    overflowLeft = 0.0;
  }
  else
  {
    overflowLeft = 0.0;
    overflowRight = 0.0;
  }
  //Serial.println("Motor 0: " + String(encoderLeft) + ". PID: " + pids[0]);
  //Serial.println("Motor 1: " + String(encoderRight) + ". PID: " + pids[1]);
  if (leftTraveledDistance <= leftMotorTravel) {
    MOTOR_SetSpeed(0, pids[0]);
  } else {
    MOTOR_SetSpeed(0, 0);
  }
  if (rightTraveledDistance <= rightMotorTravel) {
    MOTOR_SetSpeed(1, pids[1]);
  } else {
    MOTOR_SetSpeed(1, 0);
  }
  ++cycle;
  if (actualSpeed != goal && actualSpeed > 0 && leftTraveledDistance < leftMotorTravel && rightTraveledDistance < rightMotorTravel)
  {
    actualSpeed += 10 * speedIncrease;
  }
  if (actualSpeed < goal - 5 && rightTraveledDistance >= rightMotorTravel / 2 || leftTraveledDistance >= leftMotorTravel / 2) {
    speedIncrease = -1;
  }
  else if (actualSpeed >= goal - 5) {
    if (rightTraveledDistance >= leftTraveledDistance) {
      turningPoint = rightMotorTravel - rightTraveledDistance;
    } else if (rightTraveledDistance <= leftTraveledDistance) {
      turningPoint = rightMotorTravel - leftTraveledDistance;
    }
  }
  return (leftTraveledDistance <= leftMotorTravel && rightTraveledDistance <= rightMotorTravel);
}

void SetDistanceToGoal(float requiredPulses, int leftMotorDirection, int rightMotorDirection) {
  leftDirection = leftMotorDirection;
  rightDirection = rightMotorDirection;
  rightMotorTravel = requiredPulses * rightMotorDirection;
  leftMotorTravel = requiredPulses * leftMotorDirection;
  leftTraveledDistance = 0.0;
  rightTraveledDistance = 0.0;
  actualSpeed = 10;
  lastErrors[0] = goal;
  lastErrors[1] = goal;
}