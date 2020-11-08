#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"
#include "Ball.h"
#include "IR.h"
#include "Keel.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;
unsigned long AUDIO_previousMillis = 0;
unsigned long IR_previousMillis = 0;

void setup()
{
  BoardInit();
  AUDIO_Init();
  IR_Init();
  //AddLength(-30);
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long AUDIO_currentMillis = millis();
  unsigned long IR_currentMillis = millis();
  static bool AUDIO_started = false;
  static bool IR_started = false;

  if (currentMillis - previousMillis > STEP)
  {
    previousMillis = currentMillis;
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

  if(AUDIO_started == false && AUDIO_Status(false) == true)
  {
    AUDIO_started = true;
    KEEL_Init();
  }
  if(AUDIO_started == true && IR_started == false && IR_Status(false) == true)
  {
    IR_started = true;
    //AddLength(450 - MOTOR_Traveled());  
    MOTOR_Update(true);
  }
}








void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}