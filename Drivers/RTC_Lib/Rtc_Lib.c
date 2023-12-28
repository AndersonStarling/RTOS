#include "Rtc_Lib.h"
#include "Print_Lib.h"
#include "Convert_Lib.h"

/* Print the time */
void App_RTC_Print_Time(void)
{
    RTC_TimeTypeDef sTime;
    uint8_t Hours = 0;
    uint8_t Min = 0;
    uint8_t Sec = 0;

    while(HAL_OK != HAL_RTC_WaitForSynchro(&hrtc));

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_HOURFORMAT12_PM);

    Hours = App_Convert_Hex_To_Char(sTime.Hours);
    Min = App_Convert_Hex_To_Char(sTime.Minutes);
    Sec = App_Convert_Hex_To_Char(sTime.Seconds);

    /* Print time according to hh:mm:ss */
    App_Print_Character(Hours);
    App_Print_Character(':');
    App_Print_Character(Min);
    App_Print_Character(':');
    App_Print_Character(Sec);

}

/* Print the date */
void App_RTC_Print_Date(void)
{
    RTC_DateTypeDef sDate;

    while(HAL_OK == HAL_RTC_WaitForSynchro(&hrtc));

    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BCD);

    /* Print time according to hh:mm:ss */
    App_Print_Character(sDate.Date);
    App_Print_Character('/');
    App_Print_Character(sDate.Month);
    App_Print_Character('/');
    App_Print_Character(sDate.Year);
}

/* Set the time */
void App_Set_Time(RTC_TimeTypeDef *sTime)
{
    RTC_TimeTypeDef sTime_local;

    /* Use as default value */
    HAL_RTC_GetTime(&hrtc, &sTime_local, RTC_HOURFORMAT12_PM);
    sTime->SubSeconds = sTime_local.SubSeconds;
    sTime->SecondFraction = sTime_local.SecondFraction;
    sTime->DayLightSaving = sTime_local.DayLightSaving;
    sTime->StoreOperation = sTime_local.StoreOperation;

    /* Set new time */
    HAL_RTC_SetTime(&hrtc, sTime, RTC_HOURFORMAT12_PM);
}


/* Set the date */
void App_Set_Date(RTC_DateTypeDef *sDate)
{
    RTC_DateTypeDef sDate_local;

    /* Use as default value */
    HAL_RTC_GetDate(&hrtc, &sDate_local, RTC_FORMAT_BCD);
    sDate->WeekDay = sDate_local.WeekDay;

    /* Set new time */
    HAL_RTC_SetDate(&hrtc, sDate, RTC_FORMAT_BCD);
}









