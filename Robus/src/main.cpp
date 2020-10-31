#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;
unsigned long AUDIO_previousMillis = 0;

void setup()
{
  //BoardInit();
  Serial.begin(9600);
  AUDIO_Setup();

  /*while(1){
    Serial.println("ssyt");
    delay(200);
  }*/
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long AUDIO_currentMillis = millis();

  if (currentMillis - previousMillis > STEP)
  {
    previousMillis = currentMillis;
    UpdateMotors();
  }
  if (AUDIO_currentMillis - AUDIO_previousMillis > AUDIO_SAMPLE)
  {
    AUDIO_previousMillis = AUDIO_currentMillis;
    AUDIO_Update();
    Serial.println(AUDIO_Status(false));
  }
}

void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}