#include "drivers/gpio.h"
#include "stm32f103xb.h"

// GPIO Configuration Field
#define GPIO_CFG_FIELD(pin)    ((pin) * 4U)

// GPIO Configuration Values
#define GPIO_INPUT_ANALOG      0x0U
#define GPIO_INPUT_PULL        0x8U
#define GPIO_OUTPUT_PP_2MHZ    0x2U

void GPIO_Init(void)
{
    // Enable GPIO peripheral clocks
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN;

    /**************************************************
     * GPIOA Configuration
     **************************************************/

    // PA0 : ADC_IN (Analog Input)
    GPIOA->CRL &= ~(0xFU << GPIO_CFG_FIELD(0));
    GPIOA->CRL |=  (GPIO_INPUT_ANALOG << GPIO_CFG_FIELD(0));

    // PA1-PA6 : User-Input Buttons (Input Pull-down)
    GPIOA->CRL &= ~((0xFU << GPIO_CFG_FIELD(1)) |
                    (0xFU << GPIO_CFG_FIELD(2)) |
                    (0xFU << GPIO_CFG_FIELD(3)) |
                    (0xFU << GPIO_CFG_FIELD(4)) |
                    (0xFU << GPIO_CFG_FIELD(5)) |
                    (0xFU << GPIO_CFG_FIELD(6)));

    GPIOA->CRL |=  ((GPIO_INPUT_PULL << GPIO_CFG_FIELD(1)) |
                    (GPIO_INPUT_PULL << GPIO_CFG_FIELD(2)) |
                    (GPIO_INPUT_PULL << GPIO_CFG_FIELD(3)) |
                    (GPIO_INPUT_PULL << GPIO_CFG_FIELD(4)) |
                    (GPIO_INPUT_PULL << GPIO_CFG_FIELD(5)) |
                    (GPIO_INPUT_PULL << GPIO_CFG_FIELD(6)));

    // PA7 : LED_SURP (Output Push-Pull 2 MHz)
    GPIOA->CRL &= ~(0xFU << GPIO_CFG_FIELD(7));
    GPIOA->CRL |=  (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(7));

    // PA8 : BUZZER ; PA15: LED_LOWB

    GPIOA->CRH &= ~((0xFU << GPIO_CFG_FIELD(0)) |
                    (0xFU << GPIO_CFG_FIELD(7)));

    GPIOA->CRH |=  ((GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(0)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(7)));

    // PA11 : SENSOR (Input Pull-up)
    GPIOA->CRH &= ~(0xFU << GPIO_CFG_FIELD(3));
    GPIOA->CRH |=  (GPIO_INPUT_PULL << GPIO_CFG_FIELD(3));

    // Enable internal pull-downs for buttons
    GPIOA->ODR &= ~(GPIO_ODR_ODR1 |
                    GPIO_ODR_ODR2 |
                    GPIO_ODR_ODR3 |
                    GPIO_ODR_ODR4 |
                    GPIO_ODR_ODR5 |
                    GPIO_ODR_ODR6);

    // Enable internal pull-up for sensor
    GPIOA->ODR |= GPIO_ODR_ODR11;

    /**************************************************
     * GPIOB Configuration
     **************************************************/

    // PB0-PB1 : Training Mode LEDs 
    GPIOB->CRL &= ~((0xFU << GPIO_CFG_FIELD(0)) |
                    (0xFU << GPIO_CFG_FIELD(1)));

    GPIOB->CRL |=  ((GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(0)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(1)));

    // PB3-PB7 : Display Segments E-G and CC4
    GPIOB->CRL &= ~((0xFU << GPIO_CFG_FIELD(3)) |
                    (0xFU << GPIO_CFG_FIELD(4)) |
                    (0xFU << GPIO_CFG_FIELD(5)) |
                    (0xFU << GPIO_CFG_FIELD(6)) |
                    (0xFU << GPIO_CFG_FIELD(7)));

    GPIOB->CRL |=  ((GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(3)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(4)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(5)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(6)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(7)));

    // PB8-PB15 : Display, Common Cathodes and Status LEDs 
    GPIOB->CRH &= ~((0xFU << GPIO_CFG_FIELD(0)) |
                    (0xFU << GPIO_CFG_FIELD(1)) |
                    (0xFU << GPIO_CFG_FIELD(2)) |
                    (0xFU << GPIO_CFG_FIELD(3)) |
                    (0xFU << GPIO_CFG_FIELD(4)) |
                    (0xFU << GPIO_CFG_FIELD(5)) |
                    (0xFU << GPIO_CFG_FIELD(6)) |
                    (0xFU << GPIO_CFG_FIELD(7)));

    GPIOB->CRH |=  ((GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(0)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(1)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(2)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(3)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(4)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(5)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(6)) |
                    (GPIO_OUTPUT_PP_2MHZ << GPIO_CFG_FIELD(7)));
}

bool GPIO_ReadPin(GPIO_TypeDef *port, uint16_t pin)
{
    return (port->IDR & pin) != 0U;
}

void GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, bool state)
{
    if (state)
    {
        port->BSRR = pin;
    }
    else
    {
        port->BSRR = (uint32_t)pin << 16U;
    }
}

void GPIO_TogglePin(GPIO_TypeDef *port, uint16_t pin)
{
    port->ODR ^= pin;
}