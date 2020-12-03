#ifndef GETSET_H
#define GETSET_H

#include <Config.h>
#include <Arduino.h>

void GetSetMove(float *move, int action);
void GetSetData(uint8_t *data, int action);
void GetSetAngle(float *angle, int action);
void GetSetSweepStatus(int *status, int action);

#endif