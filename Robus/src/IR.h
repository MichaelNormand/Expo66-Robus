#ifndef IR_H
#define IR_H

#define IR_GET_INFO 0
#define IR_SET_INFO 1
#define IR_SAMPLE 10
#define IR_SAMPLE_COUNT 2
#define IR_SENSITIVITY 60 
#define IR_ZONE_1 1
#define IR_ZONE_2 2
#define IR_ZONE_3 3

void IR_Init(void);
float IR_Update(void);
uint16_t IR_Status(uint16_t status);
bool IR_Wait(void);

#endif