#include "app/fsm/training.h"
#include "app/fsm/setup.h"
#include "app/user_input.h"
#include "app/time_service.h"
#include "app/display_manager.h"
#include "app/indicator.h"
#include "app/feedback.h"
#include "app/sensor.h"

#define FEEDBACK_BUTTON_MS       (100U)
#define FEEDBACK_LONG_MS         (500U)

// Training phases
typedef enum
{
    TRAINING_ACTIVE,
    TRAINING_SURPASSED
} Training_Phase_t;

// Private variables
static FSM_Mode_t current_mode;
static Training_Phase_t current_phase;
static uint16_t current_value;
static bool training_started;

// Private function prototypes
static void Training_Start(void);
static void Training_UpdateRep(void);
static void Training_UpdateTimed(void);
static void Training_UpdateSurpassed(void);

void Training_Init(void)
{
    current_mode = MODE_REP;
    current_phase = TRAINING_ACTIVE;
    current_value = 0U;
    training_started = false;
}

FSM_State_t Training_Update(FSM_Mode_t mode)
{
    // Initialize a new training session when entering the state
    if (!training_started)
    {
        current_mode = mode;
        Training_Start();
        training_started = true;
    }

    // Reset training and return to setup
    if (UserInput_IsPressed(USER_INPUT_RESET))
    {
        Feedback_Play(FEEDBACK_BUTTON_MS);

        TimeService_Stop();

        Indicator_Set(INDICATOR_TRAINING, false);
        Indicator_Set(INDICATOR_SURPASSED, false);

        training_started = false;

        return STATE_SETUP;
    }

    // Finish training and enter the resting state
    if (UserInput_IsPressed(USER_INPUT_START_FINISH))
    {
        Feedback_Play(FEEDBACK_LONG_MS);

        TimeService_Stop();

        Indicator_Set(INDICATOR_TRAINING, false);
        Indicator_Set(INDICATOR_SURPASSED, false);

        training_started = false;

        return STATE_RESTING;
    }

    // Handle surpassed phase
    if (current_phase == TRAINING_SURPASSED)
    {
        Training_UpdateSurpassed();
    }
    else if (current_mode == MODE_REP)
    {
        Training_UpdateRep();
    }
    else
    {
        Training_UpdateTimed();
    }

    return STATE_TRAINING;
}

// Initialize a new training session
static void Training_Start(void)
{
    // Turn on the training indicator
    Indicator_Set(INDICATOR_TRAINING, true);

    // Short feedback when training starts
    Feedback_Play(FEEDBACK_BUTTON_MS);

    // Start in the active phase
    current_phase = TRAINING_ACTIVE;

    if (current_mode == MODE_REP)
    {
        // Start repetition counting from zero
        current_value = 0U;

        // Display the current repetition count
        DisplayManager_ShowNumber(current_value);
    }
    else
    {
        // Load the configured training duration
        current_value = Setup_GetValue();

        // Display the configured duration
        DisplayManager_ShowTime(current_value);

        // Start the timed countdown
        TimeService_StartTimed(current_value);
    }
}

// Handle repetition mode
static void Training_UpdateRep(void)
{
    // A detected sensor event represents one completed repetition
    if (Sensor_IsRepDetected())
    {
        current_value++;

        // Display the current repetition count
        DisplayManager_ShowNumber(current_value);

        // Check whether the target was surpassed
        if (current_value > Setup_GetValue())
        {
            current_phase = TRAINING_SURPASSED;

            // Turn on the surpassed indicator
            Indicator_Set(INDICATOR_SURPASSED, true);

            // Long feedback when target is surpassed
            Feedback_Play(FEEDBACK_LONG_MS);
        }
    }
}

// Handle active timed mode
static void Training_UpdateTimed(void)
{
    // Update the displayed remaining time
    current_value = TimeService_GetTimedRemaining();

    DisplayManager_ShowTime(current_value);

    // The configured duration has reached zero
    if (TimeService_IsTimedFinished())
    {
        current_value = 0U;

        DisplayManager_ShowTime(current_value);

        current_phase = TRAINING_SURPASSED;

        // Turn on the surpassed indicator
        Indicator_Set(INDICATOR_SURPASSED, true);

        // Long feedback when target time is reached
        Feedback_Play(FEEDBACK_LONG_MS);

        // Start the elapsed-time counter
        TimeService_StartSurpassed();

        return;
    }

    // Sensor event ends the timed set
    if (Sensor_IsRepDetected())
    {
        TimeService_Stop();
    }
}

// Handle the surpassed phase
static void Training_UpdateSurpassed(void)
{
    // REP mode continues counting repetitions
    if (current_mode == MODE_REP)
    {
        if (Sensor_IsRepDetected())
        {
            current_value++;

            DisplayManager_ShowNumber(current_value);
        }

        return;
    }

    // TIMED mode counts upward after reaching zero
    current_value = TimeService_GetTimedElapsed();

    DisplayManager_ShowTime(current_value);

    // Sensor event ends the timed set
    if (Sensor_IsRepDetected())
    {
        TimeService_Stop();
    }
}