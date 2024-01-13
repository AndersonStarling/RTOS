#ifndef RTC_LIB_H
#define RTC_LIB_H

#include "rtc.h"

/* Init RTC timer */
void App_RTC_Init(void);

/* Print the time */
void App_RTC_Print_Time(void);

/* Print the date */
void App_RTC_Print_Date(void);

/* Set the time */
void App_Set_Time(RTC_TimeTypeDef *sTime);

/* Set the date */
void App_Set_Date(RTC_DateTypeDef *sDate);


#endif /* RTC_LIB_H */







