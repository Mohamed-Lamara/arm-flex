#include "app/time_service.h"
#include "drivers/timer.h"

static bool rest_active;
static uint32_t rest_start_tick;
static uint16_t rest_duration_s;

static bool timed_active;
static uint32_t timed_start_tick;
static uint16_t timed_duration_s;

static bool surpassed_active;
static uint32_t surpassed_start_tick;

// Initializes all timers to an inactive state
void TimeService_Init(void)
{
    rest_active = false;
    rest_start_tick = 0U;
    rest_duration_s = 0U;
    timed_active = false;
    timed_start_tick = 0U;
    timed_duration_s = 0U;
    surpassed_active = false;
    surpassed_start_tick = 0U;
}

// Starts a rest countdown
void TimeService_StartRest(uint16_t duration_s)
{
    rest_start_tick = Timer_GetTicks();
    rest_duration_s = duration_s;
    rest_active = true;
}

// Checks whether the rest countdown has finished
bool TimeService_IsRestFinished(void)
{
    if (!rest_active)
    {
        return false;
    }

    return ((Timer_GetTicks() - rest_start_tick) >= (rest_duration_s * 1000U));
}

// Returns the remaining rest time in seconds
uint16_t TimeService_GetRestRemaining(void)
{
    uint32_t elapsed_ms;
    uint32_t duration_ms;

    if (!rest_active)
    {
        return 0U;
    }

    elapsed_ms = Timer_GetTicks() - rest_start_tick;
    duration_ms = rest_duration_s * 1000U;

    if (elapsed_ms >= duration_ms)
    {
        return 0U;
    }

    // Ceiling division to avoid integer division truncation
    return (uint16_t)((duration_ms - elapsed_ms + 999U) / 1000U);
}

// Starts a timed-mode training countdown
void TimeService_StartTimed(uint16_t duration_s)
{
    timed_start_tick = Timer_GetTicks();
    timed_duration_s = duration_s;
    timed_active = true;
    surpassed_active = false;
}

// Checks whether the timed-mode countdown has finished
bool TimeService_IsTimedFinished(void)
{
    if (!timed_active)
    {
        return false;
    }

    return ((Timer_GetTicks() - timed_start_tick) >= (timed_duration_s * 1000U));
}

// Returns the remaining timed-mode duration in seconds
uint16_t TimeService_GetTimedRemaining(void)
{
    uint32_t elapsed_ms;
    uint32_t duration_ms;

    if (!timed_active)
    {
        return 0U;
    }

    elapsed_ms = Timer_GetTicks() - timed_start_tick;
    duration_ms = timed_duration_s * 1000U;

    if (elapsed_ms >= duration_ms)
    {
        return 0U;
    }

    // Ceiling division to avoid integer division truncation
    return (uint16_t)((duration_ms - elapsed_ms + 999U) / 1000U);
}

// Starts the elapsed-time counter after the timed target is reached
void TimeService_StartSurpassed(void)
{
    surpassed_start_tick = Timer_GetTicks();
    surpassed_active = true;
}

// Returns elapsed time since the timed target was reached
uint16_t TimeService_GetTimedElapsed(void)
{
    uint32_t elapsed_ms;

    if (!surpassed_active)
    {
        return 0U;
    }

    elapsed_ms = Timer_GetTicks() - surpassed_start_tick;

    return (uint16_t)(elapsed_ms / 1000U);
}

// Stops all timers and resets their state
void TimeService_Stop(void)
{
    rest_active = false;
    rest_start_tick = 0U;
    rest_duration_s = 0U;
    timed_active = false;
    timed_start_tick = 0U;
    timed_duration_s = 0U;
    surpassed_active = false;
    surpassed_start_tick = 0U;
}