#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>

void Task_1_Handler(void * Task_Param)
{
    char data[100] = {0};

    /* Infinitive loop */
    for(;;)
    {
        snprintf(data, 100, "%s\n", (char *)Task_Param);

        SEGGER_SYSVIEW_PrintfTarget(data);
        taskYIELD();
    };
}

void Task_2_Handler(void * Task_Param)
{
    char data[100] = {0};

    /* Infinitive loop */
    for(;;)
    {
        snprintf(data, 100, "%s\n", (char *)Task_Param);
        SEGGER_SYSVIEW_PrintfTarget(data);
        taskYIELD();
    };
}









