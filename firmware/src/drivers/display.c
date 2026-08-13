#include "drivers/display.h"
#include "drivers/gpio.h"

#define DISPLAY_DIGITS      (4U)
#define DISPLAY_NUMBERS     (10U)

// Private function prototypes
static void Display_SetSegments(uint8_t pattern);
static void Display_DisableAllDigits(void);
static void Display_EnableDigit(uint8_t digit);

// Logical segment representation
enum
{
    SEG_A = (1U << 0),
    SEG_B = (1U << 1),
    SEG_C = (1U << 2),
    SEG_D = (1U << 3),
    SEG_E = (1U << 4),
    SEG_F = (1U << 5),
    SEG_G = (1U << 6)
};

// Segment pattern for the minus sign
#define SEG_MINUS    SEG_G

// Segment patterns for decimal digits 0-9
static const uint8_t segmentMap[DISPLAY_NUMBERS] =
{
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,         // 0
    SEG_B | SEG_C,                                         // 1
    SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,                 // 2
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,                 // 3
    SEG_B | SEG_C | SEG_F | SEG_G,                         // 4
    SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,                 // 5
    SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,         // 6
    SEG_A | SEG_B | SEG_C,                                 // 7
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 8
    SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G          // 9
};

// Stores segment patterns for the four display digits
static uint8_t displayBuffer[DISPLAY_DIGITS] = {0U};

static uint8_t firstVisibleDigit = 0U;
static uint8_t currentDigit = 0U;
static uint8_t displayEnabled = 0U;

// Displays a decimal number from 0 to 9999
void Display_SetNumber(uint16_t value)
{
    // Saturate if value is over the maximum
    if (value > 9999U)
    {
        value = 9999U;
    }

    // Split the number into individual decimal digits
    for (int i = DISPLAY_DIGITS - 1; i >= 0; i--)
    {
        displayBuffer[i] = segmentMap[value % 10U];
        value /= 10U;
    }

    // Find the first non-zero digit
    // Keep the last digit visible so that 0 is still displayed
    firstVisibleDigit = 0U;

    while (firstVisibleDigit < (DISPLAY_DIGITS - 1U))
    {
        // Check whether this digit is displaying zero.
        //
        // Since the buffer now contains segment patterns,
        // compare against the pattern for zero.
        if (displayBuffer[firstVisibleDigit] != segmentMap[0])
        {
            break;
        }

        firstVisibleDigit++;
    }

    displayEnabled = 1U;
}

// Displays a minus sign on the first digit
void Display_SetMinus(void)
{
    // Clear all digits
    for (uint8_t i = 0U; i < DISPLAY_DIGITS; i++)
    {
        displayBuffer[i] = 0U;
    }

    // Place the minus sign on the first digit
    displayBuffer[0] = SEG_MINUS;

    firstVisibleDigit = 0U;
    displayEnabled = 1U;
}

// Initializes the display
void Display_Init(void)
{
    Display_Clear();

    currentDigit = 0U;
}

// Refreshes the currently active digit
void Display_Update(void)
{
    // Disable all digits before changing the segment pattern
    Display_DisableAllDigits();

    // Do nothing if the display is disabled
    if (displayEnabled == 0U)
    {
        return;
    }

    // Blank leading zeros
    if (currentDigit < firstVisibleDigit)
    {
        Display_SetSegments(0U);
    }
    else
    {
        Display_SetSegments(displayBuffer[currentDigit]);
    }

    // Enable only the current digit
    Display_EnableDigit(currentDigit);

    // Move to the next digit
    currentDigit++;

    // Wrap around after the last digit
    if (currentDigit >= DISPLAY_DIGITS)
    {
        currentDigit = 0U;
    }
}

// Clears the display
void Display_Clear(void)
{
    // Disable all digits immediately
    Display_DisableAllDigits();

    // Turn all segments OFF immediately
    Display_SetSegments(0U);

    // Clear the display buffer
    for (uint8_t i = 0U; i < DISPLAY_DIGITS; i++)
    {
        displayBuffer[i] = 0U;
    }

    // Disable display rendering
    displayEnabled = 0U;

    // Restart multiplexing from the first digit
    currentDigit = 0U;

    // Reset leading-zero state
    firstVisibleDigit = 0U;
}

// Set the physical segment outputs according to a logical pattern
static void Display_SetSegments(uint8_t pattern)
{
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR14, (pattern & SEG_A) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR8,  (pattern & SEG_B) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR5,  (pattern & SEG_C) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR4,  (pattern & SEG_D) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR3,  (pattern & SEG_E) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR15, (pattern & SEG_F) != 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR6,  (pattern & SEG_G) != 0U);
}

// Disable all four display digits
static void Display_DisableAllDigits(void)
{
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR12, 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR13, 0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR9,  0U);
    GPIO_WritePin(GPIOB, GPIO_ODR_ODR7,  0U);
}

// Enable one display digit
static void Display_EnableDigit(uint8_t digit)
{
    switch (digit)
    {
        case 0U:
            GPIO_WritePin(GPIOB, GPIO_ODR_ODR12, 1U);
            break;

        case 1U:
            GPIO_WritePin(GPIOB, GPIO_ODR_ODR13, 1U);
            break;

        case 2U:
            GPIO_WritePin(GPIOB, GPIO_ODR_ODR9, 1U);
            break;

        case 3U:
            GPIO_WritePin(GPIOB, GPIO_ODR_ODR7, 1U);
            break;

        default:
            break;
    }
}