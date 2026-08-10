#include "drivers/uart.h"
#include "stm32f103xb.h"

void UART_Init()
{
    // Enable USART1 clock
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9 : USART1_TX (Alternate Function Push-Pull, 2 MHz)
    GPIOA->CRH &= ~(0xFU << (1U * 4));
    GPIOA->CRH |=  (0xAU << (1U * 4));

    // PA10 : USART1_RX (Input Floating)
    GPIOA->CRH &= ~(0xFU << (2U * 4));
    GPIOA->CRH |=  (0x4U << (2U * 4));

    // Baud-Rate Calculated for 115200 (refer to the reference manual)
    USART1->BRR = 0x0271U;

    // Enable transmitter and reciever
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE;

    // Enable USART
    USART1->CR1 |= USART_CR1_UE;
}

void UART_SendChar(char c)
{
    // Wait until the Transmit data register is empty
    while (!(USART1->SR & USART_SR_TXE))
    {
    }

    // Write the byte to the data register
    USART1->DR = (uint16_t)c;
}

void UART_SendString(const char *str)
{
    while (*str != '\0')        // '\0' is the null terminator
    {
        UART_SendChar(*str);
        str++;
    }
}

/* Temporary utility function for driver verification.
 * Integer formatting will later be moved to a dedicated formatting module.
 */

void UART_SendUInt16(uint16_t value)
{
    uint8_t digits[5];
    uint8_t count = 0U;

    if (value == 0U)
    {
        UART_SendChar('0');
        return;
    }    

    while (value > 0U)
    {
        digits[count] = value % 10U;
        value /= 10U;
        count++;
    }

    for (int i = (count - 1); i >= 0; i--)
    {
        UART_SendChar(digits[i] + '0');
    }
}