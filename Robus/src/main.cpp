#include <Arduino.h>
#include "LibRobus.h"
#include "Distance.h"


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
}