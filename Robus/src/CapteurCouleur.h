#include <Arduino.h>
#include "LibRobus.h"
#include "Adafruit_TCS34725.h"

#define COLOR_SAMPLE 1000

int COLORSENSOR_Update(Adafruit_TCS34725 tcs);
Adafruit_TCS34725 COLORSENSOR_Setup();