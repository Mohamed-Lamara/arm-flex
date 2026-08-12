#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H

#include <stdbool.h>

void BatteryMonitor_Init(void);
void BatteryMonitor_Update(void);
bool BatteryMonitor_IsLow(void);

#endif