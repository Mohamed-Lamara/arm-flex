/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   UART and GPIO verification test.
 *
 * @details
 * Verifies the basic firmware infrastructure by sending repeated UART messages
 * while toggling the LED connected to PA15 using the GPIO and Timer drivers.
 *
 * Test Objective:
 * - Verify MCU clock initialization.
 * - Verify GPIO configuration.
 * - Verify SysTick interrupt operation.
 * - Verify Timer_Delay() functionality.
 * - Verify UART transmission via serial monitor.
 * - Verify cooperation between UART, GPIO, and Timer drivers.
 *
 * Expected Result:
 * - "UART is On Air!" is printed repeatedly over UART.
 * - LED on PA15 toggles during the test sequence.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "stm32f103xb.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();

    while (1)
    {
        UART_SendString("UART is On Air!\r\n");
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(100);
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(100);
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(100);
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(100);
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(1000);
        GPIO_WritePin(GPIOA, GPIO_ODR_ODR15, 0);
        Timer_Delay(1500);
    }
}