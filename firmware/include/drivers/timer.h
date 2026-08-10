#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void Timer_Init(void);
uint32_t Timer_GetTicks(void);
void Timer_Delay(uint32_t ms);

#endif