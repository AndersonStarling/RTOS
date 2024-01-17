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
extern TaskHandle_t Task_Handle_Received_Command_Kernel_Ptr;

extern QueueHandle_t Queue_Data;
extern QueueHandle_t Queue_Print;
extern uint8_t App_Data;

extern RTOS_State_Machine_enum_t Global_State;

/* USART receive call back */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    xQueueSendFromISR
                     (
                        Queue_Data,
                        &App_Data,
                        NULL
                     );

    HAL_UART_Receive_IT(&huart1, (uint8_t*)&App_Data, 1);

    xTaskNotifyFromISR(Task_Handle_Received_Command_Kernel_Ptr,
                                    0,
									eSetValueWithOverwrite,
                                    NULL );
 
}

void Task_Print_Queue(void * Task_Param)
{
    uint32_t Received_Data;
	UBaseType_t Num_Element_In_Queue = 0;
	
	for(;;)
	{
		Num_Element_In_Queue = uxQueueMessagesWaiting(Queue_Print);

		if(Num_Element_In_Queue != 0)
		{
	        xQueueReceive(
	                    Queue_Print,
	                    &Received_Data,
	                    pdMS_TO_TICKS(500)
	                 );

		    App_Print_String((uint8_t *)Received_Data);
		}
	}
}

void Task_Print_Menu(void * Task_Param)
{
    const uint8_t * Print_Msg = "\n"                               \
    		                    "RTC and LED application v1.1\n"   \
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

        /* Wait event */
        while(pdTRUE != xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500)));	 
	}
}

void Task_Led_Effect(void * Task_Param)
{
	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"========== LED effect ========\n" \
								"==============================\n" \
								    "0. Mode 0\n"            \
									"1. Mode 1\n"            \
									"2. Mode 2\n"            \
									"3. Exit\n";

	uint32_t Notified_Value = 0;

    for(;;)
	{
        /* Wait event */
        while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

    	/* Switch app state to led_menu */
    	Global_State = led_menu;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));

        switch(Notified_Value)
        {
            case 0:
            	LED_Mode_Off();
            	LED_Mode_0();
            	break;
            case 1:
            	LED_Mode_Off();
            	LED_Mode_1();
            	break;
            case 2:
            	LED_Mode_Off();
            	LED_Mode_2();
            	break;
            case 3:
            	xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
            	break;
        }

	}
}

void Task_RTC(void * Task_Param)
{
	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"============ RTC =============\n" \
								"==============================\n" \
								    "0. Configure time\n"          \
									"1. Configure date\n"          \
	                                "2. Exit\n";

	uint32_t Notified_Value = 0;

    for(;;)
	{
        /* Wait event */
        while(pdTRUE != xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500))){};

        Global_State = rtc_menu;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));

        switch(Notified_Value)
        {
            case 0:
            	break;
            case 1:
            	break;
            case 2:
            	xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
            	break;
        }

	}
}

void Task_Handle_Received_Command(void * Task_Param)
{
	UBaseType_t Num_Element_In_Queue = 0;
	uint8_t Received_Command = 0;

    for(;;)
	{
        /* Wait event */
        while(pdTRUE != xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(500))){};

	    Num_Element_In_Queue = uxQueueMessagesWaiting(Queue_Data);

		if(Num_Element_In_Queue != 0)
		{
			xQueueReceive(
                               Queue_Data,
                               &Received_Command,
                               pdMS_TO_TICKS(500)
                            );

			if( Global_State == main_menu )
			{
				switch(Received_Command)
				{
					case '0':
					    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
					    break;
					case '1':
					    xTaskNotify(Task_RTC_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
					    break;
					case '2':
					    xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
					    break;
				}
			}
			else if( Global_State == led_menu )
			{
				switch(Received_Command)
				{
					case '0':
					    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 0, eSetValueWithOverwrite);
					    break;
					case '1':
					    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 1, eSetValueWithOverwrite);
					    break;
					case '2':
					    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 2, eSetValueWithOverwrite);
					    break;
					case '3':
					    xTaskNotify(Task_Led_Effect_Kernel_Ptr, 3, eSetValueWithOverwrite);
					    break;
				}
			}
			else if( Global_State == rtc_menu)
			{
				switch(Received_Command)
				{
					case '0':
					    xTaskNotify(Task_RTC_Kernel_Ptr, 0, eSetValueWithOverwrite);
					    break;
					case '1':
					    xTaskNotify(Task_RTC_Kernel_Ptr, 1, eSetValueWithOverwrite);
					    break;
					case '2':
					    xTaskNotify(Task_RTC_Kernel_Ptr, 2, eSetValueWithOverwrite);
					    break;
				}
			}
		}
	}

}












