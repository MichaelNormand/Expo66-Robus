#include <Manual_Override.h>

#define ACTIVATED 66
#define DEACTIVATED 99
#define CHEATCODE 420

void RobusProcess(void)
{
  static uint8_t data[16];
  static float speed[2] = {SPEED0, SPEED1};
  static float iaromyr = OFF;
  static float  move[4]; /*= {0, 90, LEFT, ROTATE}*/

  GetSetData(data, GET);

  // if(data[SHARE] == 1)
  //   iaromyr = OFF;

  // if(iaromyr == OFF)
  // {
  //   if(CheatCode(data) == ACTIVATED)
  //     iaromyr = ON;
  // }
  // else  
  // {
    if(ManualOverride(data, speed) == AUTO)
    {
      GetSetMove(move, GET);
      if(move[STATE] == FORWARD)
      {
        if(Move(move[DIS], 1) == DONE)
        {
          move[STATE] = STOP;
          GetSetMove(move, SET);
        }
      }
      if(move[STATE] == ROTATE)
      {
        if(Rotate(move[DEG], move[DIR]) == DONE)
        {
          move[STATE] = STOP;
          GetSetMove(move, SET);
        }
      }
    }
  // }
}

int CheatCode(uint8_t *data)
{
  //CHEAT CODE LIES BELOW ( X X C T S S S L U X D )

  static int key = 0;
  static double cheatcode = 0;

  MOTOR_SetSpeed(LEFT, 0);
  MOTOR_SetSpeed(RIGHT, 0);

  if(data[OPTIONS] == 1)
  {
    Serial.println("RESET");
    key = 0;
    cheatcode = 0;
  }

  if(data[CROSS] == 1)
  {
    key++;
    cheatcode += 2; //1: 2 x CROSS  (4)   10: 1 x CROSS (10)
  }

  if(data[CIRCLE] == 1)
  {
    key++;
    cheatcode *= 3; //3: 1 x CIRCLE (12)
  }

  if(data[TRIANGLE] == 1)
  {
    key++;
    cheatcode /= 12; //4: 1 x TRIANGLE  (1)
  }

  if(data[SQUARE] == 1)
  {
    key++;
    cheatcode *= 69; //5: 3 x SQUARE  (328'509)
  }

  if(data[A_LEFT] == 1)
  {
    key++;
    cheatcode += 226851; //8: 1 x A_LEFT  (555'360)
  }

  if(data[A_RIGHT] == 1)
  {
    key++;            
    cheatcode = 0;  //?: 0 x HONEY POT
  }

  if(data[A_UP] == 1)
  {
    key++;        
    cheatcode /= 69420; //9: 1 x A_UP (8)
  }

  if(data[A_DOWN] == 1)
  {
    key++;        
    cheatcode *= 42; //11: 1 x A_DOWN (420)
  }

  for(int i = 0; i < 16; i++)
    data[i] = 0;

  if(cheatcode == CHEATCODE && key == 11)
  {
    cheatcode = 0;
    key = 0;
    return ACTIVATED;
  }
  return DEACTIVATED;
}

int ManualOverride(uint8_t *data, float *speed)
{
  static int pressed = 0;
  static float encoder[2] = {0, 0};
  static bool reset;

  if(data[CROSS] == 1)
  {
    data[CROSS] = 0;
    pressed++;
  }

  if((pressed & 0x01) == 1)
  {
    reset = true;
    ManualGripping(data);
    Acceleration(data, speed);
    encoder[LEFT] = (float)ENCODER_ReadReset(LEFT);
    encoder[RIGHT] = (float)ENCODER_ReadReset(RIGHT);
    PID(speed, encoder, MANUAL);                      
    ManualDrive(data, speed);
    MOTOR_SetSpeed(LEFT, speed[LEFT]);
    MOTOR_SetSpeed(RIGHT, speed[RIGHT]);
    return MANUAL;
  }

  if(reset == true)
  {
    reset = false;
    speed[LEFT] = SPEED0;
    speed[RIGHT] = SPEED1;
    ENCODER_ReadReset(LEFT);
    ENCODER_ReadReset(RIGHT);
    encoder[LEFT] = 0;
    encoder[RIGHT] = 0;
  }
  return AUTO;
}

void ManualGripping(uint8_t *data)
{
  static int pressedGripper = 0;
  static int pressedWrist = 0;

  if(data[CIRCLE] == 1)
  {
    data[CIRCLE] = 0;
    pressedGripper++;
  }

  if(data[TRIANGLE] == 1)
  {
    data[TRIANGLE] = 0;
    pressedWrist++;
  }

  if((pressedGripper & 0x01) == OPEN)
    ControlGripper(OPEN);
  else
    ControlGripper(CLOSE);

  if((pressedWrist & 0x01) == 1)
    ControlWrist(DOWN);
  else
    ControlWrist(UP); 
}

void Acceleration(uint8_t *data, float *speed)
{
  speed[LEFT] = (data[R2] / 255) * 0.75;
  speed[RIGHT] = speed[LEFT];
}

void ManualDrive(uint8_t *data, float *speed)
{
  double dir;
  double theta0;
  double theta1;

  double X = (double)(data[LEFTHATX] - 127);
  double Y = (double)(data[LEFTHATY] - 127) * -1;

  double speedMag = min(127, sqrt(X * X + Y * Y));

  if(Y >= 10)
    dir = 1;
  if(Y <= -10)
    dir = -1; 
  
  theta1 =  180 / PI * acos(X / sqrt(X * X + Y * Y));
  theta0 = 180 - theta1;

  speed[LEFT] = speed[LEFT] * (float)((speedMag / 127) * min(1, (theta0 / 90)) * dir);
  speed[RIGHT] = speed[RIGHT] * (float)((speedMag / 127) * min(1, (theta1 / 90)) * dir);
}

