#include "User_IRQ.h"
#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include "stm32f4xx.h"

uint32_t Task_ID = 0;
extern TaskHandle_t Task_Shutdown_Handler_Kernel_Pointer;


void EXTI15_10_IRQHandler()
{
    BaseType_t Status;
    uint32_t EXTI_Pending_Interrupt = 0;

    traceISR_ENTER();

    Status = xTaskNotifyIndexedFromISR( Task_Shutdown_Handler_Kernel_Pointer, 
                                        1, 
                                        Task_ID, 
                                        eSetValueWithOverwrite, 
                                        NULL);

    Task_ID = (Task_ID % 3);
    Task_ID ++;

    EXTI_Pending_Interrupt = EXTI->PR;
    EXTI->PR = EXTI_Pending_Interrupt;

    traceISR_EXIT();
}



