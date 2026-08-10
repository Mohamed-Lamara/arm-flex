/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   4-digit 7-segment display verification test.
 *
 * @details
 * Verifies the display driver by cycling through a series of values while
 * the SysTick interrupt continuously updates the display multiplexing.
 *
 * Test Objective:
 * - Verify display initialization.
 * - Verify 4-digit multiplexing operation.
 * - Verify segment pattern mapping.
 * - Verify leading-zero suppression.
 * - Verify zero display handling.
 * - Verify maximum value display.
 * - Verify value saturation above 9999.
 * - Verify cooperation between Display and Timer drivers.
 *
 * Expected Result:
 * - Values are displayed sequentially with a 2-second interval.
 * - Leading zeros remain blank.
 * - The value 0 is displayed correctly.
 * - Values above 9999 are saturated to 9999.
 * - No visible flicker or ghosting is observed.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/display.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    Display_Init();

    while (1)
    {
        Display_SetNumber(0U);
        Timer_Delay(2000U);

        Display_SetNumber(1U);
        Timer_Delay(2000U);

        Display_SetNumber(42U);
        Timer_Delay(2000U);

        Display_SetNumber(1050U);
        Timer_Delay(2000U);

        Display_SetNumber(1000U);
        Timer_Delay(2000U);

        Display_SetNumber(1234U);
        Timer_Delay(2000U);

        Display_SetNumber(9999U);
        Timer_Delay(2000U);

        Display_SetNumber(10000U);
        Timer_Delay(2000U);
    }
}