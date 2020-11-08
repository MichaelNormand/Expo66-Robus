#include "Audio.h"

void AUDIO_Init(void){
    Serial.println("AUDIO INIT");
    pinMode(AUDIO_PIN, INPUT);
}

void AUDIO_Update(void){
    static bool trigger = false;
    static uint16_t counter = 0;

    if(trigger == true)
        return;

    //Serial.print("audio = ");
    //Serial.println(analogRead(AUDIO_PIN));

    if(analogRead(AUDIO_PIN) >= AUDIO_SENSITIVITY){
        counter++;

        if(counter == AUDIO_SAMPLE_COUNT){
            trigger = true;
            Serial.println("AUDIO DETECTED");
            AUDIO_Status(true);
            return;
        }
    }
    else{
        counter = 0;
    }
}

bool AUDIO_Status(bool status){
    static bool triggered = false;

    if(status == true)
        triggered = true;

    return triggered;
}