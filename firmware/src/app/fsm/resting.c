#include "app/fsm/resting.h"
#include "app/fsm/setup.h"
#include "app/time_service.h"
#include "app/display_manager.h"
#include "app/user_input.h"
#include "app/indicator.h"
#include "app/feedback.h"

#include <stdint.h>
#include <stdbool.h>

#define FEEDBACK_BUTTON_MS       (100U)
#define FEEDBACK_LONG_MS         (500U)

// Private variables
static uint16_t current_rest_time;
static uint16_t remaining_time;
static bool resting_started;

void Resting_Init(void)
{
    current_rest_time = 0U;
    remaining_time = 0U;
    resting_started = false;
}

FSM_State_t Resting_Update(void)
{
    // Detect entry into resting state
    if (!resting_started)
    {
        current_rest_time = Setup_GetRestTime();
        remaining_time = current_rest_time;

        // Display the configured rest time
        DisplayManager_ShowTime(remaining_time);

        // Turn on the resting indicator
        Indicator_Set(INDICATOR_RESTING, true);

        // Start the rest countdown
        TimeService_StartRest(current_rest_time);

        resting_started = true;
    }

    // Handle reset
    if (UserInput_IsPressed(USER_INPUT_RESET))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);

        TimeService_Stop();
        Indicator_Set(INDICATOR_RESTING, false);

        resting_started = false;

        return STATE_SETUP;
    }

    // Update the remaining rest time
    remaining_time = TimeService_GetRestRemaining();
    DisplayManager_ShowTime(remaining_time);

    // Check whether the rest countdown has finished
    if (TimeService_IsRestFinished())
    {
        TimeService_Stop();
        Indicator_Set(INDICATOR_RESTING, false);

        // Long feedback when rest finishes
        Feedback_Play(FEEDBACK_LONG_MS);

        resting_started = false;

        return STATE_SETUP;
    }

    return STATE_RESTING;
}