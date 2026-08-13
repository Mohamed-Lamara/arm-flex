#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

void Display_Init(void);
void Display_SetNumber(uint16_t value);
void Display_SetMinus(void);
void Display_Clear(void);
void Display_Update(void);

#endif