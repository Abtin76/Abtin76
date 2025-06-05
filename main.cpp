#include "stm32f4xx_hal.h"

UART_HandleTypeDef huart2;

void uart_init(void);
void SysTick_Handler(void);

char message[30] = "Hello my name is Abtin\r\n";  // Add newline for serial readability

int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

int main(void)
{
    HAL_Init();
    uart_init();  // Call after HAL_Init()

    while (1)
    {
        printf("Printf being used");
        HAL_Delay(100);
    }
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}

void uart_init(void)
{
    GPIO_InitTypeDef GPIO_initstruct = {0};

    // ✅ Correct Clock Enable Macros
    __HAL_RCC_GPIOA_CLK_ENABLE();      // Enable GPIOA clock (PA2, PA3)
    __HAL_RCC_USART2_CLK_ENABLE();     // Enable USART2 clock

    // ✅ Correct GPIO setup
    GPIO_initstruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_initstruct.Mode = GPIO_MODE_AF_PP;
    GPIO_initstruct.Pull = GPIO_NOPULL;  // typo corrected: GPOI_NOPULL → GPIO_NOPULL
    GPIO_initstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_initstruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_initstruct);

    // ✅ Correct USART and UART settings
    huart2.Instance = USART2;  // Typo fixed: USART → USART2
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;  // Typo fixed: UART_WORLDLENGTH → UART_WORDLENGTH
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;  // Better to enable RX too
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        while (1);  // Init failed
    }
}

