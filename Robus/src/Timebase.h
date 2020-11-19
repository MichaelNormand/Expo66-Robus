#ifndef TIMEBASE_H
#define TIMEBASE_H

#include <stdio.h>

void timebase_init(void);
void timebase_enable(void (*function)(void));
void timebase_disable(void (*function)(void));
void timebase_status(void (*function)(void), bool status);
void timebase_add(void (*function)(void), uint32_t milliseconds);

#endif