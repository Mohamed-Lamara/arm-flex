/******************************************************************************
 * @file    test_main.c
 * @author  Mohamed Lamara
 * @brief   ADC, UART, and Timer verification test.
 *
 * @details
 * Verifies the Analog-to-Digital Converter by continuously sampling the
 * analog input connected to PA0 and transmitting the measured ADC value over
 * UART at fixed time intervals.
 *
 * Test Objective:
 * - Verify ADC initialization and calibration.
 * - Verify analog-to-digital conversion.
 * - Verify UART transmission of ADC readings.
 * - Verify Timer_Delay() functionality.
 * - Verify cooperation between ADC, UART, and Timer drivers.
 *
 * Expected Result:
 * - ADC conversion values are printed repeatedly over UART.
 * - Rotating the potentiometer changes the reported ADC values smoothly from
 *   approximately 0 to 4095.
 ******************************************************************************/

#include "drivers/init.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "drivers/uart.h"
#include "drivers/adc.h"

int main(void)
{
    MCU_Init();
    GPIO_Init();
    Timer_Init();
    UART_Init();
    ADC_Init();
    
    while (1)
    {
        uint16_t value = ADC_Read();

        UART_SendString("Value: ");
        UART_SendUInt16(value);
        UART_SendString("\r\n");

        Timer_Delay(100);
    }
}