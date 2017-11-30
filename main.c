#include "vendor.h"
#include "stm32l0xx_hal.h"
	
static blocks_errorcode_t Block_Function_LedOn (uint8_t brightness) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);
	return ERROR_NONE;
}

static blocks_errorcode_t Block_Function_LedOff (void) {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_RESET);
	return ERROR_NONE;
}

void blocks_initializeModule (void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3 | GPIO_PIN_4);
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void blocks_main (void) {
}

const ModuleInfo blocks_module_info = { 
	.label = u"Module Label", 
	.vendorID = u"Module Vendor", 
	.modelID = {0xDE, 0xAD, 0xBE, 0xEF} 
};
	
vendor_array_handler_t array_register_functions = { .nbfuncs = 2,
	.funcs = {
		{FUNC_LED_ON, (blocks_standard_function)Block_Function_LedOn},
		{FUNC_LED_OFF, (blocks_standard_function)Block_Function_LedOff}
	}
};
