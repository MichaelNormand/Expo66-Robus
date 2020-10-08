#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(9600);
  AddPulse(3200);
}
 
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > MOVE_SAMPLE_DELAY) {
    previousMillis = currentMillis;
    UpdateMotors();
  }

  // ControlGripper(OPENED);
  // delay(2000);
  // ControlGripper(CLOSED);
  // delay(2000);
}

void ControlGripper(int state)
{ 
  if(state == OPENED)
    SERVO_SetAngle(1, 120);  
  else
    SERVO_SetAngle(1, 0);  
}