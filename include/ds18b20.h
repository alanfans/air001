/*
 * ds18b20.h
 *
 *  Created on: Apr 3, 2024
 *      Author: alanfans
 */

#ifndef INCLUDE_DS18B20_H_
#define INCLUDE_DS18B20_H_
#include "tim.h"
#include "air001xx_hal.h"

#define DS18B20_PORT GPIOA
#define DS18B20_PIN GPIO_PIN_1

void delay(uint32_t us);
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
uint8_t DS18B20_Start(void);
void DS18B20_Write(uint8_t data);
uint8_t DS18B20_Read(void);
void DS18B20_TEMP(void);




#endif /* INCLUDE_DS18B20_H_ */
