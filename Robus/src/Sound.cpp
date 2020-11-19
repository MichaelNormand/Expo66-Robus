#include <Arduino.h>
#include "Sound.h"

void (*sound_list[SOUND_COUNT])(void);

void sound_init(void)
{
    pinMode(SOUND_PIN, OUTPUT);
    digitalWrite(SOUND_PIN, LOW);
    sound_list[SOUND_OBJECT] = sound_play_object;
    sound_list[SOUND_BOMB] = sound_play_bomb;
}

void sound_play(uint16_t id)
{
    sound_list[id]();
}

void sound_play_object(void)
{
    tone(SOUND_PIN,NOTE_D4,100);
    delay(200);
    tone(SOUND_PIN,NOTE_A4,100);
    delay(200);
    tone(SOUND_PIN,NOTE_D4,100);
    delay(200);
    tone(SOUND_PIN,NOTE_A4,100);
    delay(200);
    tone(SOUND_PIN,NOTE_D4,100);
    delay(200);
}

void sound_play_bomb(void)
{
    tone(SOUND_PIN,NOTE_E6,125);
    delay(130);
    tone(SOUND_PIN,NOTE_G6,125);
    delay(130);
    tone(SOUND_PIN,NOTE_E7,125);
    delay(130);
    tone(SOUND_PIN,NOTE_C7,125);
    delay(130);
    tone(SOUND_PIN,NOTE_D7,125);
    delay(130);
    tone(SOUND_PIN,NOTE_G7,125);
    delay(125);
    noTone(SOUND_PIN);
}