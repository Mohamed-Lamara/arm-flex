#include "app/indicator.h"
#include "drivers/gpio.h"
#include "stm32f103xb.h"

/* Indicator GPIO mapping
 * Intended only for V1 of the project
 */
#define INDICATOR_REP_MODE_PIN      GPIO_ODR_ODR11
#define INDICATOR_TIMED_MODE_PIN    GPIO_ODR_ODR10
#define INDICATOR_TRAINING_PIN      GPIO_ODR_ODR1
#define INDICATOR_RESTING_PIN       GPIO_ODR_ODR0
#define INDICATOR_SURPASSED_PIN     GPIO_ODR_ODR7   // GPIOA!
#define INDICATOR_LOW_BATTERY_PIN   GPIO_ODR_ODR15  // GPIOA!

// Sets the GPIO pin that corresponds to its specified indicator
void Indicator_Set(Indicator_t indicator, bool state)
{
    switch (indicator)
    {
        case INDICATOR_REP_MODE:
            GPIO_WritePin(GPIOB, INDICATOR_REP_MODE_PIN, state);
            break;
        case INDICATOR_TIMED_MODE:
            GPIO_WritePin(GPIOB, INDICATOR_TIMED_MODE_PIN, state);
            break;
        case INDICATOR_TRAINING:
            GPIO_WritePin(GPIOB, INDICATOR_TRAINING_PIN, state);
            break;
        case INDICATOR_RESTING:
            GPIO_WritePin(GPIOB, INDICATOR_RESTING_PIN, state);
            break;
        case INDICATOR_SURPASSED:
            GPIO_WritePin(GPIOA, INDICATOR_SURPASSED_PIN, state);
            break;
        case INDICATOR_LOW_BATTERY:
            GPIO_WritePin(GPIOA, INDICATOR_LOW_BATTERY_PIN, state);
            break;
        default:
            break;
    }
}

// initializes the indicators to their default state
void Indicator_Init(void)
{
    for (Indicator_t i = INDICATOR_REP_MODE; i < INDICATOR_ALL; i++) 
    {
        Indicator_Set(i, false);
    }
}