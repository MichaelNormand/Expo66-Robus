#include <Arduino.h>
#include <LibRobus.h>
#include <PID.h>
void setup()
{
  // put your setup code here, to run once:
  BoardInit();
  Serial.begin(9600);
  GoForward(200);
  RotateRight(180);
  GoForward(200);
  RotateRight(180);
}

void loop()
{
}
