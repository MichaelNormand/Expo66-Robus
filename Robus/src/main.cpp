#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"
#include "Audio.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;
unsigned long previousMillis_audio = 0;

void setup()
{
  BoardInit();
  Serial.begin(9600);

  while(1){
    Serial.print("hi ?");
    delay(100);
  }
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long currentMillis_audio = millis();

  if (currentMillis - previousMillis > STEP)
  {
    previousMillis = currentMillis;
    UpdateMotors();
  }
  if (currentMillis_audio - previousMillis_audio > SAMPLE_AUDIO)
  {
    previousMillis_audio = currentMillis_audio;
    UpdateAudio();
  }
}

void ControlGripper(int state)
{
  if (state == OPENED)
    SERVO_SetAngle(1, 120);
  else
    SERVO_SetAngle(1, 0);
}