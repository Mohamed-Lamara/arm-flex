#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <stdint.h>

void DisplayManager_Init(void);
void DisplayManager_ShowNumber(uint16_t number);
void DisplayManager_ShowTime(uint16_t seconds);

#endif