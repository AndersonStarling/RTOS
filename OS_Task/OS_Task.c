#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"


extern TaskHandle_t Led_1_Handler_Kernel_Pointer;
extern TaskHandle_t Led_2_Handler_Kernel_Pointer;
extern TaskHandle_t Led_3_Handler_Kernel_Pointer;
extern TaskHandle_t Task_Shutdown_Handler_Kernel_Pointer;

void Led_1_Handler(void * Task_Param)
{
    uint32_t Button_Status;
    BaseType_t Status;
    uint32_t Task_ID = 0;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_1");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Led_2_Handler(void * Task_Param)
{
    uint32_t Task_ID = 1;
    uint32_t Button_Status;
    BaseType_t Status;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_2");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12);
        vTaskDelay(pdMS_TO_TICKS(800));
    }
}

void Led_3_Handler(void * Task_Param)
{
    uint32_t Task_ID = 2;
    uint32_t Button_Status;
    BaseType_t Status;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_3");
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

void Task_Shutdown_Handler(void * Task_Param)
{
    uint32_t Task_ID;
    BaseType_t Status;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_Shut_Down");
        Status = xTaskNotifyWaitIndexed(1, 0x0, 0xffffffff, &Task_ID, pdMS_TO_TICKS(OS_TASK_TIME_OUT));

        /* A event came */
        if(Status == pdTRUE)
        {
            switch(Task_ID)
            {
                case 0:
                    vTaskDelete(Led_1_Handler_Kernel_Pointer);
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
                    break;
                case 1:
                    vTaskDelete(Led_2_Handler_Kernel_Pointer);
                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
                	break;
                case 2:
                    vTaskDelete(Led_3_Handler_Kernel_Pointer);
                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                    break;
                default:
                	break;
            }
        }
    };
}












