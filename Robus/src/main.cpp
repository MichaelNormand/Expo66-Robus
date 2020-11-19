#include <Arduino.h>
<<<<<<< HEAD
#include "Timebase.h"
#include "LibRobus.h"

=======
#include <LibRobus.h>
#include <PID.h>
>>>>>>> 27925cd5596e63233a4a4ae68f016e0b1f0ca023
void setup()
{
  // put your setup code here, to run once:
  BoardInit();
<<<<<<< HEAD
=======
  Serial.begin(9600);
  GoForward(200);
  RotateRight(180);
  GoForward(200);
  RotateRight(180);
>>>>>>> 27925cd5596e63233a4a4ae68f016e0b1f0ca023
}

void loop()
{
<<<<<<< HEAD
  SOFT_TIMER_Update();
}
=======
}
>>>>>>> 27925cd5596e63233a4a4ae68f016e0b1f0ca023
