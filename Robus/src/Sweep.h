#include <Arduino.h>
#include <LibRobus.h>
#include "Config.h"
#include "GetSet.h"
#include "Sonar.h"

struct DisDeg
{
    float distance;
    float angle;
};

void sweep(void);