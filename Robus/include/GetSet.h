#ifndef GETSET_H
#define GETSET_H

#include <Config.h>
#include <Arduino.h>

void GetSetMove(float *move, int action);
void GetSetData(uint8_t *data, int action);
void GetSetState(int *state, int action);

#endif