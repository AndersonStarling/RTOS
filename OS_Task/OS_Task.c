#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "Led_Mode.h"
#include "usart.h"
#include <string.h>
#include "Rtc_Lib.h"
#include "Print_Lib.h"

#define UART_IN_USE huart1

extern TaskHandle_t Led_1_Handler_Kernel_Pointer;
extern TaskHandle_t Led_2_Handler_Kernel_Pointer;
extern TaskHandle_t Led_3_Handler_Kernel_Pointer;
extern TaskHandle_t Task_Suspend_And_Resume_Kernel_Pointer;

TaskHandle_t Task_Kernel_Pointer_Array[4] = { 0 };
uint8_t Rx_Buffer[2] = {0};
                                
uint8_t Task_Index_Shall_Resume = 0;
uint8_t Task_Off_Led = 0;

void OS_Task_Init(void)
{
	uint8_t Task_Index = 0;

	Task_Kernel_Pointer_Array[0] = Led_1_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[1] = Led_2_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[2] = Led_3_Handler_Kernel_Pointer;
	Task_Kernel_Pointer_Array[3] = Task_Suspend_And_Resume_Kernel_Pointer;

	/* Suspend all task */
    for(Task_Index = 0; Task_Index < 3; Task_Index ++)
    {
        vTaskSuspend(Task_Kernel_Pointer_Array[Task_Index]);
    }

	HAL_UART_Receive_IT(&UART_IN_USE, &Rx_Buffer[0], 1);
}

void Led_1_Handler(void * Task_Param)
{
    TaskHandle_t Curent_Task;
    uint8_t Task_Index = 0;

	for(;;)
	{
	    Curent_Task = xTaskGetCurrentTaskHandle();

		for(Task_Index = 0; Task_Index < 3; Task_Index ++)
	    {
			/* Suspend all another task, excep this task */
			if(Curent_Task != Task_Kernel_Pointer_Array[Task_Index])
			{
	            vTaskSuspend(Task_Kernel_Pointer_Array[Task_Index]);
			}
	    }

    	if(Task_Off_Led != 0)
    	{
    		LED_Mode_Off();
    	}

    	Task_Off_Led = 0;

	    LED_Mode_0();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void Led_2_Handler(void * Task_Param)
{
	TaskHandle_t Curent_Task;
    uint8_t Task_Index = 0;

	for(;;)
	{
	    Curent_Task = xTaskGetCurrentTaskHandle();

		for(Task_Index = 0; Task_Index < 3; Task_Index ++)
	    {
			/* Suspend all another task, excep this task */
			if(Curent_Task != Task_Kernel_Pointer_Array[Task_Index])
			{
	            vTaskSuspend(Task_Kernel_Pointer_Array[Task_Index]);
			}
	    }

    	if(Task_Off_Led != 0)
    	{
    		LED_Mode_Off();
    	}

    	Task_Off_Led = 0;

	    LED_Mode_1();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void Led_3_Handler(void * Task_Param)
{
	TaskHandle_t Curent_Task;
    uint8_t Task_Index = 0;

	for(;;)
	{
	    Curent_Task = xTaskGetCurrentTaskHandle();

		for(Task_Index = 0; Task_Index < 3; Task_Index ++)
	    {
			/* Suspend all another task, excep this task */
			if(Curent_Task != Task_Kernel_Pointer_Array[Task_Index])
			{
	            vTaskSuspend(Task_Kernel_Pointer_Array[Task_Index]);
			}
	    }

    	if(Task_Off_Led != 0)
    	{
    		LED_Mode_Off();
    	}

    	Task_Off_Led = 0;

	    LED_Mode_2();
	    vTaskDelay(pdMS_TO_TICKS(400));
	}
}

/* USART receive call back */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Re-Enable RXNE interrupt */
	HAL_UART_Receive_IT(&UART_IN_USE, &Rx_Buffer[0], 1);

	Task_Off_Led ++;

	switch(Rx_Buffer[0])
	{
	    case '0':
	    	Task_Index_Shall_Resume = 0;
	    	break;
	    case '1':
	    	Task_Index_Shall_Resume = 1;
	    	break;
	    case '2':
	    	Task_Index_Shall_Resume = 2;
	    	break;
	    default:
		    break;
	}
}


void Task_Resume_And_Suspend(void * Task_Param)
{
    for(;;)
    {
        /* Resume only one task from UART message */
        vTaskResume(Task_Kernel_Pointer_Array[Task_Index_Shall_Resume]);
    }
}

void Task_Print_Information(void * Task_Param)
{
    uint8_t Task_Clear_Screen_Cmd[4] = {0x1B, 0x5B, 0x32, 0x4a};

	for(;;)
	{
		/* Clear terminal screen */
		App_Print_Character(Task_Clear_Screen_Cmd[0]);
		App_Print_Character(Task_Clear_Screen_Cmd[1]);
		App_Print_Character(Task_Clear_Screen_Cmd[2]);
		App_Print_Character(Task_Clear_Screen_Cmd[3]);

		/* Print program content */
        App_Print_String((uint8_t *)"------- RTC and Led application v1.0 -------");
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

        /* Print Date */
		App_Print_String((uint8_t *)"Date: ");
		App_RTC_Print_Date();
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		/* Print Time */
		App_Print_String((uint8_t *)"Time: ");
		App_RTC_Print_Time();
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		App_Print_String((uint8_t *)"Led Mode ");
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		App_Print_String((uint8_t *)"0. Mode 0");
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		App_Print_String((uint8_t *)"1. Mode 1");
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		App_Print_String((uint8_t *)"2. Mode 2");
		App_Print_Character(0x0a);
		App_Print_Character(0x0d);

		vTaskDelay(pdMS_TO_TICKS(800));

	}
}












