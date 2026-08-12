#include "app/battery_monitor.h"
#include "drivers/adc.h"

#define BATTERY_LOW_THRESHOLD       2048U    // temporary value

static bool battery_low;

void BatteryMonitor_Init(void)
{
    battery_low = false;
}

void BatteryMonitor_Update()
{
    uint16_t adc_value = ADC_Read();
    if (adc_value <= BATTERY_LOW_THRESHOLD) 
    {
        battery_low = true;
    }
}

bool BatteryMonitor_IsLow(void)
{
    return battery_low;
}