#ifndef TIME_SERVICE_H
#define TIME_SERVICE_H

#include <stdbool.h>
#include <stdint.h>

void TimeService_Init(void);

void TimeService_StartRest(uint16_t duration_s);
bool TimeService_IsRestFinished(void);
uint16_t TimeService_GetRestRemaining(void);

void TimeService_StartTimed(uint16_t duration_s);
bool TimeService_IsTimedFinished(void);
uint16_t TimeService_GetTimedRemaining(void);

void TimeService_StartSurpassed(void);
uint16_t TimeService_GetTimedElapsed(void);

void TimeService_Stop(void);

#endif