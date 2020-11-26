#include "Sweep.h"

void sweep(void)
{
    static int increment = 0;
    float rotate[4];
    int state;
    static struct DisDeg disDeg;
    float distance = 0;
    static int status = INIT;

    if (status == INIT)
    {
        disDeg.distance = 100;
        disDeg.angle = 0;
        rotate[DIS] = 0;
        rotate[DEG] = 90;
        rotate[DIR] = RIGHT;
        rotate[STATE] = ROTATE;

        GetSetMove(rotate, SET);

        status = START;
    }

    if (status == START)
    {
        GetSetMove(rotate, GET);
        if (rotate[STATE] != STOP)
        {
            distance = sonar_get_data();
            if (distance < 100 && distance > 5)
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

        else status = RESET;
    }

    if (status == RESET)
    {
        rotate[DIS] = 0;
        rotate[DEG] = 90 - disDeg.angle;
        rotate[DIR] = LEFT;
        rotate[STATE] = ROTATE;
        GetSetMove(rotate, SET);

        status = SWEEPSTOP;
    }
}
