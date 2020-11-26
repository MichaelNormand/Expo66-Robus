#include "Sweep.h"

void sweep(void)
{
    static int increment = 0;
    float rotate[4];
    int state;
    static struct DisDeg disDeg;
    float distance = 0;
    static int steps = 1;

    if (steps == 0)
        increment = 0;

    if (increment < 90)
    {
        GetSetMove(rotate, GET);

        Serial.println(state);

        if (rotate[STATE] == STOP)
        {
            rotate[DIS] = 0;
            rotate[DEG] = 2;
            rotate[DIR] = RIGHT;
            rotate[STATE] = ROTATE;

            Serial.print("Rotate set: ");
            Serial.println(increment);

            if (increment == 0)
            {
                disDeg.distance = 100;
            }

            distance = sonar_get_data();

            if (distance < 100 && distance > 5)
            {
                if (distance < disDeg.distance)
                {
                    disDeg.distance = distance;
                    disDeg.angle = increment + 15;
                }
            }

            GetSetMove(rotate, SET);
            increment += 2;
        }
    }

    if (increment == 90)
    {
        increment = 500;
        rotate[0] = 0;
        rotate[1] = 90 - disDeg.angle;
        rotate[2] = LEFT;
        rotate[3] = ROTATE;
        GetSetMove(rotate, SET);
    }
}
