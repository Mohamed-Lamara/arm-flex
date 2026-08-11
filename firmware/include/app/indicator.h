#ifndef INDICATOR_H
#define INDICATOR_H

#include <stdbool.h>

typedef enum
{
    INDICATOR_REP_MODE,
    INDICATOR_TIMED_MODE,
    INDICATOR_TRAINING,
    INDICATOR_RESTING,
    INDICATOR_SURPASSED,
    INDICATOR_LOW_BATTERY,
    INDICATOR_ALL
} Indicator_t;

void Indicator_Init(void);
void Indicator_Set(Indicator_t indicator, bool state);

#endif