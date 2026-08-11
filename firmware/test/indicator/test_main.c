/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Indicator, UART, GPIO, and Timer verification test.
 *
 * @details
 * Verifies the Indicator module by sequentially activating each indicator
 * and transmitting the expected indicator state over UART.
 *
 * Test Objective:
 * - Verify Indicator initialization.
 * - Verify GPIO indicator output configuration.
 * - Verify Indicator_Set() functionality.
 * - Verify UART transmission of test status.
 * - Verify Timer_Delay() functionality.
 * - Verify cooperation between Indicator, GPIO, UART, and Timer modules.
 *
 * Expected Result:
 * - Each indicator is activated individually for a fixed duration.
 * - UART reports which indicator is currently being tested.
 * - The corresponding physical indicator LED turns on.
 * - After the test sequence, all indicators are turned off.
 ******************************************************************************/

#include "app/indicator.h"
#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();
    Indicator_Init();

    UART_SendString("Indicator Test\r\n");

    while (1)
    {
        UART_SendString("Testing: REP MODE\r\n");
        Indicator_Set(INDICATOR_REP_MODE, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_REP_MODE, false);

        UART_SendString("Testing: TIMED MODE\r\n");
        Indicator_Set(INDICATOR_TIMED_MODE, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_TIMED_MODE, false);

        UART_SendString("Testing: TRAINING\r\n");
        Indicator_Set(INDICATOR_TRAINING, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_TRAINING, false);

        UART_SendString("Testing: RESTING\r\n");
        Indicator_Set(INDICATOR_RESTING, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_RESTING, false);

        UART_SendString("Testing: SURPASSED\r\n");
        Indicator_Set(INDICATOR_SURPASSED, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_SURPASSED, false);

        UART_SendString("Testing: LOW BATTERY\r\n");
        Indicator_Set(INDICATOR_LOW_BATTERY, true);
        Timer_Delay(1000U);
        Indicator_Set(INDICATOR_LOW_BATTERY, false);

        UART_SendString("Sequence complete\r\n\r\n");

        Timer_Delay(1000U);
    }
}