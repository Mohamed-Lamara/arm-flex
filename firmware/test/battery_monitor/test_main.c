/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Battery Monitor, ADC, UART, and Timer verification test.
 *
 * @details
 * Verifies the Battery Monitor by periodically sampling the battery-monitor
 * ADC input and reporting the resulting low-battery state over UART.
 *
 * Test Objective:
 * - Verify Battery Monitor initialization.
 * - Verify periodic ADC sampling.
 * - Verify low-battery threshold detection.
 * - Verify BatteryMonitor_IsLow() state reporting.
 * - Verify cooperation between Battery Monitor, ADC, UART, and Timer.
 *
 * Expected Result:
 * - The reported battery state changes when the ADC input crosses the
 *   configured low-battery threshold.
 * - "LOW" is reported below the threshold.
 * - "OK" is reported above the threshold.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/adc.h"
#include "app/battery_monitor.h"

#define TEST_UPDATE_INTERVAL_MS    500U

int main(void)
{
    uint32_t last_update = 0U;
    bool previous_low = false;
    bool current_low;

    MCU_Init();
    GPIO_Init();
    Timer_Init();
    ADC_Init();
    UART_Init();

    BatteryMonitor_Init();

    UART_SendString("Battery Monitor Test\r\n");

    while (1)
    {
        uint32_t current_tick = Timer_GetTicks();

        if ((current_tick - last_update) >= TEST_UPDATE_INTERVAL_MS)
        {
            last_update = current_tick;

            BatteryMonitor_Update();

            current_low = BatteryMonitor_IsLow();

            if (current_low != previous_low)
            {
                if (current_low)
                {
                    UART_SendString("Battery: LOW\r\n");
                }
                else
                {
                    UART_SendString("Battery: OK\r\n");
                }

                previous_low = current_low;
            }
        }
    }
}