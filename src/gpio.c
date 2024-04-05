/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
UART_HandleTypeDef UART_HandleType = {0};
void MX_GPIO_Init(void)
{


//	GPIO_InitTypeDef GPIO_InitStruct_Led = {0};
//	GPIO_InitStruct_Led.Pin = GPIO_PIN_2 | GPIO_PIN_1 | GPIO_PIN_0;
//	GPIO_InitStruct_Led.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct_Led.Pull = GPIO_PULLUP;
//	GPIO_InitStruct_Led.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct_Led);

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
	if (HAL_UART_Init(&UART_HandleType) != HAL_OK)
	  {
	    _Error_Handler(__FILE__, __LINE__);
	  }

  GPIO_InitTypeDef GPIO_InitStruct;



  /*Configure GPIO pin Output Level */


  /*Configure GPIO pins : PAPin PAPin PAPin */
  GPIO_InitStruct.Pin = DS18B20_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF13_TIM1;
  HAL_GPIO_Init(DS18B20_PORT, &GPIO_InitStruct);
  HAL_GPIO_WritePin(DS18B20_PORT, DS18B20_PIN, GPIO_PIN_RESET);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
