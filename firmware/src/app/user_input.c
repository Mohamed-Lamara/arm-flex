#include "app/user_input.h"
#include "drivers/gpio.h"
#include "stm32f103xb.h"

/* User input GPIO mapping
 * TODO: Replace individual pin mappings with a centralized hardware
 * configuration mechanism in a future version.
 */
#define USER_INPUT_INCREMENT_PIN     GPIO_ODR_ODR5
#define USER_INPUT_DECREMENT_PIN     GPIO_ODR_ODR4
#define USER_INPUT_SELECT_PIN        GPIO_ODR_ODR3
#define USER_INPUT_START_FINISH_PIN  GPIO_ODR_ODR1
#define USER_INPUT_RESET_PIN         GPIO_ODR_ODR2
#define USER_INPUT_MODE_PIN          GPIO_ODR_ODR6

bool UserInput_IsPressed(UserInput_t input)
{
    switch (input)
    {
        case USER_INPUT_INCREMENT:
            return GPIO_ReadPin(GPIOA, USER_INPUT_INCREMENT_PIN);

        case USER_INPUT_DECREMENT:
            return GPIO_ReadPin(GPIOA, USER_INPUT_DECREMENT_PIN);

        case USER_INPUT_SELECT:
            return GPIO_ReadPin(GPIOA, USER_INPUT_SELECT_PIN);

        case USER_INPUT_START_FINISH:
            return GPIO_ReadPin(GPIOA, USER_INPUT_START_FINISH_PIN);

        case USER_INPUT_RESET:
            return GPIO_ReadPin(GPIOA, USER_INPUT_RESET_PIN);

        case USER_INPUT_MODE:
            return GPIO_ReadPin(GPIOA, USER_INPUT_MODE_PIN);

        default:
            return false;
    }
}