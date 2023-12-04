#include "Rtc_Lib.h"
#include "rtc.h"

/* Print Character */
static void App_Print_Character(uint8_t * Print_Character)
{

}

/* Init RTC timer */
void App_RTC_Init(void)
{
    /* Init RTC */
    MX_RTC_Init();
}

/* Print the time */
void App_RTC_Print_Time(void)
{
    RTC_TimeTypeDef sTime;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_HOURFORMAT12_PM);

    /* Print time according to hh:mm:ss */
    App_Print_Character(sTime.Hours);
    App_Print_Character(':');
    App_Print_Character(sTime.Minutes);
    App_Print_Character(':');
    App_Print_Character(sTime.Seconds);
}

/* Print the date */
void App_RTC_Print_Date(void)
{
    RTC_DateTypeDef sDate;

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
    RTC_TimeTypeDef sDate_local;

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









