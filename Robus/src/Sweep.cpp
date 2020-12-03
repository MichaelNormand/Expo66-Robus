#include "Sweep.h"
#include "Communication.h"

void sweep(void)
{
    static int increment = 0;
    float rotate[4];
    int state;
    static struct DisDeg disDeg;
    float distance = 0;
    int status;
    GetSetSweepStatus(&status, GET);

    if (status == INIT)
    {
        disDeg.distance = MAX_DIS;
        disDeg.angle = 0;
        rotate[DIS] = 0;
        rotate[DEG] = ANGLE;
        rotate[DIR] = RIGHT;
        rotate[STATE] = ROTATE;

        GetSetMove(rotate, SET);

        status = START;
        GetSetSweepStatus(&status, SET);
    }

    if (status == START)
    {
        GetSetMove(rotate, GET);
        if (rotate[STATE] != STOP)
        {
            distance = sonar_get_data();
            if (distance < MAX_DIS && distance > MIN_DIS)
            {
                if (distance < disDeg.distance)
                {
                    disDeg.distance = distance;
                    GetSetAngle(&disDeg.angle, GET);

                    Serial.print("distance = ");
                    Serial.println(disDeg.distance);
                    Serial.print("Angle = ");
                    Serial.println(disDeg.angle);
                }
            }
        }
        else
        {
            status = RESET;
            GetSetSweepStatus(&status, SET);
        }
    }

    if (status == RESET)
    {
        rotate[DIS] = 0;
        rotate[DEG] = ANGLE - disDeg.angle;
        rotate[DIR] = LEFT;
        rotate[STATE] = ROTATE;
        GetSetMove(rotate, SET);

        status = SWEEPSTOP;
        GetSetSweepStatus(&status, SET);
    }
}
