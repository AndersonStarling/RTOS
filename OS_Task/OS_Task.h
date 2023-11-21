#ifndef OS_TASK_H
#define OS_TASK_H

#define OS_TASK_TIME_OUT 1000

void Led_1_Handler(void * Task_Param);
void Led_2_Handler(void * Task_Param);
void Led_3_Handler(void * Task_Param);
void User_Button_Handler(void * Task_Param);
void Task_Shutdown_Handler(void * Task_Param);

#endif /* OS_TASK_H */

