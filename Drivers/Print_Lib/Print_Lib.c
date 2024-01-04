#include "Print_Lib.h"
#include "usart.h"
#include <stdbool.h>

#define UART_IN_USE huart1


/* Print Character */
bool App_Print_Character(uint8_t Print_Character)
{
    HAL_StatusTypeDef Status;
    uint8_t Send_Character = Print_Character;
    bool RetVal = false;

    Status =  HAL_UART_Transmit_IT(&UART_IN_USE, &Send_Character, 1);

    if(Status == HAL_OK)
    {
        RetVal = true;
    }

    while(HAL_UART_GetState(&UART_IN_USE) == HAL_UART_STATE_BUSY_TX);

    return RetVal;
}

void App_Print_String(uint8_t * String, uint32_t String_Len)
{
    uint32_t Index = 0;

    for(Index = 0; Index < String_Len; Index ++)
    {
        App_Print_Character(String[Index]);
    }
}














