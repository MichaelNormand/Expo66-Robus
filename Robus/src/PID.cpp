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
int32_t goal = 200;
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

void PID(int motorToCheck, float &encoder)
{
  int direction = 1;
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
  PID(0, encoderLeft);
  PID(1, encoderRight);
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
  //Serial.println("Motor 0: " + String(encoderLeft) + ". PID: " + pids[0]);
  //Serial.println("Motor 1: " + String(encoderRight) + ". PID: " + pids[1]);
  MOTOR_SetSpeed(0, pids[0]);
  MOTOR_SetSpeed(1, pids[1]);
  ++cycle;
  if (actualSpeed != goal)
  {
    actualSpeed += 10;
  }
  return (leftTraveledDistance >= leftMotorTravel && rightTraveledDistance >= rightMotorTravel);
}

void SetDistanceToGoal(float requiredPulses, int leftMotorDirection, int rightMotorDirection) {

  Serial.print("requiredPulses = ");
  Serial.println(requiredPulses);
  Serial.print("leftMotorDirection = ");
  Serial.println(leftMotorDirection);
  Serial.print("rightMotorDirection = ");
  Serial.println(rightMotorDirection);
  Serial.println();

  leftDirection = leftMotorDirection;
  rightDirection = rightMotorDirection;
  rightMotorTravel = requiredPulses * rightMotorDirection;
  leftMotorTravel = requiredPulses * leftMotorDirection;
  leftTraveledDistance = 0.0;
  rightTraveledDistance = 0.0;
  actualSpeed = 10;
  lastErrors[0] = goal;
  lastErrors[1] = goal;
  pids[0] = 0;
  pids[1] = 0;
  cycle = 1;
  speedIncrease = 1;
}