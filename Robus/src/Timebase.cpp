#include <Arduino.h>
#include "LibRobus.h"
#include "Timebase.h"

uint32_t timebase_callback_count = 0;
void (*timebase_callback[20])(void);

void timebase_enable(void (*function)(void))
{
    timebase_status(function, true);
}

void timebase_disable(void (*function)(void))
{
    timebase_status(function, false);
}

void timebase_status(void (*function)(void), bool status)
{
    for(uint32_t i = 0; i < timebase_callback_count; i++)
    {
        if(timebase_callback[i] == function)
        {
            if(status == true)
                SOFT_TIMER_Enable(i);
            else
                SOFT_TIMER_Disable(i);

            return;
        }
    }
}

void timebase_add(void (*function)(void), uint32_t milliseconds)
{
    Serial.print("TIMEBASE : ");
    for(uint32_t i = 0; i < timebase_callback_count; i++)
    {
        if(timebase_callback[i] == function)
        {
            Serial.println("MODIFIED");
            SOFT_TIMER_SetDelay(timebase_callback_count, milliseconds);
            SOFT_TIMER_SetRepetition(timebase_callback_count, -1);
            SOFT_TIMER_Enable(timebase_callback_count);
            return;
        }
    }

    Serial.println("ADDED");
    timebase_callback[timebase_callback_count] = function;
    SOFT_TIMER_SetCallback(timebase_callback_count, function);
    SOFT_TIMER_SetDelay(timebase_callback_count, milliseconds);
    SOFT_TIMER_SetRepetition(timebase_callback_count, -1);
    SOFT_TIMER_Enable(timebase_callback_count);
    timebase_callback_count ++;
}
