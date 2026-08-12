#include "drivers/exti.h"
#include "app/sensor.h"
#include "stm32f103xb.h"

void EXTI_Init(void)
{
    // Route EXTI11 to PA11
    AFIO->EXTICR[2] &= ~(0xFU << 12U);

    // Configure EXTI11 for rising-edge detection
    EXTI->RTSR |= EXTI_RTSR_TR11;
    EXTI->FTSR &= ~EXTI_FTSR_TR11;

    // Clear any pending interrupt
    EXTI->PR = EXTI_PR_PR11;

    // Enable EXTI11 interrupt 
    EXTI->IMR |= EXTI_IMR_MR11;

    // Enable EXTI15_10 interrupt in NVIC
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

// EXTI11 interrupt handler
void EXTI15_10_IRQHandler(void)
{
    if (EXTI->PR & EXTI_PR_PR11)
    {
        // Clear interrupt pending flag
        EXTI->PR = EXTI_PR_PR11;

        // Notify Sensor module
        Sensor_CaptureEvent();
    }
}