#include <Distance.h>

bool DistanceToGoal(int32_t goal, int dir0, int dir1)
{
  static float dataPID[4] = {0, 0, 0, 0};    // {cumError0, lastError0, cumError1, lastError1} -> for Integral and Derivative

  static int32_t now;
  static int32_t before = 0;

  static float speed0 = SPEED0;
  static float speed1 = SPEED1;
  
  static int32_t distance = 0;
  static int32_t encoder0;
  static int32_t encoder1;

  if(distance < goal)                  // Keep moving if the distance isn't reached.
  {
    MOTOR_SetSpeed(0, dir0 * speed0);
    MOTOR_SetSpeed(1, dir1 * speed1);

    now = millis();                        

    if(now - before >= STEP)           // True every STEP (10ms).
    {
      before = now;

      encoder0 = ENCODER_Read(0) * dir0;
      encoder1 = ENCODER_Read(1) * dir1;

      speed0 = PID(encoder0, speed0, dir0, MOTOR0, dataPID);  // Adjusted Speed.
      speed1 = PID(encoder1, speed1, dir1, MOTOR1, dataPID);  

      distance += (encoder0 + encoder1)/2;                    // Keep track of distance (average distance traveled of both wheel)

      ENCODER_Reset(0);
      ENCODER_Reset(1);
    }
    return NOT_DONE;
  }

  else
  {
    MOTOR_SetSpeed(0, 0);
    MOTOR_SetSpeed(1, 0);

    ENCODER_Reset(0);
    ENCODER_Reset(1);
 
    speed0 = SPEED0;
    speed1 = SPEED1;

    distance = 0;

    //See data after movement
    // for(int i = 0; i < 4; i++)
    // {
    //   Serial.print(dataPID[i]);
    //   Serial.print("   ");
    // } 
    // Serial.println("");

    for(int i = 0; i < 4; i++)
     dataPID[i] = 0;

    return DONE; 
  }
}



float PID(int32_t encoder, float speed, int dir, bool motor, float *dataPID)
{
  float lastError;
  float cumError;

  float rateError;

  float error = (float)(RPS - encoder);  // Error each STEP.

  if(motor == MOTOR0)
  {
    dataPID[0] += error * STEP / 1000;   // Cumulated error over time (in sec).
    cumError = dataPID[0];
    lastError = dataPID[1];
  }
  else
  {
    dataPID[2] += error * STEP / 1000;
    cumError = dataPID[2]; 
    lastError = dataPID[3];
  }

  rateError = (error - lastError) / STEP / 1000;   // Error's rate of change every STEP (in sec).

  if(motor == MOTOR0)                              // Keep track of error for derivative.
    dataPID[1] = error;
  else
    dataPID[3] = error;                               

  speed = speed + (KP * error) + (KI * cumError) + (KD * rateError); // Adjust speed in function of error.

  if(speed > 1)
    speed = 1;

  return speed;    // Return new speed.        
}           
