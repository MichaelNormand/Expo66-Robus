#include "Audio.h"

void AUDIO_Setup(void){
    pinMode(54, INPUT);
}

void AUDIO_Update(void){
    static bool trigger = false;
    static uint16_t counter = 0;

    if(trigger == true)
        return;

    if(analogRead(AUDIO_PIN) >= AUDIO_SENSITIVITY){
        counter++;

        if(counter == AUDIO_SAMPLE_COUNT){
            trigger = true;
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