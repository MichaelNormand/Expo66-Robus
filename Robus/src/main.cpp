#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"

void ControlGripper(int state);

unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(9600);

  /*MOTOR_SetSpeed(0, 0.2);
  MOTOR_SetSpeed(1, 0.2);
  delay(1605);
  MOTOR_SetSpeed(0, 0);
  MOTOR_SetSpeed(1, 0);
  int pulse0 = ENCODER_Read(0);
  int pulse1 = ENCODER_Read(1);

  Serial.print("NOMBRE DE PULSE (0): ");
  Serial.println(pulse0);
  Serial.print("NOMBRE DE PULSE (1): ");
  Serial.println(pulse1);
  while(1);*/

  AddLength(30);
  AddRotation(90, ROTATE_RIGHT);
  AddLength(30);
  AddRotation(90, ROTATE_RIGHT);
  AddLength(30);
  AddRotation(90, ROTATE_RIGHT);
  AddLength(50);
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