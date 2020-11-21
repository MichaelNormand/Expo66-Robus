#include <Arduino.h>
#include <Manual_Override.h>
#include <Communication.h>

void setup() {
  BoardInit();
  Communication_Init();
}
 
void loop() {
  static int32_t previousMillis = 0;
  int32_t currentMillis = millis();

  if(currentMillis - previousMillis > 20) 
  {
    previousMillis = currentMillis;
    DataRequest();
    RobusProcess();
  }
}



