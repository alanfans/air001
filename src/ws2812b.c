/*
 * ws2812.c
 *
 *  Created on: Dec 8, 2023
 *      Author: alanfans
 */


#include "ws2812b.h"
//#include "tim.h"

/*Some Static Colors------------------------------*/
const RGB_Color_TypeDef RED      = {255,0,0};   //显示红色RGB数据
const RGB_Color_TypeDef ORANGE   = {127,106,0};
const RGB_Color_TypeDef YELLOW   = {127,216,0};
const RGB_Color_TypeDef GREEN    = {0,255,0};
const RGB_Color_TypeDef CYAN	   = {0,255,255};
const RGB_Color_TypeDef BLUE     = {0,0,255};
const RGB_Color_TypeDef PURPLE	 = {238,130,238};
const RGB_Color_TypeDef BLACK    = {0,0,0};
const RGB_Color_TypeDef WHITE    = {255,255,255};
const RGB_Color_TypeDef MAGENTA  = {255,0,220};


/*二维数组存放最终PWM输出数组，每一行24个
数据代表一个LED，最后一行24个0代表RESET码*/
uint8_t Pixel_Buf[LED_NUM+1][24];

SPI_HandleTypeDef htim2;
void APP_SPIConfig(void)
{
  SPI_InitTypeDef SPI_InitStruct = {0};
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_SPI1_CLK_ENABLE();

  // PA7 MOSI
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* The frequency after prescaler should be below 8.25MHz */
  SPI_InitStruct.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  SPI_InitStruct.Direction = SPI_DIRECTION_2LINES;
  SPI_InitStruct.Mode = SPI_MODE_MASTER;
  SPI_InitStruct.DataSize = SPI_DATASIZE_8BIT;
  SPI_InitStruct.CLKPolarity = SPI_POLARITY_LOW;
  SPI_InitStruct.CLKPhase = SPI_PHASE_2EDGE;
  SPI_InitStruct.NSS = SPI_NSS_SOFT;
  SPI_InitStruct.FirstBit = SPI_FIRSTBIT_MSB;

  htim2.Init = SPI_InitStruct;
  htim2.Instance = SPI1;
//  SPI_InitHandleStruct.Lock = HAL_UNLOCKED;
  HAL_SPI_Init(&htim2);
}
/*
功能：设定单个RGB LED的颜色，把结构体中RGB的24BIT转换为0码和1码
参数：LedId为LED序号，Color：定义的颜色结构体
*/
void RGB_SetColor(uint8_t LedId,RGB_Color_TypeDef Color)
{
	uint8_t i;
	if(LedId > LED_NUM)return; //avoid overflow 防止写入ID大于LED总数

	for(i=0;i<8;i++)   Pixel_Buf[LedId][i]   = ( (Color.G & (1 << (7 -i)))? (CODE_1):CODE_0);//数组某一行0~7转化存放G
	for(i=8;i<16;i++)  Pixel_Buf[LedId][i]   = ( (Color.R & (1 << (15-i)))? (CODE_1):CODE_0);//数组某一行8~15转化存放R
	for(i=16;i<24;i++) Pixel_Buf[LedId][i]   = ( (Color.B & (1 << (23-i)))? (CODE_1):CODE_0);//数组某一行16~23转化存放B

}

/*
功能：最后一行装在24个0，输出24个周期占空比为0的PWM波，作为最后reset延时，这里总时长为24*1.2=30us > 24us(要求大于24us)
*/
void Reset_Load(void)
{
	uint8_t i;
	for(i=0;i<24;i++)
	{
		Pixel_Buf[LED_NUM][i] = 0;
	}
}

/*
功能：发送数组
参数：(&htim1)定时器1，(TIM_CHANNEL_2)通道2，((uint32_t *)Pixel_Buf)待发送数组，
			(Pixel_NUM+1)*24)发送个数，数组行列相乘
*/
void RGB_SendArray(void)
{
//	HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_3, (uint32_t *)Pixel_Buf,(LED_NUM+1)*24);
	HAL_SPI_Transmit(&htim2,(uint8_t *)Pixel_Buf,(uint16_t)(LED_NUM+1)*24,HAL_MAX_DELAY);
}

