#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdbool.h>

typedef enum
{
    USER_INPUT_INCREMENT,
    USER_INPUT_DECREMENT,
    USER_INPUT_SELECT,
    USER_INPUT_START_FINISH,
    USER_INPUT_RESET,
    USER_INPUT_MODE,
    USER_INPUT_ALL
} UserInput_t;

void UserInput_Init(void);
void UserInput_Update(void);
bool UserInput_IsPressed(UserInput_t input);

#endif