#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"

void Led_1_Handler(void * Task_Param)
{

    /* Infinitive loop */
    for(;;)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        SEGGER_SYSVIEW_PrintfTarget("Task_1");
        HAL_Delay(1000);
        taskYIELD();
    };
    }

void Led_2_Handler(void * Task_Param)
{
    /* Infinitive loop */
    for(;;)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        SEGGER_SYSVIEW_PrintfTarget("Task_2");
        HAL_Delay(800);
        taskYIELD();
    };
}

void Led_3_Handler(void * Task_Param)
{

    /* Infinitive loop */
    for(;;)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        SEGGER_SYSVIEW_PrintfTarget("Task_3");
        HAL_Delay(400);
        taskYIELD();
    };
}









