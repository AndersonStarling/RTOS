#ifndef CONVERT_LIB_H
#define CONVERT_LIB_H

#include <stdio.h>
#include <stdint.h>

#define APP_CONVERT_HIGH_BYTE_TO_CHAR(Hex_Value) (((Hex_Value) >> 4) & 0x0f) + '0'

#define APP_CONVERT_LOW_BYTE_TO_CHAR(Hex_Value) ((Hex_Value) & 0x0f) + '0'

#endif /* CONVERT_LIB_H */











