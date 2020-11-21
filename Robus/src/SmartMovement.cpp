#include <Arduino.h>
#include <stdio.h>
#include "LibRobus.h"
#include "Timebase.h"
#include "SmartMovement.h"

bool smart_movement_init(void)
{
    //uint32_t distance = 1000 / (ROBUS_ReadIR(0) - 2);
    uint32_t distance = (6787 / (ROBUS_ReadIR(0) - 3)) - 4;

    Serial.print("distance = ");
    Serial.print(distance);
    Serial.print("   :   ");

    if(distance < 100)
    {
        Serial.println(" OK");
        return true;
    }
    else
    {
        Serial.println(" FAIL");
        return false;
    }
    //timebase_add(smart_movement_update, 50);
}

void smart_movement_update(void)
{
    static bool started = false;
    static bool ended = false;
    static bool locked = true;      //***
    static uint32_t goal;
    static uint32_t errorCount = 0;

    if(started == false)
    {
        goal = 1000 / (ROBUS_ReadIR(0) - 2);        //average this over 5 readings
        //move(goal - 10);
    }
    
    if(locked == true)
    {
        if((1000 / (ROBUS_ReadIR(0) - 2)) > goal)
        {
            errorCount++;
        }

        if(errorCount == 3)
        {
            locked = false;
            errorCount = 0;
            //move_abort();
        }
    }
    else
    {
        if(smart_movement_lock(&goal) == true)
        {
            started = false;
            locked = true;
        }
    }
    

    //AUTO RESET
    if(ended == true)
    {
        started = false;
        ended = false;
        errorCount = 0;
        timebase_disable(smart_movement_update);
    }

}

bool smart_movement_lock(uint32_t* goal)
{
    static bool done = true;
    static uint32_t sequence = 0;

    //if(sequence > 0)
    //{
        //done = get_rotation_done();
    //}

    if(done == true)
    {
        if((1000 / (ROBUS_ReadIR(0) - 2)) < *goal)      //Lock operation successful
        {
            sequence = 0;
            return true;
        }
        else                                            //Turn slowly
        {
            if(sequence <= 9)
            {
                //rotate(2,left);
            }
            else if(sequence == 10)
            {
                //rotate(2*10,right);
            }
            else if (sequence <= 20)
            {
                //rotate(2,right);
            }
        }
        
    }
    else                                                //Wait for end of rotation
    {
        //Do nothing
    }
    
    return false;
}