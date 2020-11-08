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
    distance_reel = (1000/distance) - 2; 

    if(trigger == false)
    {
        Serial.print("distance_reel = ");
        if(distance_reel < IR_SENSITIVITY)
            Serial.println(distance_reel);
        else
            Serial.println();
    }

    if (trigger == false && distance_reel < 15)
    {
        counter++;

        if(counter == IR_SAMPLE_COUNT){
            trigger = true;
            Serial.println("IR DETECTED");
            IR_Status(true);

            if(MOTOR_Traveled() > 200 && MOTOR_Traveled() < 300){
                //AddRotation(180, ROTATE_RIGHT); 
                Serial.print("MOTOR_Traveled = ");
                Serial.println(MOTOR_Traveled());
                Serial.println("200 < x < 300");
                //delay(2000);
            } 
            else{
                //AddRotation(180, ROTATE_RIGHT);
                Serial.print("MOTOR_Traveled = ");
                Serial.println(MOTOR_Traveled());
                Serial.println("else");
                //delay(2000);
            }
        }

        return distance_reel;
    }
    else{
        counter = 0;
    }

    return 0;

}

/*float SONAR_Calcul(float distance)
{
    float adjacent = cos(10)*distance;
    return adjacent;
}*/

bool IR_Status(bool status)
{
    static bool triggered = false;

    if(status == true)
        triggered = true;

    return triggered;
}
    
