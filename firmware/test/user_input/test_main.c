/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   User Input, UART, and Timer verification test.
 *
 * @details
 * Verifies the User Input module by continuously monitoring the six user
 * buttons and transmitting their debounced states over UART at fixed
 * time intervals.
 *
 * Test Objective:
 * - Verify UserInput initialization.
 * - Verify GPIO button input configuration.
 * - Verify button state reading and debouncing.
 * - Verify UART transmission of user input states.
 * - Verify Timer_Delay() functionality.
 * - Verify cooperation between User Input, GPIO, UART, and Timer modules.
 *
 * Expected Result:
 * - The state of all six user inputs is printed repeatedly over UART.
 * - Each input reports 0 when released and 1 when pressed.
 * - Pressing and releasing a button changes its reported state after
 *   the configured debounce interval.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "app/user_input.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();
    UserInput_Init();

    UART_SendString("User Input Test\r\n");

    while (1)
    {
        UserInput_Update();

        UART_SendString("INC: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_INCREMENT) + '0');

        UART_SendString(" | DEC: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_DECREMENT) + '0');

        UART_SendString(" | SEL: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_SELECT) + '0');

        UART_SendString(" | START: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_START_FINISH) + '0');

        UART_SendString(" | RESET: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_RESET) + '0');

        UART_SendString(" | MODE: ");
        UART_SendChar(UserInput_IsPressed(USER_INPUT_MODE) + '0');

        UART_SendString("\r\n");

        Timer_Delay(200U);
    }
}