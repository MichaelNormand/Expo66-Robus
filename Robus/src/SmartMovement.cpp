#include <Arduino.h>
#include <stdio.h>
#include "LibRobus.h"
#include "Timebase.h"
#include "SmartMovement.h"
#include "GetSet.h"
#include "Manual_Override.h"

/*bool smart_movement_init(void)
{
    uint32_t distance = 0;

    smart_ir_read(&distance);
    Serial.print("distance = ");
    Serial.println(distance);

    if(distance <= 130)
    {
        Serial.println("STARTED MOVING SEQUENCE");
        timebase_add(smart_movement_lock_update, 50);
        return true;
    }
    else
    {
        return false;
    }
}

void smart_movement_lock_update(void)
{
    static int started = false;
    static int locked = true;      //***
    static uint32_t goal = 0;
    uint32_t distance;
    static uint32_t errorCount = 0;
    static float move[4] = {0, 0, 0, 0};

    //Serial.println("UPDATE");

    if(started == false)                            //Init new movement
    {
        smart_ir_read(&goal);
        if(goal > 130)
            return;

        if(goal > 10)
            goal -= 10;

        move[DIS] = goal;
        move[DEG] = 0;
        move[DIR] = 1;
        move[STATE] = FORWARD;
        Serial.print("goal = ");
        Serial.println(goal);
        GetSetMove(move, SET);

        started = true;
        locked = true;
        return;
    }

    if(locked == false)                             //Target is lost
    {
        if(smart_movement_lock(&goal) == true)
        {
            started = false;
            locked = true;
        }
        return;  
    }

    GetSetMove(move, GET);
    if(locked && move[STATE] == STOP)               //Sequence ended successfully
    {
        Serial.println("ENDED");
        started = false;
        errorCount = 0;
        timebase_disable(smart_movement_lock_update);
    }
    else
    {
        smart_ir_read(&distance);
        if(distance > (goal + 15))  
        {
            errorCount++;
            if(errorCount == 8)                     //3 times to avoid ghost readings
            {
                Serial.println("LOST CONTACT");
                locked = false;
                errorCount = 0;

                move[DIS] = 0;
                move[DEG] = 0;
                move[DIR] = 0;
                move[STATE] = FORWARD;
                GetSetMove(move, SET);
            }
        }
    }
}

bool smart_movement_lock(uint32_t* goal)
{
    static uint32_t sequence = 0;
    static uint32_t wait = 0;
    uint32_t distance = 0;
    static float move[4] = {0, 0, 0, 0};


    smart_ir_read(&distance);
    if(distance < (*goal + 15))      //Lock operation successful
    {
        Serial.println("LOCKING SUCCESSFUL");
        move[DIS] = 0;
        move[DEG] = 0;
        move[DIR] = 0;
        move[STATE] = FORWARD;
        GetSetMove(move, SET);

        sequence = 0;
        return true;
    }

    GetSetMove(move, GET);
    if(move[STATE] == STOP)
    {
        //Serial.println("NOT BUSY");
        Serial.print("sequence[");
        Serial.print(sequence);
        Serial.print("] : ");
        Serial.print(*goal + 15);
        Serial.print(" : ");
        Serial.println(distance);

        if(sequence == 0)
        {
            if(wait <= 2)
            {
                wait++;
            }
            else
            {
                wait = 0;
                sequence = 1;
            }
        }
        else if(sequence <= 20)
        {
            if(wait <= 2)
            {
                wait++;
            }
            else
            {
                wait = 0;
                move[DIS] = 0;
                move[DEG] = 2;
                move[DIR] = LEFT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
                sequence++;
            }
        }
        else if(sequence == 21)
        {
            if(wait <= 2)
            {
                wait++;
            }
            else
            {
                wait = 0;
                move[DIS] = 0;
                move[DEG] = 40;
                move[DIR] = RIGHT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
                sequence = 22;
            } 
        }
        else if (sequence <= 41)
        {
            if(wait <= 2)
            {
                wait++;
            }
            else
            {
                wait = 0;
                move[DIS] = 0;
                move[DEG] = 2;
                move[DIR] = RIGHT;
                move[STATE] = ROTATE;
                GetSetMove(move, SET);
                sequence++;
            } 
        }
        else
        {
            move[DIS] = 0;
            move[DEG] = 0;
            move[DIR] = 0;
            move[STATE] = FORWARD;
            GetSetMove(move, SET);
            Serial.println("SEQUENCE FAILED");
        }
    }
    else                                                //Wait for end of rotation
    {
        //Serial.println("BUSY");
    }
    
    return false;
}*/

