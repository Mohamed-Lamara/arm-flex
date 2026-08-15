#ifndef SETUP_H
#define SETUP_H

#include "app/fsm/fsm.h"
#include <stdint.h>

void Setup_Init(void);
FSM_State_t Setup_Update(void);
FSM_Mode_t Setup_GetMode(void);
uint16_t Setup_GetValue(void);
uint16_t Setup_GetRestTime(void);

#endif