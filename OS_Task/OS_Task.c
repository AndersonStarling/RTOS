#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>

void Task_1_Handler(void * Task_Param)
{
    /* Infinitive loop */
    for(;;)
    {
        printf("%s\n", (char *)Task_Param);
        taskYIELD();
    };
}

void Task_2_Handler(void * Task_Param)
{
    /* Infinitive loop */
    for(;;)
    {
        printf("%s\n", (char *)Task_Param);
        taskYIELD();
    };
}









