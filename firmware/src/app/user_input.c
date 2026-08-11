#include "app/user_input.h"
#include "drivers/gpio.h"
#include "stm32f103xb.h"

#define USER_INPUT_DEBOUNCE_MS 20U

/* User input GPIO mapping
 * Intended only for V1 of the project
 */
#define USER_INPUT_INCREMENT_PIN     GPIO_ODR_ODR5
#define USER_INPUT_DECREMENT_PIN     GPIO_ODR_ODR4
#define USER_INPUT_SELECT_PIN        GPIO_ODR_ODR3
#define USER_INPUT_START_FINISH_PIN  GPIO_ODR_ODR1
#define USER_INPUT_RESET_PIN         GPIO_ODR_ODR2
#define USER_INPUT_MODE_PIN          GPIO_ODR_ODR6

typedef struct
{
    bool raw_state;
    bool stable_state;
    uint16_t counter_ms;
} UserInput_State_t;

static UserInput_State_t input_states[USER_INPUT_ALL];

// Reads the raw state of the specified user input.
static bool UserInput_ReadRaw(UserInput_t input)
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

// Updates and debounces all user input states.
void UserInput_Update(void)
{
    for (UserInput_t input = USER_INPUT_INCREMENT; input < USER_INPUT_ALL; input++)
    {
        bool current_state = UserInput_ReadRaw(input);

        if (current_state != input_states[input].raw_state)
        {
            input_states[input].raw_state = current_state;
            input_states[input].counter_ms = 0U;
        }
        else
        {
            if (input_states[input].counter_ms < USER_INPUT_DEBOUNCE_MS)
            {
                input_states[input].counter_ms++;
            }

            if (input_states[input].counter_ms >= USER_INPUT_DEBOUNCE_MS)
            {
                input_states[input].stable_state = input_states[input].raw_state;
            }
        }
    }

}

// Returns the debounced pressed state of the specified user input.
bool UserInput_IsPressed(UserInput_t input)
{
if (input >= USER_INPUT_ALL)
{
    return false;
}
    return input_states[input].stable_state;
}

// Initializes states to their initial values
void UserInput_Init(void)
{
    for (UserInput_t input = USER_INPUT_INCREMENT; input < USER_INPUT_ALL; input++)
    {
        input_states[input].raw_state = UserInput_ReadRaw(input);
        input_states[input].stable_state = false;
        input_states[input].counter_ms = 0U;
    }
}