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
    //distance_reel = (1000/distance) - 2; 

    /*if(trigger == false)
    {
        Serial.print("distance_reel = ");
        if(distance_reel < IR_SENSITIVITY)
            Serial.println(distance_reel);
        else
            Serial.println();
    }*/

    /*if(trigger == false && MOTOR_Traveled() >= 445)
    {
        trigger = true;
        AddRotation(90, ROTATE_LEFT)
        AddLength(65);
    }*/

    if (trigger == false && distance > IR_SENSITIVITY)
    {
        counter++;

        if(counter == IR_SAMPLE_COUNT){
            trigger = true;
            Serial.println("IR DETECTED");

            if(MOTOR_Traveled() >= 0 && MOTOR_Traveled() < 235)
            {
                IR_Status(IR_ZONE_1);
                //AddRotation(90, ROTATE_LEFT);
                //AddLength(65);
                AddRotation(90, ROTATE_RIGHT);
                AddLength(150 - MOTOR_Traveled());
            }
            else if(MOTOR_Traveled() >= 235 && MOTOR_Traveled() <= 255)
            {
                IR_Status(IR_ZONE_2);
                //AddRotation(90, ROTATE_LEFT);
                //AddLength(65);
            } 
            else if(MOTOR_Traveled() > 255 && MOTOR_Traveled() < 450)
            {
                IR_Status(IR_ZONE_3);
                //AddRotation(90, ROTATE_LEFT);
                //AddLength(65);
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

        if(count == 15)
            return 1;
    }
    else
    {
        count = 0;
    }
    
    return 0;
}