void smart_ir_read(uint32_t* distance)
{
    *distance = 0;

     for(uint32_t i = 0; i < 8; i++)
        *distance += (6787 / (ROBUS_ReadIR(0) - 3)) - 4;        //average this over 5 readings
    *distance >>= 3;

    if(*distance < 0)
        *distance = 0;
}








bool smart_align_init(uint32_t distance)
{
    uint32_t state;
    smart_align_status(&state, GET);

    if(state == FORWARD || distance < 10)
    {
        return 0;
    }
    else
    {
        static float move[4] = {0, 0, 0, 0};
        move[DIS] = distance - 10;
        move[DEG] = 0;
        move[DIR] = 0;
        move[STATE] = FORWARD;
        GetSetMove(move, SET);

        state = FORWARD;
        smart_align_status(&state, SET);
        timebase_add(smart_align, 50);
        return 1;
    }
}

void smart_align(void){
    static float move[4] = {0, 0, 0, 0};
    static bool started = false;
    static bool locked = false;
    static uint32_t distance = 0;
    static uint32_t sequence = 0;
    static uint32_t wait = 0;
    uint32_t state;

    Serial.println("ALIGN");

    GetSetMove(move, GET);

    if(started == false)
    {
        if(move[STATE] == STOP)
        {
            started = true;
        }
        return;
    }

    if(locked == true)
    {
        Serial.print("LAST BIT : ");
        Serial.println(distance);

        if(distance > 10)
            distance -= 10;

        move[DIS] = distance;
        move[DEG] = 0;
        move[DIR] = 0;
        move[STATE] = FORWARD;
        
        started = false;
        locked = false;
        sequence = 0;
        wait = 0;
        state = STOP;

        GetSetMove(move, SET);
        smart_align_status(&state, SET);
        timebase_disable(smart_align);

        return;
    }

    smart_ir_read(&distance);

    if(distance > 0 && distance < 25)
    {
        Serial.print("TARGET FOUND : ");
        Serial.println(distance);

        locked = true;
        move[DIS] = 0;
        move[DEG] = 0;
        move[DIR] = 0;
        move[STATE] = ROTATE;
        GetSetMove(move, SET);
    }
    else
    {
         if(move[STATE] == STOP)
        {
            //Serial.println("NOT BUSY");
            Serial.print("zequence[");
            Serial.print(sequence);
            Serial.print("] : ");
            //Serial.print(*goal + 15);
            //Serial.print(" : ");
            Serial.println(distance);

            if(sequence == 0)
            {
                if(wait <= 2)
                {
                    wait++;
                }
                else
                {
                    wait = 0;
                    sequence = 1;
                }
            }
            else if(sequence <= 10)
            {
                if(wait <= 2)
                {
                    wait++;
                }
                else
                {
                    wait = 0;
                    move[DIS] = 0;
                    move[DEG] = 3;
                    move[DIR] = LEFT;
                    move[STATE] = ROTATE;
                    GetSetMove(move, SET);
                    sequence++;
                }
            }
            else if(sequence == 11)
            {
                if(wait <= 2)
                {
                    wait++;
                }
                else
                {
                    wait = 0;
                    move[DIS] = 0;
                    move[DEG] = 40;
                    move[DIR] = RIGHT;
                    move[STATE] = ROTATE;
                    GetSetMove(move, SET);
                    sequence = 12;
                } 
            }
            else if (sequence <= 21)
            {
                if(wait <= 2)
                {
                    wait++;
                }
                else
                {
                    wait = 0;
                    move[DIS] = 0;
                    move[DEG] = 3;
                    move[DIR] = RIGHT;
                    move[STATE] = ROTATE;
                    GetSetMove(move, SET);
                    sequence++;
                } 
            }
            else
            {
                move[DIS] = 0;
                move[DEG] = 0;
                move[DIR] = 0;
                move[STATE] = FORWARD;
                GetSetMove(move, SET);
                Serial.println("SEQUENCE FAILED");
            }
        }
    }
}

void smart_align_status(uint32_t* state, bool action)
{
    static int temp = 0;

    if(action == SET)
        temp = *state;
    if(action == GET)
        *state = temp;
}

