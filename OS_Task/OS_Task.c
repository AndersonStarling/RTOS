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
#include "RTOS_State_Machine.h"
#include "queue.h"

#define UART_IN_USE huart1

extern TaskHandle_t Task_Print_Queue_Kernel_Ptr;
extern TaskHandle_t Task_Print_Menu_Kernel_Ptr;
extern TaskHandle_t Task_Led_Effect_Kernel_Ptr;
extern TaskHandle_t Task_RTC_Kernel_Ptr;

extern QueueHandle_t Queue_Data;
extern QueueHandle_t Queue_Print;

extern RTOS_State_Machine_enum_t Global_State;

/* USART receive call back */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{


}


void Task_Print_Queue(void * Task_Param)
{
    uint8_t * Received_Data = NULL;
	UBaseType_t Num_Element_In_Queue = 0;
	
	Num_Element_In_Queue = uxQueueMessagesWaiting(Queue_Data);

	if(Num_Element_In_Queue != 0)
	{
        xQueueReceive(
                    Queue_Print,
                    Received_Data,
                    pdMS_TO_TICKS(500)
                 );

	    App_Print_String(Received_Data);
	}


}

void Task_Print_Menu(void * Task_Param)
{
    const uint8_t * Print_Msg = "RTC and LED application v1.1\n" \
	                            "==============================\n" \
								"============ Menu ============\n" \
								"==============================\n" \
								    "0. LED Effect\n"            \
									"1. RTC configure\n"         \
									"2. Exit\n";


    for(;;)
	{
		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));

		xTaskNotify(Task_Print_Queue, 0, eSetValueWithOverwrite);

        /* Wait event */
        xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500));	 
	}
}

void Task_Led_Effect(void * Task_Param)
{
	const uint8_t * Print_Msg = \
	                            "==============================\n" \
								"========== LED effect ========\n" \
								"==============================\n" \
								    "0. Mode 0\n"            \
									"1. Mode 1\n"            \
									"2. Mode 2\n";

    for(;;)
	{
		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));

		xTaskNotify(Task_Print_Queue, 0, eSetValueWithOverwrite);

        /* Wait event */
        xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500));	 
	}
}

void Task_RTC(void * Task_Param)
{
	const uint8_t * Print_Msg = \
	                            "==============================\n" \
								"============ RTC =============\n" \
								"==============================\n" \
								    "0. Configure time\n"            \
									"1. Configure date\n";

    for(;;)
	{
		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));

		xTaskNotify(Task_Print_Queue_Kernel_Ptr, 0, eSetValueWithOverwrite);

        /* Wait event */
        xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500));	 
	}
}

void Task_Handle_Received_Command(void * Task_Param)
{
	UBaseType_t Num_Element_In_Queue = 0;
	uint8_t Received_Command = 0;

    for(;;)
	{
        /* Wait event */
        xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500));

	    Num_Element_In_Queue = uxQueueMessagesWaiting(Queue_Data);

		if(Num_Element_In_Queue != 0)
		{
			xQueueReceive(
                               Queue_Data,
                               &Received_Command,
                               pdMS_TO_TICKS(500)
                            );

			switch(Received_Command)
			{
				case main_menu:
				    xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0, eSetValueWithOverwrite);
				    break;
				case led_menu:
				    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 0, eSetValueWithOverwrite);
				    break;
				case rtc_menu:
				    xTaskNotify(Task_RTC_Kernel_Ptr, 0, eSetValueWithOverwrite);
				    break;
			}
		}
	}

}












