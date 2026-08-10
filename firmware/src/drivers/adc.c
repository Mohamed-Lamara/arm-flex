#include "drivers/adc.h"
#include "stm32f103xb.h"

void ADC_Init(void)
{
    // Enable the ADC1 Peripheral Clock
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    // Set ADC prescaler to PCLK2 / 6 (72 MHz / 6 = 12 MHz)
    RCC->CFGR &= ~RCC_CFGR_ADCPRE; // clear its bits
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;

    // Turn the ADC On
    ADC1->CR2 |= ADC_CR2_ADON;

    // Reset calibration and wait for it to finish
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);

    // Start calibration and wait for it to finish
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);
}

uint16_t ADC_Read(void) 
{
    // Start conversion
    ADC1->CR2 |= ADC_CR2_ADON;

    // Wait until conversion completes
    while (!(ADC1->SR & ADC_SR_EOC))
    {
    }

    // Return converted value
    return (uint16_t)ADC1->DR;
}