/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Display Manager verification test.
 *
 * @details
 * Verifies numerical and time formatting through the Display Manager.
 *
 * Test Objective:
 * - Verify numerical display.
 * - Verify seconds display below one minute.
 * - Verify minute-second formatting.
 * - Verify '-' separator placement.
 * - Verify single-digit minute formatting.
 * - Verify the maximum supported time of 9:59.
 * - Verify saturation above the supported range.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/timer.h"
#include "drivers/display.h"
#include "app/display_manager.h"


int main(void)
{
    MCU_Init();
    Timer_Init();
    Display_Init();
    DisplayManager_Init();

    while (1)
    {
        // Display a regular number
        DisplayManager_ShowNumber(1234U);
        Timer_Delay(2000U);

        // Display seconds below one minute
        DisplayManager_ShowTime(45U);
        Timer_Delay(2000U);

        // Display 1 minute 2 seconds
        // Expected: 1-02
        DisplayManager_ShowTime(62U);
        Timer_Delay(2000U);

        // Display 2 minutes 2 seconds
        // Expected: 2-02
        DisplayManager_ShowTime(122U);
        Timer_Delay(2000U);

        // Display 9 minutes 59 seconds
        // Expected: 9-59
        DisplayManager_ShowTime(599U);
        Timer_Delay(2000U);

        // Test value above the supported range
        // Expected: 9-59
        DisplayManager_ShowTime(600U);
        Timer_Delay(2000U);
    }
}