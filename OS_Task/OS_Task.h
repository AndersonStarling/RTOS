#ifndef OS_TASK_H
#define OS_TASK_H

#define OS_TASK_TIME_OUT 1000

void Task_Print_Queue(void * Task_Param);
void Task_Print_Menu(void * Task_Param);
void Task_Led_Effect(void * Task_Param);
void Task_RTC(void * Task_Param);
void Task_Handle_Received_Command(void * Task_Param);

#endif /* OS_TASK_H */

