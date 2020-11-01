#include "Ball.h"
#include "Distance.h"

void BALL_Init(void){
    //delay(15000) //15 second delay
    AddLength(100);
    AddRotation(90, ROTATE_RIGHT);
    AddLength(50);
    AddRotation(90, ROTATE_LEFT);
    
    //ReadColor
    Serial.println("Added Sequence !");
}