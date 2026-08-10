#ifndef GPIO_H
#define GPIO_H

#include "stm32f103xb.h"
#include <stdint.h>
#include <stdbool.h>

void GPIO_Init(void);

bool GPIO_ReadPin(GPIO_TypeDef *port, uint16_t pin);
void GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, bool state);
void GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pin);

#endif