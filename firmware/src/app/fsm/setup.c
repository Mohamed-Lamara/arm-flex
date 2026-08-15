#include "app/fsm/setup.h"
#include "app/user_input.h"
#include "app/display_manager.h"
#include "app/feedback.h"
#include "app/indicator.h"

#define SETUP_DEFAULT_REPS       (1U)
#define SETUP_DEFAULT_REST_TIME (30U)

#define FEEDBACK_BUTTON_MS       (100U)

// Private variables
static FSM_Mode_t selected_mode;
static uint16_t reps;
static uint16_t rest_time;
static bool displaying_rest;

// Private function prototypes
static void Setup_Reset(void);
static void Setup_HandleMode(void);
static void Setup_HandleSelect(void);
static void Setup_HandleIncrement(void);
static void Setup_HandleDecrement(void);

void Setup_Init(void)
{
    selected_mode = MODE_REP;
    reps = SETUP_DEFAULT_REPS;
    rest_time = SETUP_DEFAULT_REST_TIME;
    displaying_rest = false;

    // Display the number of repetitions by default
    DisplayManager_ShowNumber(reps);

    // Set the default mode indicator
    Indicator_Set(INDICATOR_REP_MODE, true);
    Indicator_Set(INDICATOR_TIMED_MODE, false);
}

FSM_State_t Setup_Update(void)
{
    // Handle mode selection
    Setup_HandleMode();

    // Toggle between displaying repetitions and rest time
    Setup_HandleSelect();

    
    // Increase the currently displayed value
    if (UserInput_IsPressed(USER_INPUT_INCREMENT))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);
        Setup_HandleIncrement();
    }

    // Decrease the currently displayed value
    if (UserInput_IsPressed(USER_INPUT_DECREMENT))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);
        Setup_HandleDecrement();
    }

    // Reset setup values to their defaults
    if (UserInput_IsPressed(USER_INPUT_RESET))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);
        Setup_Reset();
    }

    // Start training
    if (UserInput_IsPressed(USER_INPUT_START_FINISH))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);
        return STATE_TRAINING;
    }

    return STATE_SETUP;
}

// Toggle between repetition and timed mode
static void Setup_HandleMode(void)
{
    if (UserInput_IsPressed(USER_INPUT_MODE))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);

        if (selected_mode == MODE_REP)
        {
            selected_mode = MODE_TIMED;

            Indicator_Set(INDICATOR_REP_MODE, false);
            Indicator_Set(INDICATOR_TIMED_MODE, true);
        }
        else
        {
            selected_mode = MODE_REP;

            Indicator_Set(INDICATOR_TIMED_MODE, false);
            Indicator_Set(INDICATOR_REP_MODE, true);
        }
    }
}

// Toggle between displaying repetitions and rest time
static void Setup_HandleSelect(void)
{
    if (UserInput_IsPressed(USER_INPUT_SELECT))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);

        displaying_rest = !displaying_rest;

        if (displaying_rest)
        {
            DisplayManager_ShowTime(rest_time);
        }
        else
        {
            DisplayManager_ShowNumber(reps);
        }
    }
}

// Increase the currently displayed value
static void Setup_HandleIncrement(void)
{
    if (displaying_rest)
    {
        rest_time++;
        DisplayManager_ShowTime(rest_time);
    }
    else
    {
        reps++;
        DisplayManager_ShowNumber(reps);
    }
}

// Decrease the currently displayed value
static void Setup_HandleDecrement(void)
{
    if (displaying_rest)
    {
        if (rest_time > 0U)
        {
            rest_time--;
            DisplayManager_ShowTime(rest_time);
        }
    }
    else
    {
        if (reps > 0U)
        {
            reps--;
            DisplayManager_ShowNumber(reps);
        }
    }
}

// Reset setup values to their default values
static void Setup_Reset(void)
{
    selected_mode = MODE_REP;
    reps = SETUP_DEFAULT_REPS;
    rest_time = SETUP_DEFAULT_REST_TIME;
    displaying_rest = false;

    // Display repetitions after reset
    DisplayManager_ShowNumber(reps);

    // Restore the default mode indicator
    Indicator_Set(INDICATOR_TIMED_MODE, false);
    Indicator_Set(INDICATOR_REP_MODE, true);
}

// Return the currently selected training mode
FSM_Mode_t Setup_GetMode(void)
{
    return selected_mode;
}

// Return the configured training value
uint16_t Setup_GetValue(void)
{
    return reps;
}

// Return the configured rest time
uint16_t Setup_GetRestTime(void)
{
    return rest_time;
}