/*
功能：显示红色
参数：Pixel_Len为显示LED个数
*/
void RGB_RED(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//给对应个数LED写入红色
	{
		RGB_SetColor(i,RED);
	}
	Reset_Load();
	RGB_SendArray();
}

/*
功能：显示绿色
参数：Pixel_Len为显示LED个数
*/
void RGB_GREEN(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//给对应个数LED写入绿色
	{
		RGB_SetColor(i,GREEN);
	}
	Reset_Load();
	RGB_SendArray();
}

/*
功能：显示蓝色
参数：Pixel_Len为显示LED个数
*/
void RGB_BLUE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//给对应个数LED写入蓝色
	{
		RGB_SetColor(i,BLUE);
	}
	Reset_Load();
	RGB_SendArray();
}

/*
功能：显示白色
参数：Pixel_Len为显示LED个数
*/
void RGB_WHITE(uint16_t Pixel_Len)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)//给对应个数LED写入白色
	{
		RGB_SetColor(i,WHITE);
	}
	Reset_Load();
	RGB_SendArray();
}

//用户自定义API接口可根据实际拓展

/*******************************************************************************/
/*									添加部分									   */

//显示指定颜色
static void rgb_show(uint32_t Pixel_Len, RGB_Color_TypeDef rgb)
{
	uint16_t i;
	for(i=0;i<Pixel_Len;i++)
	{
		RGB_SetColor(i,rgb);
	}
	Reset_Load();
	RGB_SendArray();
}

//颜色循环转换
static RGB_Color_TypeDef Wheel(uint8_t WheelPos)
{
	RGB_Color_TypeDef rgb;
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85)
	{
		rgb.R = 255 - WheelPos * 3;
		rgb.G = 0;
		rgb.B = WheelPos * 3;
		return rgb;
	}
	if (WheelPos < 170)
	{
		WheelPos -= 85;
		rgb.R = 0;
		rgb.G = WheelPos * 3;
		rgb.B = 255 - WheelPos * 3;
		return rgb;
	}
	WheelPos -= 170;
	rgb.R = WheelPos * 3;
	rgb.G = 255 - WheelPos * 3;
	rgb.B = 0;
	return rgb;
}

//彩虹呼吸灯
static void rainbow(uint8_t wait)
{
	uint32_t timestamp = HAL_GetTick();
	uint16_t i;
	static uint8_t j;
	static uint32_t next_time = 0;

	uint32_t flag = 0;
	if (next_time < wait)
	{
		if ((uint64_t)timestamp + wait - next_time > 0)
			flag = 1;
	}
	else if (timestamp > next_time)
	{
		flag = 1;
	}
	if (flag)    // && (timestamp - next_time < wait*5))
	{
		j++;
		next_time = timestamp + wait;
		for (i = 0; i < LED_NUM; i++)
		{
			RGB_SetColor(i, Wheel((i + j) & 255));
		}
	}
	RGB_SendArray();
}

//彩虹灯旋转
static void rainbowCycle(uint8_t wait)
{
	uint32_t timestamp = HAL_GetTick();
	uint16_t i;
	static uint8_t j;
	static uint32_t next_time = 0;

	static uint8_t loop = 0;
	if (loop == 0)
		next_time = timestamp;
	loop = 1;    //首次调用初始化

	if ((timestamp > next_time))    // && (timestamp - next_time < wait*5))
	{
		j++;
		next_time = timestamp + wait;
		for (i = 0; i < LED_NUM; i++)
		{
			RGB_SetColor(i, Wheel(((i * 256 / (LED_NUM)) + j) & 255));
		}
	}
	RGB_SendArray();
}
