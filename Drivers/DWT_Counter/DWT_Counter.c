#include "DWT_Counter.h"
#include <stdint.h>

#define DWT_CTRL (*(volatile uint32_t *)0xE0001000)

void DWT_Enable(void)
{
    DWT_CTRL |= (1 << 0);
}










