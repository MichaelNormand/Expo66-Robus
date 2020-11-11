#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"
#include "Ball.h"
#include "IR.h"
#include "Keel.h"

void ControlGripper(int state);

unsigned long MOTOR_previousMillis = 0;
unsigned long AUDIO_previousMillis = 0;
unsigned long IR_previousMillis = 0;

void setup()
{
  BoardInit();
  AUDIO_Init();
  IR_Init();
}

void loop()
{
  unsigned long MOTOR_currentMillis = millis();
  unsigned long AUDIO_currentMillis = millis();
  unsigned long IR_currentMillis = millis();
  static bool AUDIO_started = false;
  static bool IR_started = false;

  //Constant checks
  if (MOTOR_currentMillis - MOTOR_previousMillis > STEP)
  {
    MOTOR_previousMillis = MOTOR_currentMillis;
    MOTOR_Update(false);
  }
  if (AUDIO_currentMillis - AUDIO_previousMillis > AUDIO_SAMPLE)
  {
    AUDIO_previousMillis = AUDIO_currentMillis;
    AUDIO_Update();
  }
  if (IR_currentMillis - IR_previousMillis > AUDIO_SAMPLE)
  {
    IR_previousMillis = IR_currentMillis;
    if(AUDIO_started == true)
      IR_Update();
  }

  //Check if 5kHz was detected
  if(AUDIO_started == false && AUDIO_Status(false) == true)
  {
    AUDIO_started = true;
    KEEL_Init();
  }

  //Check if keel was detected
  if(AUDIO_started == true && IR_started == false && IR_Status(IR_GET_INFO) > 0)
  {
    IR_started = true;
    MOTOR_Update(true);

    if(IR_Status(IR_GET_INFO) == IR_ZONE_2)
    {
      while(1)
      {
        //delay(10);

        if(IR_Wait())
        {
          delay(8000);
          break;
        }
      }
    }

  }
}








void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}