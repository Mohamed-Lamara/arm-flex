/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   Sensor and EXTI verification test.
 *
 * @details
 * Verifies the repetition sensor by detecting sensor events through the EXTI
 * interrupt mechanism and processing them through the Sensor module.
 *
 * Test Objective:
 *
 * - Verify sensor initialization.
 * - Verify EXTI interrupt event capture.
 * - Verify Sensor_CaptureEvent() communication with the ISR.
 * - Verify sensor event processing in the main loop.
 * - Verify repetition event detection.
 * - Verify the minimum repetition interval filter.
 * - Verify UART reporting of detected repetitions.
 *
 * Expected Result:
 *
 * - Triggering the Hall sensor produces one "REP DETECTED" message.
 * - Repeated sensor events occurring within the minimum repetition interval
 *   are ignored.
 * - Valid sensor events occurring after the minimum interval are detected.
 * - The main loop remains non-blocking while sensor events are processed.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/exti.h"
#include "app/sensor.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();
    EXTI_Init();
    Sensor_Init();

    UART_SendString("Sensor test started\r\n");

    while (1)
    {
        Sensor_Update();

        if (Sensor_IsRepDetected())
        {
            UART_SendString("REP DETECTED\r\n");
        }
    }
}