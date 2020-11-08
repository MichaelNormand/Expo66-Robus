/*#include <librobus.h>
#include <sonar.h>
#include "Distance.h"

void SONAR_Init(void)
{
    Serial.println("SONAR INIT");
    pinMode(trigpin, OUTPUT); 
    pinMode(echopin, INPUT); 
}

float SONAR_Update(void) 
{
    static bool triggered = false;
    float distance_reel;
    float duration;
    float distance;

    digitalWrite(trigpin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigpin, LOW);
    duration = pulseIn(echopin, HIGH);
    distance = duration * 0.034 / 2; 

    Serial.print("distance = ");
    Serial.println(distance);

    if (triggered == false && distance < 70)
    {
        triggered = true;

        Serial.println("SONAR DETECTED");

        //distance_reel = SONAR_Calcul(distance);

        if(MOTOR_Traveled() > 200 && MOTOR_Traveled() < 300){
            //AddLength(-30);
            //AddRotation(90, ROTATE_LEFT);
            //AddLength(70);
            //AddRotation(90, ROTATE_RIGHT);
            //AddLength(30);
        } 
        else{
            AddLength((int)(distance/4));
            AddRotation(90, ROTATE_LEFT);
            AddLength(70);
            AddRotation(90, ROTATE_RIGHT);
        }
        
        SONAR_Status(true);
        return distance_reel;
    }
    else 
        return 0;

}

/*float SONAR_Calcul(float distance)
{
    float adjacent = cos(10)*distance;
    return adjacent;
}*/

/*bool SONAR_Status(bool status)
{
    static bool triggered = false;

    if(status == true)
        triggered = true;

    return triggered;
}*/
    
