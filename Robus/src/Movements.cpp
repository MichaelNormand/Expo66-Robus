#include <Movements.h>

int Move(float cm, bool dir, int state)
{
  // 1 cm = 133.67 pulses
  float goal = cm * 133.6;
  static float distance = 0;
  static float speed[2] = {SPEED0, SPEED1};
  static float encoder[2] = {0, 0};

  if(distance < goal)
  {
    encoder[LEFT] = (float)ENCODER_ReadReset(LEFT);
    encoder[RIGHT] = (float)ENCODER_ReadReset(RIGHT);

    distance += ((encoder[LEFT] + encoder[RIGHT]) / 2) * dir;

    SpeedUp(speed, goal, distance);     
    SpeedDown(speed, goal, distance);
    
    PID(speed, encoder, AUTO);

    MOTOR_SetSpeed(LEFT, speed[LEFT] * dir);
    MOTOR_SetSpeed(RIGHT, speed[RIGHT] * dir);

    return NOT_DONE;
  }
  
  if(distance >= goal || state == STOP)
  {
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    distance = 0;
    speed[LEFT] = SPEED0;
    speed[RIGHT] = SPEED1;
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    return DONE;
  }
  
}

int Rotate(float deg, bool direction)
{
  // 1 deg = 8.88888 pulses
  float goal = deg * 33.3;
  static float distance = 0;
  static float speed[2] = {SPEED0, SPEED1};
  static float encoder[2] = {0, 0};
  float dirLeft;
  float dirRight;

  if(direction == LEFT)
  {
    dirLeft = -1;
    dirRight = 1;
  }
  else
  {
    dirLeft = 1;
    dirRight = -1;
  }
  
  if(distance < goal)
  {
    encoder[LEFT] = (float)ENCODER_ReadReset(LEFT);
    encoder[RIGHT] = (float)ENCODER_ReadReset(RIGHT);
    distance += ((encoder[LEFT] * dirLeft) + (encoder[RIGHT] * dirRight) / 2);

    SpeedUp(speed, goal, distance);
    SpeedDown(speed, goal, distance);

    //PID(speed, encoder, AUTO);  //À DEBUG (il accelere trop)

    MOTOR_SetSpeed(LEFT, speed[LEFT] * dirLeft);
    MOTOR_SetSpeed(RIGHT, speed[RIGHT] * dirRight);

    return NOT_DONE;
  }
  else
  {
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    distance = 0;
    speed[LEFT] = SPEED0;
    speed[RIGHT] = SPEED1;
    MOTOR_SetSpeed(LEFT, 0);
    MOTOR_SetSpeed(RIGHT, 0);
    return DONE;
  }
  
}

void SpeedUp(float *speed, float goal, float distance)
{
    if(distance < (goal * 0.25))
    {
      if(speed[LEFT] < 0.5)
        speed[LEFT] += 0.01;
      if(speed[RIGHT] < 0.5)
        speed[RIGHT] += 0.01;
    }
}

void SpeedDown(float *speed, float goal, float distance)
{
    if(distance > (goal * 0.75))
    {
      if(speed[LEFT] > 0.2)
        speed[LEFT] -= 0.01;
      if(speed[RIGHT] > 0.2)
        speed[RIGHT] -= 0.01;
      
    }
}
