#include <Arduino.h>
#include "Sonar.h"

float sonar_distance;

void sonar_init(void)
{
    Serial.println("SONAR INIT");
    pinMode(SONAR_TRIGPIN, OUTPUT); 
    pinMode(SONAR_ECHOPIN, INPUT); 
}

void sonar_update(void) 
{
    float duration;
    //float distance;
    digitalWrite(SONAR_TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(SONAR_TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(SONAR_TRIGPIN, LOW);
    duration = pulseIn(SONAR_ECHOPIN, HIGH);
    sonar_distance = duration * 0.034  / 2; 
    sonar_distance += sonar_distance / 20 * 5.2;
    Serial.print("distance = ");
    Serial.println(sonar_distance);
}

float sonar_get_data(void)
{
    return sonar_distance;
}
