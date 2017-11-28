/*
 * Blocks sample vendor
 *
 * Copyright (C) 2017 BayLibre, SAS - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 *
 * Author(s) :
 * LE Phong <ple@baylibre.com>
 */

/* Includes ------------------------------------------------------------------*/

#include "vendor.h"
//#include "stm32l0xx_hal.h"
#include "stm32l4xx_hal.h"

static blocks_errorcode_t Block_Function_LedOn (uint8_t brightness)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);

	return ERROR_NONE;
}

static blocks_errorcode_t Block_Function_LedOff (void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);

	return ERROR_NONE;
}

void blocks_initializeModule (void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3 | GPIO_PIN_4);
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Registering our standard functions */
	blocks_registerStdFunc (FUNC_LED_ON, (blocks_standard_function)Block_Function_LedOn);
	blocks_registerStdFunc (FUNC_LED_OFF, (blocks_standard_function)Block_Function_LedOff);
}

void blocks_main (void)
{
	//while (1) {}
}
