#include <Arduino.h>
#include <stdio.h>
#include "LibRobus.h"
#include "Timebase.h"
#include "SmartMovement.h"
#include "GetSet.h"

bool smart_movement_init(void)
{
    uint32_t distance = (6787 / (ROBUS_ReadIR(0) - 3)) - 4;

    Serial.print("distance = ");
    Serial.print(distance);
    Serial.print("   :   ");

    if(distance < 100)
    {
        Serial.println(" OK");
        timebase_add(smart_movement_lock_update, 50);
        return true;
    }
    else
    {
        Serial.println(" FAIL");
        return false;
    }
}

void smart_movement_lock_update(void)
{
    static int started = false;
    static int state = false;
    static int locked = true;      //***
    static uint32_t goal;
    static uint32_t errorCount = 0;
    static float move[4] = {DIS, DEG, DIR, STATE};

    //Serial.println("UPDATE");

    if(started == false)
    {
        goal = (6787 / (ROBUS_ReadIR(0) - 3)) - 4;        //average this over 5 readings
        move[DIS] = goal;
        move[DEG] = 0;
        move[DIR] = 1;
        move[STATE] = GO;
        Serial.print("goal = ");
        Serial.println(goal);
        GetSetMove(move, SET);

        started = true;
        locked = true;
        return;
    }
    
    GetSetMove(move, GET);

    Serial.print("GetSetDis = ");
    Serial.println(move[STATE]);

    /*if(locked == true)
    {
        if(((6787 / (ROBUS_ReadIR(0) - 3)) - 4) > goal)
        {
            errorCount++;
        }

        if(errorCount == 3)
        {
            Serial.println("LOST CONTACT");
            locked = false;
            errorCount = 0;

            move[DIS] = 0;
            move[DEG] = 0;
            move[DIR] = 1;
            move[STATE] = STOP;
            GetSetMove(move, SET);
        }
        return;
    }
    else
    {
        if(smart_movement_lock(&goal) == true)
        {
            started = false;
            locked = true;
        }
        //return;             //***???
    }*/
    
    //GetSetDis(&state, GET);

    /*AUTO RESET
    if(state)
    {
        Serial.println("ENDED");
        started = false;
        //state = false;
        errorCount = 0;
        timebase_disable(smart_movement_lock_update);
    }*/


    return;
}

bool smart_movement_lock(uint32_t* goal)
{
    static int done = true;
    static uint32_t sequence = 0;
    static float move[4] = {DIS, DEG, DIR, STATE};

    GetSetState(&done, GET);

    if(done)
    {
        if(((6787 / (ROBUS_ReadIR(0) - 3)) - 4) < *goal)      //Lock operation successful
        {
            sequence = 0;
            return true;
        }
        else                                            //Turn slowly
        {
            if(sequence <= 9)
            {
                move[DIS] = 0;
                move[DEG] = 2;
                move[DIR] = LEFT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
            }
            else if(sequence == 10)
            {
                move[DIS] = 0;
                move[DEG] = 2*10;
                move[DIR] = RIGHT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
            }
            else if (sequence <= 20)
            {
                move[DIS] = 0;
                move[DEG] = 2;
                move[DIR] = RIGHT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
            }
        }
        
    }
    else                                                //Wait for end of rotation
    {
        //Do nothing
    }
    
    return false;
}