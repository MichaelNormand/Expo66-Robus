#ifndef AUDIO_H
#define AUDIO_H

#include <Arduino.h>

#define AUDIO_PIN A1
#define AUDIO_SAMPLE 50
#define AUDIO_SAMPLE_COUNT 5
#define AUDIO_SENSITIVITY 455   //400 = ambiant noise, 660 = max val

void AUDIO_Init(void);
void AUDIO_Update(void);
bool AUDIO_Status(bool);        //Send false as parameter to get back the status

#endif