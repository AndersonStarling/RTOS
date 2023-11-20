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
        SEGGER_SYSVIEW_PrintfTarget("Task_1");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        vTaskDelay(pdMS_TO_TICKS(1000));
        // taskYIELD();
    };
}

void Led_2_Handler(void * Task_Param)
{
    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_2");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        vTaskDelay(pdMS_TO_TICKS(800));
        // taskYIELD();
    };
}

void Led_3_Handler(void * Task_Param)
{

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_3");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        vTaskDelay(pdMS_TO_TICKS(400));
        // taskYIELD();
    };
}









