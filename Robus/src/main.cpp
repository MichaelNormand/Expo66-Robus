#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(9600);
  AddLength(115);
  AddRotation(90, ROTATE_LEFT);
  AddLength(90);
  AddRotation(95, ROTATE_RIGHT);
  AddLength(90);
  AddRotation(43, ROTATE_RIGHT);
  AddLength(180);
  AddRotation(87, ROTATE_LEFT);
  AddLength(65);
  AddRotation(32, ROTATE_RIGHT);
  AddLength(110);
  AddRotation(205, ROTATE_RIGHT);

  AddLength(110);
  AddRotation(32, ROTATE_LEFT);
  AddLength(65);
  AddRotation(90, ROTATE_RIGHT);
  AddLength(185);
  AddRotation(43, ROTATE_LEFT);
  AddLength(85);
  AddRotation(90, ROTATE_LEFT);
  AddLength(80);
  AddRotation(90, ROTATE_RIGHT);
  AddLength(115);

}
 
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > STEP) {
    previousMillis = currentMillis;
    UpdateMotors();
  }
}

void ControlGripper(int state)
{ 
  if(state == OPENED)
    SERVO_SetAngle(1, 120);  
  else
    SERVO_SetAngle(1, 0);  
}