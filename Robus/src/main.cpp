#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"


unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(9600);
  AddLength(50);
  AddRotation(90, ROTATE_LEFT);
  AddLength(50);
  AddRotation(90, ROTATE_LEFT);
  AddLength(50);
  AddRotation(90, ROTATE_LEFT);
  AddLength(50);
  AddRotation(90, ROTATE_LEFT);
}
 
void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > MOVE_SAMPLE_DELAY) {
    previousMillis = currentMillis;
    UpdateMotors();
  }
}