#include "drivers/init.h"
#include "stm32f103xb.h"

void MCU_Init(void)
{   
    /**************************************************     
     * Flash configuration    
     **************************************************/
     
    /* set latency to 2 wait states
       in order for CPU to wait for Flash to catch up*/
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    /**************************************************     
     * Clock configuration    
     **************************************************/

    // Enable HSE
    RCC->CR |= RCC_CR_HSEON;
    // Wait untill the HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY)) 
    {
    }

    // Configure PLL
    RCC->CFGR &= ~RCC_CFGR_PLLSRC;
    RCC->CFGR |= RCC_CFGR_PLLSRC;   // Select HSE as PLL source
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;
    RCC->CFGR |= RCC_CFGR_PLLMULL9; // Select PLL multiplier x9

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    // Wait until the PLL is ready
    while (!(RCC->CR & RCC_CR_PLLRDY))
    {
    }

    // Switch system clock to PLL
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    // Wait until the switch is confirmed
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
    {
    }

    /**************************************************     
     * Disabling JTAG
     **************************************************/

    // Enable AFIO Clock
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // Disable JTAG in order to use PA15, PB3, and PB4 as GPIO Pins
    AFIO->MAPR &= ~AFIO_MAPR_SWJ_CFG;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE;
}