#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"


extern TaskHandle_t Led_1_Handler_Kernel_Pointer;
extern TaskHandle_t Led_2_Handler_Kernel_Pointer;
extern TaskHandle_t Led_3_Handler_Kernel_Pointer;
extern TaskHandle_t User_Button_Handler_Kernel_Pointer;
extern TaskHandle_t Task_Shutdown_Handler_Kernel_Pointer;

void Led_1_Handler(void * Task_Param)
{
    uint32_t pulNotificationValue;
    BaseType_t Status;
    uint32_t Task_ID = 0;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_1");
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_10);
        vTaskDelay(pdMS_TO_TICKS(1000));

        Status = xTaskNotifyWait( 0x0, 0xffffffff, &pulNotificationValue, pdMS_TO_TICKS(OS_TASK_TIME_OUT));

        /* A event came */
        if(Status == pdTRUE)
        {
            switch(pulNotificationValue)
            {
                case 0:
                    break;
                case 1:
                    xTaskNotify(Task_Shutdown_Handler_Kernel_Pointer, Task_ID, eNoAction);
                	break;
                default:
                	break;
            }
        }
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
    };
}

void Led_3_Handler(void * Task_Param)
{

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_3");
        HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        vTaskDelay(pdMS_TO_TICKS(400));
    };
}

void User_Button_Handler(void * Task_Param)
{
    GPIO_PinState Button_Status;
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_4_User_Button");
        vTaskDelay(pdMS_TO_TICKS(10));
        Button_Status = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
        xTaskNotify(Led_1_Handler_Kernel_Pointer, Button_Status, eSetValueWithOverwrite);
    }
}

void Task_Shutdown_Handler(void * Task_Param)
{
    uint32_t pulNotificationValue;
    BaseType_t Status;

    /* Infinitive loop */
    for(;;)
    {
        SEGGER_SYSVIEW_PrintfTarget("Task_Shut_Down");
        Status = xTaskNotifyWait( 0x0, 0xffffffff, &pulNotificationValue, pdMS_TO_TICKS(OS_TASK_TIME_OUT));

        /* A event came */
        if(Status == pdTRUE)
        {
            switch(pulNotificationValue)
            {
                case 0:
                    vTaskDelete(Led_1_Handler_Kernel_Pointer);
                    break;
                case 1:
                    vTaskDelete(Led_2_Handler_Kernel_Pointer);
                	break;
                case 2:
                    vTaskDelete(Led_3_Handler_Kernel_Pointer);
                    break;
                default:
                	break;
            }
        }
    };
}












