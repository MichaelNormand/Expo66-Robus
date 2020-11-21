#ifndef PID_H
#define PID_H

#include <LibRobus.h>
#include <math.h>
#include <Arduino.h>
#include <Config.h>

#define STEP 0.02

#define KP 0.5

#define SPEED0 0.20
#define SPEED1 0.20

void PID(float *speed, float *encoder, int mode);

#endif