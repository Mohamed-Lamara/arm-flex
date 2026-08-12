#include "app/sensor.h"
#include "drivers/timer.h"

// Set according to the PDD
#define SENSOR_MIN_REP_INTERVAL_MS    200U

static volatile bool sensor_event;
static bool rep_detected;
static uint32_t last_rep_tick;
static bool rep_initialized;

void Sensor_Init(void)
{
    sensor_event = false;
    rep_detected = false;
    last_rep_tick = 0U;
    rep_initialized = false;
}

// Called by EXTI ISR when a sensor edge is captured.
void Sensor_CaptureEvent(void)
{
    sensor_event = true;
}

// Processes sensor events in the main loop.
void Sensor_Update(void)
{
    if (sensor_event)
    {
        uint32_t current_tick = Timer_GetTicks();
        sensor_event = false;
        
        // filtering the sensor input
        if (!rep_initialized ||
           (current_tick - last_rep_tick >= SENSOR_MIN_REP_INTERVAL_MS))
        {
            rep_detected = true;
            last_rep_tick = current_tick;
            rep_initialized = true;
        }
    }
}

bool Sensor_IsRepDetected(void)
{
    if (rep_detected)
    {
        rep_detected = false;
        return true;
    }

    return false;
}