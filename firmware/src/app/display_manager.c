#include "app/display_manager.h"
#include "drivers/display.h"

// Initializes the display manager
void DisplayManager_Init(void)
{
    Display_Clear();
}

// Displays a numerical value
void DisplayManager_ShowNumber(uint16_t number)
{
    Display_SetNumber(number);
}

// Displays time in seconds or M-SS format
void DisplayManager_ShowTime(uint16_t seconds)
{
    uint16_t minutes;
    uint16_t remaining_seconds;
    uint16_t display_value;

    // Display seconds directly when below one minute
    if (seconds < 60U)
    {
        Display_SetNumber(seconds);
        return;
    }

    // Limit the display to a maximum of 9 minutes 59 seconds
    if (seconds > 599U)
    {
        seconds = 599U;
    }

    // Convert total seconds into minutes and seconds
    minutes = seconds / 60U;
    remaining_seconds = seconds % 60U;

    // Build M-SS while keeping the minute in the first digit
    display_value = (minutes * 1000U) + remaining_seconds;

    // Display the four digits
    Display_SetNumber(display_value);

    // Replace the second digit with the '-' separator
    Display_SetMinus(1U);
}