#include "Print_Lib.h"
#include "usart.h"
#include <stdbool.h>

#define UART_IN_USE huart1


/* Print Character */
void App_Print_Character(uint8_t Print_Character)
{
    HAL_StatusTypeDef Status;
    uint8_t Send_Character = Print_Character;
    bool RetVal = false;

    while(HAL_BUSY == HAL_UART_Transmit_IT(&UART_IN_USE, &Send_Character, 1));

}

void App_Print_String(uint8_t * String, uint32_t String_Len)
{
    uint32_t Index = 0;

    for(Index = 0; Index < String_Len; Index ++)
    {
        App_Print_Character(String[Index]);
    }
}














