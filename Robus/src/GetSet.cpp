#include <GetSet.h>


void GetSetMove(float *move, int action)
{
  static float temp[4] = {0, 0, 0, STOP};
  if(action == SET)
  {
    for(int i = 0; i < 4; i++)
      temp[i] = move[i];
  }

  if(action == GET)
  {
    for(int i = 0; i < 4; i++)
      move[i] = temp[i];
  }
}

void GetSetData(uint8_t *data, int action)
{
  static uint8_t temp[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  if(action == SET)
  {
    for(int i = 0; i < 16; i++)
      temp[i] = data[i];
  }

  if(action == GET)
  {
    for(int i = 0; i < 16; i++)
      data[i] = temp[i];
  }
}

void GetSetAngle(float *angle, int action)
{ 
  static float temp = 0;
  if(action == SET)
    temp = *angle;
  if(action == GET)
    *angle = temp;
}

void GetSetSweepStatus(int *status, int action)
{ 
  static int sweepStatus = 0;
  if(action == SET)
    sweepStatus = *status;
  if(action == GET)
    *status = sweepStatus;
}