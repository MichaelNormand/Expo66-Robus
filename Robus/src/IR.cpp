#include <librobus.h>
#include "Distance.h"
#include "IR.h"

void IR_Init(void)
{
    Serial.println("IR INIT");
}

float IR_Update(void) 
{
    static bool trigger = false;
    static uint16_t counter = 0;
    uint16_t distance;
    float distance_reel;
    

    distance = ROBUS_ReadIR(0);

    if (trigger == false && distance > IR_SENSITIVITY && MOTOR_Traveled() >= 20)
    {
        counter++;

        if(counter == IR_SAMPLE_COUNT){
            trigger = true;

            if(MOTOR_Traveled() >= 0 && MOTOR_Traveled() < IR_ZONE_1_END)
            {
                IR_Status(IR_ZONE_1);
                AddLength(12);
            }
            else if(MOTOR_Traveled() >= IR_ZONE_1_END && MOTOR_Traveled() <= IR_ZONE_2_END)
            {
                IR_Status(IR_ZONE_2);
                AddLength(12);
            } 
            else if(MOTOR_Traveled() > IR_ZONE_2_END && MOTOR_Traveled() < IR_ZONE_3_END - 15)
            {
                IR_Status(IR_ZONE_3);
                AddRotation(90, ROTATE_RIGHT);
                AddLength(450 - MOTOR_Traveled());
            }
        }

        return distance_reel;
    }
    else{
        counter = 0;
    }

    return 0;

}

uint16_t IR_Status(uint16_t status)
{
    static uint16_t zone = false;

    if(status > 0)
        zone = status;

    return zone;
}
    
bool IR_Wait(void)
{
    static uint16_t count = 0;
    uint16_t distance;

    distance = ROBUS_ReadIR(0);

    Serial.print("distance = ");
    Serial.println(distance);
    
    if(distance > 150)
    {
        count ++;

        if(count == IR_WAIT_COUNT)
            return 1;
    }
    else
    {
        count = 0;
    }
    
    return 0;
}
