#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"
#include "Ball.h"
#include "CapteurCouleur.h"
#include "Adafruit_TCS34725.h"

Adafruit_TCS34725 tcs;
void ControlGripper(int state);

unsigned long previousMillis = 0;
unsigned long AUDIO_previousMillis = 0;
unsigned long COLOR_previousMillis = 0;


void setup()
{
  BoardInit();
  //Serial.begin(9600);
  AUDIO_Init();
  tcs = COLORSENSOR_Setup();
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long AUDIO_currentMillis = millis();
  unsigned long COLOR_currentMillis = millis();
  static bool started = false;

  if (currentMillis - previousMillis > STEP)
  {
    previousMillis = currentMillis;
    UpdateMotors();
  }
  if (AUDIO_currentMillis - AUDIO_previousMillis > AUDIO_SAMPLE)
  {
    AUDIO_previousMillis = AUDIO_currentMillis;
    AUDIO_Update();
    //Serial.println(AUDIO_Status(false));
  }
  if (COLOR_currentMillis - COLOR_previousMillis > COLOR_SAMPLE)
  {
    COLOR_previousMillis = COLOR_currentMillis;
    COLORSENSOR_Update(tcs);
    //Serial.println(AUDIO_Status(false));
  }
  if(started == false && AUDIO_Status(false) == true)
  {
    started = true;
    //BALL_Init();
  }

}

void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}