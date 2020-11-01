#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"
#include "Ball.h"
#include "Sonar.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;
unsigned long AUDIO_previousMillis = 0;
unsigned long SONAR_previousMillis = 0;

void setup()
{
  BoardInit();
  BALL_Init();
  //Serial.begin(9600);
  AUDIO_Init();
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long AUDIO_currentMillis = millis();
  unsigned long SONAR_currentMillis = millis();
  static bool started = false;

  if (currentMillis - previousMillis > STEP)
  {
    previousMillis = currentMillis;
    MOTOR_Update();
  }
  if (AUDIO_currentMillis - AUDIO_previousMillis > AUDIO_SAMPLE)
  {
    AUDIO_previousMillis = AUDIO_currentMillis;
    AUDIO_Update();
    //Serial.println(AUDIO_Status(false));
  }
  if (SONAR_currentMillis - SONAR_previousMillis > AUDIO_SAMPLE)
  {
    SONAR_previousMillis = SONAR_currentMillis;
    SONAR_Update();
  }

  if(started == false && AUDIO_Status(false) == true)
  {
    started = true;
    //BALL_Init();
    MOTOR_Abort();
  }

}

void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}