#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"


unsigned long previousMillis = 0;


void setup() {
  BoardInit();
  Serial.begin(9600);
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
}