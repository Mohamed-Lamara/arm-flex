/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Feedback module verification test.
 *
 * @details
 * Verifies the Feedback module by generating audible feedback while the
 * User Input and Indicator modules continue operating in the same
 * cooperative superloop.
 *
 * Test Objective:
 * - Verify Feedback initialization.
 * - Verify Feedback_Play() functionality.
 * - Verify non-blocking Feedback_Update() operation.
 * - Verify Timer tick-based feedback timing.
 * - Verify cooperation between Feedback, User Input, Indicator, UART,
 *   and Timer modules.
 *
 * Expected Result:
 * - Pressing the MODE button produces a short beep.
 * - Pressing the SELECT button produces a longer beep.
 * - The corresponding indicator changes state when its button is pressed.
 * - Feedback continues timing without blocking the main loop.
 * - UART reports each button event.
 ******************************************************************************/

#include "app/feedback.h"
#include "app/indicator.h"
#include "app/user_input.h"
#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"

int main(void)
{
    bool mode_previous = false;
    bool select_previous = false;

    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();

    UserInput_Init();
    Indicator_Init();
    Feedback_Init();

    UART_SendString("Feedback Test\r\n");

    while (1)
    {
        bool mode_current;
        bool select_current;

        // Update application modules
        UserInput_Update();
        Feedback_Update();

        // Read current button states 
        mode_current = UserInput_IsPressed(USER_INPUT_MODE);
        select_current = UserInput_IsPressed(USER_INPUT_SELECT);

        // MODE button: short beep + toggle training indicator 
        if (mode_current && !mode_previous)
        {
            UART_SendString("MODE: 100 ms beep\r\n");

            Feedback_Play(100U);

            Indicator_Set(
                INDICATOR_TRAINING,
                !mode_previous
            );
        }

        // SELECT button: long beep + toggle resting indicator 
        if (select_current && !select_previous)
        {
            UART_SendString("SELECT: 500 ms beep\r\n");

            Feedback_Play(500U);

            Indicator_Set(
                INDICATOR_RESTING,
                !select_previous
            );
        }

        // Store button states for edge detection 
        mode_previous = mode_current;
        select_previous = select_current;
    }
}
