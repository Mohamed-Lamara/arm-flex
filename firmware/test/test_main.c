/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Full system initialization and application loop test.
 *
 * @details
 * Verifies the integration of the hardware drivers and application modules
 * by initializing all system components and executing the main application
 * update loop.
 *
 * Test Objective:
 * - Verify MCU, GPIO, Timer, and Display initialization.
 * - Verify application module initialization.
 * - Verify user input and sensor update handling.
 * - Verify FSM execution and state transitions.
 * - Verify feedback processing.
 *
 * Execution Flow:
 * 1. Initialize hardware drivers.
 * 2. Initialize application modules.
 * 3. Continuously update user inputs and sensors.
 * 4. Process the system FSM.
 * 5. Update feedback outputs.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/display.h"

#include "app/user_input.h"
#include "app/sensor.h"
#include "app/battery_monitor.h"
#include "app/display_manager.h"
#include "app/time_service.h"
#include "app/feedback.h"
#include "app/indicator.h"
#include "app/fsm/fsm.h"

int main(void)
{
    // Hardware initialization
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    Display_Init();

    // Application initialization
    UserInput_Init();
    Sensor_Init();
    BatteryMonitor_Init();
    DisplayManager_Init();
    TimeService_Init();
    Feedback_Init();
    Indicator_Init();
    FSM_Init();

    while (1)
    {
        UserInput_Update();
        Sensor_Update();

        FSM_Update();

        Feedback_Update();
    }
}