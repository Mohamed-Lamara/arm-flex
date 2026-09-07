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