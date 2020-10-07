#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(115200);

  // SERVO_Enable(1);

  AddRotation(45, ROTATE_LEFT);
  AddLength(30);
  AddRotation(180, ROTATE_RIGHT);
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