#include "Convert_Lib.h"

uint8_t App_Convert_Hex_To_Char(uint8_t Hex_Value)
{
    uint8_t Ret_Val = 0;

    if(Hex_Value < 10)
    {
        Ret_Val = Hex_Value;
    }

    else if(Hex_Value >= 0x10 && \
            Hex_Value < 0x20)
    {
        Ret_Val = Hex_Value - 10;
    }
    
    else
    {
        Ret_Val = Hex_Value - 12;
    }

    return Ret_Val;
}




