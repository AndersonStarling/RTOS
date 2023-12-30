#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "Led_Mode.h"

extern TaskHandle_t Led_1_Handler_Kernel_Pointer;
extern TaskHandle_t Led_2_Handler_Kernel_Pointer;
extern TaskHandle_t Led_3_Handler_Kernel_Pointer;
extern TaskHandle_t Task_Suspend_And_Resume_Kernel_Pointer;

TaskHandle_t Task_Kernel_Pointer_Array[4] = { 0 };
                                
uint8_t Task_Index_Shall_Resume = 0;

void OS_Task_Init(void)
{
	Task_Kernel_Pointer_Array[0] = Led_1_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[1] = Led_2_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[2] = Led_3_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[3] = Task_Suspend_And_Resume_Kernel_Pointer;
}

void Led_1_Handler(void * Task_Param)
{
	for(;;)
	{
	    LED_Mode_Off();
	    LED_Mode_0();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void Led_2_Handler(void * Task_Param)
{
	for(;;)
	{
	    LED_Mode_Off();
	    LED_Mode_1();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void Led_3_Handler(void * Task_Param)
{
	for(;;)
	{
	    LED_Mode_Off();
	    LED_Mode_2();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void Task_Resume_And_Suspend(void * Task_Param)
{
    uint8_t Task_Index = 0;

    for(;;)
    {
        /* Suspend all task */
        for(Task_Index = 0; Task_Index < 3; Task_Index ++)
        {
            vTaskSuspend(Task_Kernel_Pointer_Array[Task_Index]);
        }

        /* Resume only one task from UART message */
        vTaskResume(Task_Kernel_Pointer_Array[Task_Index_Shall_Resume]);
    }
}












