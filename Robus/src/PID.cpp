#include <PID.h>

unsigned long lastCycle = 0;
unsigned long actualTime = 0;
unsigned long cycleDelay = 10;
float pids[2] = {0, 0};
float pid = 0.0;
float overflowLeft = 0.0;
float overflowRight = 0.0;
float encoderLeft = 0.0;
float encoderRight = 0.0;
float rightTraveledDistance = 0.0;
float leftTraveledDistance = 0.0;
float accelerationDistance = -1;
int32_t encoderRead = 0;
int32_t cycle = 1;
int32_t goal = 400;
int32_t actualSpeed = 0;
int32_t error = 0;
int32_t lastErrors[2] = {goal, goal};
int32_t lastError = 0;
int32_t nextError = 0;

void PID(int motorToCheck, float &encoder, int32_t actualGoal)
{
  encoderRead = ENCODER_ReadReset(motorToCheck);
  error = encoderRead - actualGoal;
  if (motorToCheck == 0 && overflowLeft > 0)
  {
    error += overflowLeft;
  }
  if (motorToCheck == 0 && overflowRight > 0)
  {
    error -= overflowRight;
  }
  if (motorToCheck == 1 && overflowLeft > 0)
  {
    error -= overflowLeft;
  }
  if (motorToCheck == 1 && overflowRight > 0)
  {
    error += overflowRight;
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

void ResetCycle()
{
  lastCycle = 0;
  actualTime = 0;
  cycleDelay = 10;
  pids[0] = 0;
  pids[1] = 0;
  pid = 0.0;
  overflowLeft = 0.0;
  overflowRight = 0.0;
  encoderLeft = 0.0;
  encoderRight = 0.0;
  rightTraveledDistance = 0.0;
  leftTraveledDistance = 0.0;
  accelerationDistance = -1;
  encoderRead = 0;
  cycle = 1;
  goal = 400;
  actualSpeed = 0;
  error = 0;
  lastErrors[0] = goal;
  lastErrors[1] = goal;
  lastError = 0;
  nextError = 0;
}

void RotateLeft(float angle)
{
  ResetCycle();
  float distanceForWheel = angle * 14.95;
  bool cycleFinished = false;
  while (!cycleFinished)
  {
    leftTraveledDistance += ENCODER_ReadReset(0);
    rightTraveledDistance += ENCODER_ReadReset(1);
    if (leftTraveledDistance >= distanceForWheel * -1)
    {
      MOTOR_SetSpeed(0, -0.15);
    }
    else
    {
      MOTOR_SetSpeed(0, 0);
    }
    if (rightTraveledDistance <= distanceForWheel)
    {
      MOTOR_SetSpeed(1, 0.15);
    }
    else
    {
      MOTOR_SetSpeed(1, 0);
    }
    if (leftTraveledDistance <= distanceForWheel * -1 && rightTraveledDistance >= distanceForWheel)
    {
      cycleFinished = true;
    }
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}

void RotateRight(float angle)
{
  ResetCycle();
  float distanceForWheel = angle * 14.95;
  bool cycleFinished = false;
  while (!cycleFinished)
  {
    leftTraveledDistance += ENCODER_ReadReset(0);
    rightTraveledDistance += ENCODER_ReadReset(1);
    if (leftTraveledDistance <= distanceForWheel)
    {
      MOTOR_SetSpeed(0, 0.15);
    }
    else
    {
      MOTOR_SetSpeed(0, 0);
    }
    if (rightTraveledDistance >= distanceForWheel * -1)
    {
      MOTOR_SetSpeed(1, -0.15);
    }
    else
    {
      MOTOR_SetSpeed(1, 0);
    }
    if (leftTraveledDistance >= distanceForWheel && rightTraveledDistance <= distanceForWheel * -1)
    {
      cycleFinished = true;
    }
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}

void GoForward(float distance)
{
  ResetCycle();
  distance = distance * 133.67;
  bool cycleFinish = false;
  bool canAccelerate = true;
  while (!cycleFinish)
  {
    actualTime = millis();
    if (actualTime - lastCycle > cycleDelay)
    {
      lastCycle = actualTime;
      PID(0, encoderLeft, actualSpeed);
      leftTraveledDistance += encoderLeft;
      PID(1, encoderRight, actualSpeed);
      rightTraveledDistance += encoderRight;
      if (encoderLeft > encoderRight)
      {
        overflowLeft = encoderLeft - encoderRight;
        overflowRight = 0.0;
      }
      else if (encoderRight > encoderLeft)
      {
        overflowRight = encoderRight - encoderLeft;
        overflowLeft = 0.0;
      }
      else
      {
        overflowLeft = 0.0;
        overflowRight = 0.0;
      }
      Serial.println("Motor 0: " + String(encoderLeft) + ". PID: " + pids[0]);
      Serial.println("Motor 1: " + String(encoderRight) + ". PID: " + pids[1]);
      if (leftTraveledDistance < distance)
      {
        MOTOR_SetSpeed(0, pids[0]);
      }
      else
      {
        MOTOR_SetSpeed(0, 0);
      }
      if (rightTraveledDistance < distance)
      {
        MOTOR_SetSpeed(1, pids[1]);
      }
      else
      {
        MOTOR_SetSpeed(1, 0);
      }
      if (rightTraveledDistance >= distance && leftTraveledDistance >= distance)
      {
        cycleFinish = true;
      }
      ++cycle;
      if (actualSpeed != goal && canAccelerate)
      {
        actualSpeed += 10;
      }
      if (!canAccelerate && actualSpeed > 60)
      {
        actualSpeed -= 10;
      }
      if ((leftTraveledDistance >= distance / 2 || rightTraveledDistance >= distance / 2) && canAccelerate)
      {
        if (actualSpeed < goal)
        {
          canAccelerate = false;
        }
      }
      if (actualSpeed >= goal - 10)
      {
        accelerationDistance = distance - (((leftTraveledDistance + rightTraveledDistance) / 2) * 0.5);
      }
      if ((leftTraveledDistance >= accelerationDistance || rightTraveledDistance >= accelerationDistance) && accelerationDistance != -1)
      {
        canAccelerate = false;
      }
    }
  }
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
}
