#include <Arduino.h>
#include <Distance.h>
 
void setup() {
  BoardInit();
  Serial.begin(115200);
}
 
void loop() {
    while(DistanceToGoal(20000, 1, 1));
    delay(500);
    // while(DistanceToGoal(3200, -1, 1));
    // delay(500);
    // while(DistanceToGoal(3200, 1, -1));
    // delay(500);
    while(DistanceToGoal(20000, -1, -1));
    delay(500);
}