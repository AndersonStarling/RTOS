#ifndef RTC_LIB_H
#define RTC_LIB_H

#include "rtc.h"

/* Init RTC timer */
void App_RTC_Init(void);

/* Print the time */
void App_RTC_Print_Time(void);

/* Print the date */
void App_RTC_Print_Date(void);

/* Set Hour */
void App_Set_Hour(uint8_t Hour);

/* Set Min */
void App_Set_Min(uint8_t Hour);

/* Set Hour */
void App_Set_Second(uint8_t Hour);

/* Set Date */
void App_Set_Day(uint8_t Date);

/* Set Month */
void App_Set_Month(uint8_t Date);

/* Set Year */
void App_Set_Year(uint8_t Date);

#endif /* RTC_LIB_H */







