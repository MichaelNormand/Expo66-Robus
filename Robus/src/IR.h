#ifndef IR_H
#define IR_H

#define IR_SAMPLE 40
#define IR_SAMPLE_COUNT 2
#define IR_SENSITIVITY 10  

void IR_Init(void);
float IR_Update(void);
bool IR_Status(bool status);

#endif