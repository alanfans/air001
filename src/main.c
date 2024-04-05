#include <stdio.h>
#include "main.h"
//#include "ws2812b.h"
#include "air001xx_hal_uart.h"

static void SystemClock_Config(uint32_t HSICLKSOURCE_SET);
void HAL_MspInit(void) {
	/* GPIO Ports Clock Enable */
//	__HAL_RCC_SYSCFG_CLK_ENABLE();
//	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_RCC_USART1_CLK_ENABLE();

//	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

extern UART_HandleTypeDef UART_HandleType;
extern float Temperature;
char message[50];
void PrintFloat(float value)
{
    int tmp,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6;
    tmp = (int)value;
    tmp1=(int)((value-tmp)*10)%10;
    tmp2=(int)((value-tmp)*100)%10;
    tmp3=(int)((value-tmp)*1000)%10;
    tmp4=(int)((value-tmp)*10000)%10;
    tmp5=(int)((value-tmp)*100000)%10;
    tmp6=(int)((value-tmp)*1000000)%10;
    sprintf(message,"温度Temperature: %d.%d%d%d%d%d%d\r\n",tmp,tmp1,tmp2,tmp3,tmp4,tmp5,tmp6);
}

int main() {

	HAL_Init();
	SystemClock_Config(RCC_HSICALIBRATION_24MHz);
	MX_GPIO_Init();
	MX_TIM1_Init();
	HAL_TIM_Base_Start(&htim1); // 启动TIM1定时器
//	APP_SPIConfig();

	while (1) {

//

		DS18B20_TEMP();
		PrintFloat(Temperature);
//		sprintf(message, "温度Temperature: %.2f C\n", Temperature);
		HAL_UART_Transmit(&UART_HandleType, message, sizeof(message), HAL_MAX_DELAY);
//
		HAL_Delay(1000);
	}
}

/** System Clock Configuration
 */
void SystemClock_Config(uint32_t HSICLKSOURCE_SET) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;

	/**Configure the main internal regulator output voltage
	 */

//  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI
			| RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = HSICLKSOURCE_SET;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}
