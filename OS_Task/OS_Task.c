#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "Led_Mode.h"

void Led_Select_Mode_Task(void * Task_Param)
{

    SEGGER_SYSVIEW_PrintfTarget("Led_Select_Mode_Task");

    switch(Led_Mode)
    {
        case 0:
            LED_Mode_0();
            vTaskDelay(pdMS_TO_TICKS(400));
            break;
        case 1:
            LED_Mode_0();
            vTaskDelay(pdMS_TO_TICKS(400));
            break;
        case 2:
            LED_Mode_0();
            vTaskDelay(pdMS_TO_TICKS(400));
            break;
        default:
            break;
    }
}












