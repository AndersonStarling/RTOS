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
extern TaskHandle_t Task_RTC_Configure_Hour_Kernel_Ptr;
extern TaskHandle_t Task_RTC_Configure_Min_Kernel_Ptr;
extern TaskHandle_t Task_RTC_Configure_Second_Kernel_Ptr;
extern TaskHandle_t Task_RTC_Configure_Time_Kernel_Ptr;

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
    	App_RTC_Print_Time();
    	App_RTC_Print_Date();
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
        while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

        Global_State = rtc_menu;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));
	}
}

void Task_RTC_Configure_Time(void * Task_Param)
{
	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"====== RTC Configure Time ====\n" \
								"==============================\n" \
								    "0. Configure hour\n"          \
									"1. Configure min\n"           \
									"2. Configure second\n"        \
	                                "3. Exit\n";

	uint32_t Notified_Value = 0;

    for(;;)
    {
        /* Wait event */
        while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

        Global_State = rtc_menu_configure_time;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
                          &Print_Msg,
                          pdMS_TO_TICKS(500));
    }
}

void Task_RTC_Configure_Hour(void * Task_Param)
{
	uint32_t Notified_Value = 0;

	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"====== RTC Configure Hour ====\n" \
								"==============================\n" \
								    "Please input hour\n"          \
									"Press F to Exit";

	static uint8_t Hour[2] = {0};
	static uint8_t Count = 0;
	static uint8_t Hour_Hex_Form = 0;

	for(;;)
	{
	    /* Wait event */
	    while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

	    Global_State = rtc_menu_configure_hour;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
	                      &Print_Msg,
	                      pdMS_TO_TICKS(500));

	    if( Notified_Value != 0xff )
	    {
		    Hour[Count] = Convert_Char_To_Dec(Notified_Value);
		    Count ++;
		    Count = Count % 2;
		    Hour_Hex_Form = (Hour[0] << 4) | Hour[1];
			App_Set_Hour(Hour_Hex_Form);
	    }
	}
}

void Task_RTC_Configure_Min(void * Task_Param)
{
	uint32_t Notified_Value = 0;

	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"====== RTC Configure Min =====\n" \
								"==============================\n" \
								    "Please input min\n"           \
									"Press F to Exit";

	for(;;)
	{
	    /* Wait event */
	    while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

	    Global_State = rtc_menu_configure_min;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
	                      &Print_Msg,
	                      pdMS_TO_TICKS(500));

	    if( Notified_Value != 0xff )
	    {
		    App_Set_Hour(Notified_Value);
	    }
	}

}

void Task_RTC_Configure_Second(void * Task_Param)
{
	uint32_t Notified_Value = 0;

	const uint8_t * Print_Msg = "\n"                               \
	                            "==============================\n" \
								"==== RTC Configure Second ====\n" \
								"==============================\n" \
								    "Please input second\n"        \
									"Press F to Exit";

	for(;;)
	{
	    /* Wait event */
	    while(pdTRUE != xTaskNotifyWait(0, 0, &Notified_Value, pdMS_TO_TICKS(500))){};

	    Global_State = rtc_menu_configure_second;

		/* Send message pointer to queue */
	    xQueueSendToFront(Queue_Print,
	                      &Print_Msg,
	                      pdMS_TO_TICKS(500));

		App_Set_Second(Notified_Value);
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
		            	xTaskNotify(Task_RTC_Configure_Time_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
		            	break;
		            case '1':
		            	xTaskNotify(Task_RTC_Configure_Time_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
		            	break;
		            case '2':
		            	xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
		            	break;
		            case '3':
		            	xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
		            	break;
		        }
			}
			else if( Global_State == rtc_menu_configure_time )
			{
				switch(Received_Command)
				{
				    case '0':
				    	xTaskNotify(Task_RTC_Configure_Hour_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
				    	break;
				    case '1':
				    	xTaskNotify(Task_RTC_Configure_Min_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
				    	break;
				    case '2':
				    	xTaskNotify(Task_RTC_Configure_Second_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
				    	break;

				}
			}
			else if(Global_State == rtc_menu_configure_hour)
			{
				switch(Received_Command)
				{
				    case 'f':
				    	/* Return to main menu */
//				    	Global_State = main_menu;
				        xTaskNotify(Task_Print_Menu_Kernel_Ptr, 0xff, eSetValueWithOverwrite);
				        break;
				    default:
				    	/* Set Hour */
				        xTaskNotify(Task_RTC_Configure_Hour_Kernel_Ptr, Received_Command, eSetValueWithOverwrite);
				        break;
				}
				/* Set Hour */
				xTaskNotify(Task_RTC_Configure_Hour_Kernel_Ptr, Received_Command, eSetValueWithOverwrite);
			}
			else if(Global_State == rtc_menu_configure_min)
			{
				/* Set Min */
				xTaskNotify(Task_RTC_Configure_Min_Kernel_Ptr, Received_Command, eSetValueWithOverwrite);
			}
			else if(Global_State == rtc_menu_configure_second)
			{
				/* Set Second */
				xTaskNotify(Task_RTC_Configure_Second_Kernel_Ptr, Received_Command, eSetValueWithOverwrite);
			}
		}
	}

}












