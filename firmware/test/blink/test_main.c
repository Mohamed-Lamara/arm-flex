/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   GPIO and SysTick timer verification test.
 *
 * @details
 * Verifies the basic firmware infrastructure by toggling the LED connected
 * to PA15 at a 1-second interval using the Timer driver.
 *
 * Test Objective:
 * - Verify MCU clock initialization.
 * - Verify GPIO configuration.
 * - Verify SysTick interrupt operation.
 * - Verify Timer_Delay() functionality.
 *
 * Expected Result:
 * - LED on PA15 toggles every 1000 ms.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "stm32f103xb.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();

    while (1)
    {
        GPIO_TogglePin(GPIOA, GPIO_ODR_ODR15);
        Timer_Delay(1000);
    }
}