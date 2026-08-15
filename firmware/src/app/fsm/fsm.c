#include "app/fsm/fsm.h"
#include "app/fsm/setup.h"
#include "app/fsm/training.h"
#include "app/fsm/resting.h"

#include "app/battery_monitor.h"
#include "app/indicator.h"

// Private variables
static FSM_State_t current_state;
static FSM_Mode_t current_mode;

// Private function prototypes
static void FSM_BatteryMonitor(void);

// Helper function for executing battery monitor instructions
static void FSM_BatteryMonitor(void)
{
    BatteryMonitor_Update();

    if (BatteryMonitor_IsLow())
    {
        Indicator_Set(INDICATOR_LOW_BATTERY, true);
    }
}

void FSM_Init(void)
{
    current_state = STATE_SETUP;
    current_mode = MODE_REP;

    Setup_Init();
    Training_Init();
    Resting_Init();
}

void FSM_Update(void)
{
    // Monitor battery regardless of the current FSM state
    FSM_BatteryMonitor();

    switch (current_state)
    {
        case STATE_SETUP:

            current_state = Setup_Update();

            // Store the selected mode when entering training
            if (current_state == STATE_TRAINING)
            {
                current_mode = Setup_GetMode();
            }

            break;

        case STATE_TRAINING:

            current_state = Training_Update(current_mode);

            break;

        case STATE_RESTING:

            current_state = Resting_Update();

            break;

        default:

            current_state = STATE_SETUP;

            break;
    }
}