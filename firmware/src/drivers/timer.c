#include "drivers/timer.h"
#include "drivers/display.h"
#include "stm32f103xb.h"

#define SYS_CLOCK_HZ      72000000U
#define SYSTICK_FREQ_HZ   1000U         

static volatile uint32_t g_msTicks = 0U;

void Timer_Init(void) 
{   
    /**************************************************
     * SysTick Configuration
     **************************************************/

    // Configure a 1 ms SysTick time base 
    SysTick->LOAD = (SYS_CLOCK_HZ / SYSTICK_FREQ_HZ) - 1U;

    // Reset current value
    SysTick->VAL  = 0U; 

    // Configuring Control bits
    SysTick->CTRL =
      SysTick_CTRL_CLKSOURCE_Msk
    | SysTick_CTRL_TICKINT_Msk
    | SysTick_CTRL_ENABLE_Msk;
}

// Executed every 1 ms
void SysTick_Handler(void) 
{
    g_msTicks++; 

    Display_Update();
}

// function to provide ticks securely
uint32_t Timer_GetTicks(void)
{
    return g_msTicks;
}

// delay function for testing and debugging (Blocking!)
void Timer_Delay(uint32_t ms)
{
    uint32_t start = Timer_GetTicks();

    while ((Timer_GetTicks() - start) < ms)
    {
        // Wait...
    }
}