#include <stdio.h>
#include "main.h"
#include "ws2812b.h"
#include "air001xx_hal_uart.h"


void HAL_MspInit(void) {
    __HAL_RCC_SYSCFG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
}


UART_HandleTypeDef UART_HandleType = {0};
int main() {

    HAL_Init();
    APP_SPIConfig();



    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitTypeDef GPIO_InitStruct_uart = {0};
    GPIO_InitStruct_uart.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct_uart.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct_uart.Pull = GPIO_PULLUP;
    GPIO_InitStruct_uart.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct_uart.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct_uart);
    UART_HandleType.Instance = USART1;
    UART_HandleType.Init.BaudRate = 115200;
    UART_HandleType.Init.WordLength = UART_WORDLENGTH_8B;
    UART_HandleType.Init.StopBits = UART_STOPBITS_1;
    UART_HandleType.Init.Parity = UART_PARITY_NONE;
    UART_HandleType.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART_HandleType.Init.Mode = UART_MODE_TX_RX;
    if(HAL_UART_Init(&UART_HandleType) != HAL_OK){
    	HAL_Delay(3);
    }else{
    	HAL_Delay(2);
    }


    while (1) {
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0);
        HAL_Delay(1000);
        RGB_GREEN(LED_NUM);

        char buffer[] = "test\r\n";
        HAL_UART_Transmit(&UART_HandleType, buffer, sizeof(buffer), HAL_MAX_DELAY);
        HAL_Delay(2);
    }
}

