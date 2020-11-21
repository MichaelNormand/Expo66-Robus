#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Wire.h>
#include <Arduino.h>
#include <GetSet.h>

void Communication_Init(void);
void DataRequest(void);

// typedef struct Bluetooth
// {
//     uint16_t : 5;
//     uint16_t obstacle : 1;
//     uint16_t bombe : 1;
//     uint16_t angle : 9;
//     uint8_t distance : 8;
// };

#endif