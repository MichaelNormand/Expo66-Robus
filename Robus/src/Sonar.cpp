#include <librobus.h>
#include <sonar.h>

void SONAR_Init(void)
{
    pinMode(trigpin, OUTPUT); 
    pinMode(echopin, INPUT); 
  
}

float SONAR_Update(void) 
{
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

    if (distance < 100)
    {
        distance_reel = SONAR_Calcul(distance);
        SONAR_Status(true);
        return distance_reel;
    }

    else return 0;

    Serial.println(" cm");
}

float SONAR_Calcul(float distance)
{
    float adjacent = cos(15)*distance;
    return adjacent;
}

bool SONAR_Status(bool status)
{
    static bool triggered = false;

    if(status == true)
        triggered = true;

    return triggered;
}
    
