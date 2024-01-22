#ifndef CONVERT_LIB_H
#define CONVERT_LIB_H

#include <stdio.h>
#include <stdint.h>

#define APP_CONVERT_HIGH_BYTE_TO_CHAR(Hex_Value) (((Hex_Value) >> 4) & 0x0f) + '0'

#define APP_CONVERT_LOW_BYTE_TO_CHAR(Hex_Value) ((Hex_Value) & 0x0f) + '0'

uint8_t Convert_Char_To_Dec(uint8_t Charater);

#endif /* CONVERT_LIB_H */











