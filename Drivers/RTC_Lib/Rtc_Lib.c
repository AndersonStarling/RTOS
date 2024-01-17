#include "Rtc_Lib.h"
#include "Print_Lib.h"
#include "Convert_Lib.h"

/* Print the time */
void App_RTC_Print_Time(void)
{
    RTC_TimeTypeDef sTime;
    uint8_t Hours_High_Byte = 0;
    uint8_t Hours_Low_Byte = 0;
    uint8_t Min_High_Byte = 0;
    uint8_t Min_Low_Byte = 0;
    uint8_t Sec_High_Byte = 0;
    uint8_t Sec_Low_Byte = 0;

    while(HAL_OK != HAL_RTC_WaitForSynchro(&hrtc));

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_HOURFORMAT12_PM);

    Hours_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sTime.Hours);
    Hours_Low_Byte =  APP_CONVERT_LOW_BYTE_TO_CHAR(sTime.Hours);

    Min_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sTime.Minutes);
    Min_Low_Byte =  APP_CONVERT_LOW_BYTE_TO_CHAR(sTime.Minutes);

    Sec_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sTime.Seconds);
    Sec_Low_Byte = APP_CONVERT_LOW_BYTE_TO_CHAR(sTime.Seconds);

    /* Print time according to hh:mm:ss */
    App_Print_Character(Hours_High_Byte);
    App_Print_Character(Hours_Low_Byte);
    App_Print_Character(':');
    App_Print_Character(Min_High_Byte);
    App_Print_Character(Min_Low_Byte);
    App_Print_Character(':');
    App_Print_Character(Sec_High_Byte);
    App_Print_Character(Sec_Low_Byte);
    App_Print_String("\n");
}

/* Print the date */
void App_RTC_Print_Date(void)
{
    RTC_DateTypeDef sDate;
    uint8_t Date_High_Byte = 0;
    uint8_t Date_Low_Byte = 0;
    uint8_t Month_High_Byte = 0;
    uint8_t Month_Low_Byte = 0;
    uint8_t Year_High_Byte = 0;
    uint8_t Year_Low_Byte = 0;

    while(HAL_OK != HAL_RTC_WaitForSynchro(&hrtc));

    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

    Date_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sDate.Date);
    Date_Low_Byte =  APP_CONVERT_LOW_BYTE_TO_CHAR(sDate.Date);

    Month_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sDate.Month);
    Month_Low_Byte =  APP_CONVERT_LOW_BYTE_TO_CHAR(sDate.Month);

    Year_High_Byte = APP_CONVERT_HIGH_BYTE_TO_CHAR(sDate.Year);
    Year_Low_Byte = APP_CONVERT_LOW_BYTE_TO_CHAR(sDate.Year);

    /* Print time according to dd:mm:yy */
    App_Print_Character(Date_High_Byte);
    App_Print_Character(Date_Low_Byte);
    App_Print_Character('/');
    App_Print_Character(Month_High_Byte);
    App_Print_Character(Month_Low_Byte);
    App_Print_Character('/');
    App_Print_Character(Year_High_Byte);
    App_Print_Character(Year_Low_Byte);
    App_Print_String("\n");
}

/* Set the time */
void App_Set_Time(RTC_TimeTypeDef *sTime)
{
//    RTC_TimeTypeDef sTime_local;

    /* Use as default value */
//    HAL_RTC_GetTime(&hrtc, &sTime_local, RTC_HOURFORMAT12_PM);
//    sTime->SubSeconds = sTime_local.SubSeconds;
//    sTime->SecondFraction = sTime_local.SecondFraction;
//    sTime->DayLightSaving = sTime_local.DayLightSaving;
//    sTime->StoreOperation = sTime_local.StoreOperation;

    /* Set new time */
    HAL_RTC_SetTime(&hrtc, sTime, RTC_HOURFORMAT12_PM);
}


/* Set the date */
void App_Set_Date(RTC_DateTypeDef *sDate)
{
//    RTC_DateTypeDef sDate_local;

    /* Use as default value */
//    HAL_RTC_GetDate(&hrtc, &sDate_local, RTC_FORMAT_BCD);
//    sDate->WeekDay = sDate_local.WeekDay;

    /* Set new time */
    HAL_RTC_SetDate(&hrtc, sDate, RTC_FORMAT_BCD);
}









