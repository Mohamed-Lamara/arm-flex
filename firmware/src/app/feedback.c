#include "app/feedback.h"
#include "drivers/gpio.h"
#include "drivers/timer.h"
#include "stm32f103xb.h"

#define FEEDBACK_PIN    GPIO_ODR_ODR8

static bool feedback_active;
static uint32_t feedback_start_tick;
static uint16_t feedback_duration_ms;

// Initializes the feedback's pin and states
void Feedback_Init(void)
{
    GPIO_WritePin(GPIOA, FEEDBACK_PIN, false);
    feedback_active = false;
    feedback_start_tick = 0U;
    feedback_duration_ms = 0U;
}

// Plays Feedback for a certain duration
void Feedback_Play(uint16_t duration_ms)
{
    if (duration_ms == 0U)
    {
        GPIO_WritePin(GPIOA, FEEDBACK_PIN, false);
        feedback_active = false;
        return;
    }
    feedback_start_tick = Timer_GetTicks();
    GPIO_WritePin(GPIOA, FEEDBACK_PIN, true);
    feedback_active = true;
    feedback_duration_ms = duration_ms;
}

/* Checks whether the feedback duration has elapsed
 * and turns it off after
 */
void Feedback_Update(void)
{
    if (feedback_active && (Timer_GetTicks() - feedback_start_tick >= feedback_duration_ms)) 
    {
        GPIO_WritePin(GPIOA, FEEDBACK_PIN, false);
        feedback_active = false;
        feedback_start_tick = 0U;
        feedback_duration_ms = 0U;
    }
}