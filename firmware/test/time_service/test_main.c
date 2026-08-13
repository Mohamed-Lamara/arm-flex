/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Time Service verification test.
 *
 * @details
 * Verifies the Time Service using the system tick provided by the Timer
 * driver. The test exercises rest countdown timing, timed-mode countdown
 * timing, and elapsed-time tracking after the timed target is reached.
 *
 * Test Objective:
 *
 * - Verify TimeService initialization.
 * - Verify rest countdown timing.
 * - Verify timed-mode countdown timing.
 * - Verify timed-mode completion detection.
 * - Verify post-surpassed elapsed-time tracking.
 * - Verify UART reporting of timing values.
 *
 * Expected Result:
 *
 * - Rest countdown decreases from the configured duration to zero.
 * - Timed-mode countdown decreases from the configured duration to zero.
 * - Timed-mode completion is detected at the configured duration.
 * - Elapsed time starts from zero after the surpassed timer is started.
 * - Elapsed time increases once per second.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "app/time_service.h"

int main(void)
{
    uint16_t remaining;
    uint16_t elapsed;

    MCU_Init();
    Timer_Init();
    UART_Init();
    TimeService_Init();

    UART_SendString("Time Service test started\r\n");

    // Test rest countdown
    TimeService_StartRest(10U);

    while (!TimeService_IsRestFinished())
    {
        remaining = TimeService_GetRestRemaining();

        UART_SendString("Rest remaining: ");
        UART_SendUInt16(remaining);
        UART_SendString(" s\r\n");

        Timer_Delay(1000U);
    }

    UART_SendString("Rest finished\r\n");

    // Test timed-mode countdown
    TimeService_StartTimed(10U);

    while (!TimeService_IsTimedFinished())
    {
        remaining = TimeService_GetTimedRemaining();

        UART_SendString("Timed remaining: ");
        UART_SendUInt16(remaining);
        UART_SendString(" s\r\n");

        Timer_Delay(1000U);
    }

    UART_SendString("Timed duration finished\r\n");

    // Test elapsed time after the timed target is reached
    TimeService_StartSurpassed();

    for (uint8_t i = 0U; i < 5U; i++)
    {
        elapsed = TimeService_GetTimedElapsed();

        UART_SendString("Surpassed elapsed: ");
        UART_SendUInt16(elapsed);
        UART_SendString(" s\r\n");

        Timer_Delay(1000U);
    }

    UART_SendString("Time Service test finished\r\n");

    while (1)
    {
    }
}