#include "Led_Mode.h"
#include "stm32f4xx_hal.h"

void LED_Mode_0(void)
{
    HAL_GPIO_TogglePin(PORT_LED_0, PIN_LED_0);
    HAL_GPIO_TogglePin(PORT_LED_1, PIN_LED_1);
    HAL_GPIO_TogglePin(PORT_LED_2, PIN_LED_2);
}

void LED_Mode_1(void)
{
    HAL_GPIO_TogglePin(PORT_LED_0, PIN_LED_0);
    HAL_GPIO_TogglePin(PORT_LED_1, PIN_LED_1);
}

void LED_Mode_2(void)
{
    HAL_GPIO_TogglePin(PORT_LED_0, PIN_LED_0);
}

void LED_Mode_Off(void)
{
    HAL_GPIO_WritePin(PORT_LED_0, PIN_LED_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PORT_LED_1, PIN_LED_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PORT_LED_2, PIN_LED_2, GPIO_PIN_RESET);
}









