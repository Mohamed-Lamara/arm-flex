#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>
#include <stdint.h>

void Sensor_Init(void);
void Sensor_CaptureEvent(void);
void Sensor_Update(void);
bool Sensor_IsRepDetected(void);

#endif