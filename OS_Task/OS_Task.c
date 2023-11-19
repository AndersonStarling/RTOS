#include "FreeRTOS.h"
#include "task.h"
#include "OS_Task.h"
#include <stdio.h>

void Led_1_Handler(void * Task_Param)
{

    /* Infinitive loop */
    for(;;)
    {
        // snprintf(data, 100, "%s\n", (char *)Task_Param);
        // SEGGER_SYSVIEW_PrintfTarget(data);
        
        

        taskYIELD();
    };
}

void Led_2_Handler(void * Task_Param)
{
    /* Infinitive loop */
    for(;;)
    {
        // snprintf(data, 100, "%s\n", (char *)Task_Param);
        // SEGGER_SYSVIEW_PrintfTarget(data);
        taskYIELD();
    };
}









