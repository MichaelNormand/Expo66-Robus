#ifndef MANUAL_OVERRIDE_H
#define MANUAL_OVERRIDE_H

#include <LibRobus.h>
#include <Gripper.h>
#include <math.h>
#include <Arduino.h>
#include <Movements.h>
#include <GetSet.h>

#define A_UP 0
#define A_DOWN 1 
#define A_LEFT 2
#define A_RIGHT 3
#define OPTIONS 4
#define SHARE 5
#define CROSS 6
#define SQUARE 7
#define TRIANGLE 8
#define CIRCLE 9
#define LEFTHATX 10
#define LEFTHATY 11
#define RIGHTHATX 12
#define RIGHTHATY 13
#define L2 14
#define R2 15

void RobusProcess(void);
int CheatCode(uint8_t *data);

int ManualOverride(uint8_t *data, float *speed);
void ManualGripping(uint8_t *data);
void Acceleration(uint8_t *data, float *speed);
void ManualDrive(uint8_t *data, float *speed);

#endif