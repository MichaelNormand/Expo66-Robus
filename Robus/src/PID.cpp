#include <PID.h>

void PID(int motorToCheck, float &encoder)
{
  encoderRead = ENCODER_ReadReset(motorToCheck);
  error = encoderRead - actualSpeed;
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

void AdjustOneCycle()
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
}